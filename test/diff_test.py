
"""
This performs differential testing between Minisat 2.2.0 and Team7dot3's SAT solver.
"""

import random
import sys
import re 
import os
from subprocess import Popen, PIPE
import time


INPUT_PATH  = 'txt/diff_test.txt'
LOG_PATH    = 'txt/log_diff_test.txt'
EXE_PATH    = 'bin/sat_solver.o'
MINI_PATH   = 'minisat'
MAX_VARS    = 40  # The maximum number of variables
MAX_CLAUSES = 100 # The maximum number of clauses
TEST_RUNS   = 100 # The number of tests to run

def exec_process(args):
  """
  Executes a program and passes to it any accompanied arguments.
  Input args must be an array with the path to the program executable in the first index.
  Returns the stdout printout of the program.
  """
  ps         = Popen(args, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  return out


def init_random():
  """
  Initializes the random number generator with the current time.
  """
  random.seed(time.time())

class Logger:
  """
  Logger is a wrapper for a file writer. 
  """

  def __init__(self, path):
    """
    Initializes the Logger with the input path.
    The input path represents the file to write log messages to.
    """
    self.log_file = open(path, 'wb')

  def write(self, str):
    """
    Writes the input string to the log file.
    """
    self.log_file.write('==============================\n\n')
    self.log_file.write(str)
    self.log_file.write('\n==============================\n')
    
  def close(self):
    """
    Closes the log file. Do not call write() after calling close()!
    """
    self.log_file.close()


class Minisat:
  """
  Provides an easy mechanism for calling minisat with an input file.
  """

  def __init__(self, path):
    """
    Sets the input file to be passed to minisat.
    """
    self.path = path

  def run(self):
    """
    Returns the output of minisat.
    """
    return exec_process([MINI_PATH, self.path])


class Sat:
  """
  Provides an easy machnism for call sat_solve.o with an input file.
  """

  def __init__(self, path):
    """
    Sets the input file to be passed to sat_solver.o.
    """
    self.path = path

  def run(self):
    """
    Returns the output of sat_solver.o.
    """
    return exec_process([EXE_PATH, self.path])


class RandomTesting:
  """
  A random tester for sat_solver.o. This creates a CNF input with a random
  number of variables and clauses. The output is then compared against
  minisat. If the outputs do not match, the test fails.
  """

  def __init__(self, path, max_vars, max_clauses, itrs):
    """
    Initializes the random testing.

    path -- file path for log file
    max_num -- the maximum number of variables and clauses
    itrs -- the number of tests to run

    """
    self.path        = path
    self.max_vars    = max_vars
    self.max_clauses = max_clauses
    self.itrs        = itrs

  def gen_rand_input(self):
    """
    Generates a random input file for testing.
    """
    self.nbvars    = random.randint(1, self.max_vars)
    self.nbclauses = random.randint(1, self.max_clauses)

    with open(self.path, 'wb') as f:
      f.write('p cnf ' + str(self.nbvars) + ' ' + str(self.nbclauses) + ' \n')
      
      for i in range(0, self.nbclauses):
        # Use list to store used variables per clause
        used_vars = []
        attempts  = 0
        for j in range(0, random.randint(1, self.nbvars)):
          if attempts > 1000:
            # do waste time trying to generate random values if duplicates keep occuring
            continue
          var = random.randint(-self.nbvars, self.nbvars)
          if var == 0:
            # only write '0' if terminating the clause
            continue 
          elif var in used_vars:
            # do not write duplicate variables (per clause) to file
            continue 
          else:
            used_vars.append(var)
            f.write(str(var) + ' ')
        if len(used_vars) == 0:
          # make sure there are no empty clauses
          f.write('1' + ' ') 
        f.write('0 \n')

  def run(self):
    """
    Executes the tests. Returns the number of passed tests.
    """
    log    = Logger(LOG_PATH)
    passed = 0

    for i in range(0, self.itrs):
      self.gen_rand_input()
      prev_pass  = passed
      start_time = time.time()
      passed    += self.test()
      end_time   = time.time()
      if prev_pass == passed:
        input_file  = None
        with open(self.path, 'r') as f:
          input_file = f.read()
        log.write('Test FAILED with input:\n' + input_file + '\n  run time = ' + str(end_time - start_time))
      else:
        log.write('Test number [' + str(i) + '] PASSED.\n  nbvars    = ' + str(self.nbvars) + '\n  nbclauses = ' + str(self.nbclauses) + '\n  run time  = ' + str(end_time - start_time))
    log.close()
    return passed

  def test(self):
    """
    Represents an individual test. Compares the output of
    minisat to sat_solver.o.
    """
    ms_out    = Minisat(self.path).run().split('\n')
    ms_result = ms_out[len(ms_out) - 2] + '\n'
    t7_out    = Sat(self.path).run()
    
    if ms_result == t7_out:
      return 1
    else:
      return 0


if __name__ == '__main__':
  init_random()
  passed = RandomTesting(INPUT_PATH, MAX_VARS, MAX_CLAUSES, TEST_RUNS).run()

  print '\n\n\nDifferential Testing:'
  print '  PASSED: ' + str(passed)
  print '  FAILED: ' + str(TEST_RUNS - passed)

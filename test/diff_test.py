
"""
This performs differential testing between Minisat 2.2.0 and Team7dot3's SAT solver.
"""

import random
import sys
import re 
import os
from subprocess import Popen, PIPE
import time


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
    return exec_process(['minisat', self.path])


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
    return exec_process(['bin/sat_solver.o', self.path])


class RandomTesting:
  """
  A random tester for sat_solver.o. This creates a CNF input with a random
  number of variables and clauses. The output is then compared against
  minisat. If the outputs do not match, the test fails.
  """

  def __init__(self, path, max_num, itrs):
    """
    Initializes the random testing.

    path -- file path for log file
    max_num -- the maximum number of variables and clauses
    itrs -- the number of tests to run

    """
    self.path = path
    self.max  = max_num
    self.itrs = itrs

  def gen_rand_input(self):
    """
    Generates a random input file for testing.
    """
    self.nbvars    = random.randint(1, self.max)
    self.nbclauses = random.randint(1, self.max)

    with open(self.path, 'wb') as f:
      f.write('p cnf ' + str(self.nbvars) + ' ' + str(self.nbclauses) + ' \n')
      
      for i in range(0, self.nbclauses):
        for j in range(0, random.randint(1, self.nbvars)):
          if random.randint(0, self.nbvars) % 2 == 0:
            f.write('-')
          f.write(str(random.randint(1, self.nbvars)) + ' ')
        f.write('0 \n')

  def run(self):
    """
    Executes the tests. Returns the number of passed tests.
    """
    log    = Logger('txt/log_diff_test.txt')
    passed = 0

    for i in range(0, self.itrs):
      self.gen_rand_input()
      prev_pass = passed
      passed   += self.test()
      if prev_pass == passed:
        input_file  = None
        with open(self.path, 'r') as f:
          input_file = f.read()
        log.write('Test FAILED with input:\n' + input_file)

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
  max_var   = 100 # <-- The maximum number of variables and clauses
  test_runs = 100 # <-- The number of tests to run
  passed    = RandomTesting('txt/diff_test.txt', max_var, test_runs).run()

  print '\n\n\nDifferential Testing:'
  print '  PASSED: ' + str(passed)
  print '  FAILED: ' + str(test_runs - passed)

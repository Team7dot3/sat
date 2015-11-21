import random
import time
from process import *
from logger import *
from sat import *

INPUT_PATH = 'txt/diff_test.txt'
LOG_PASS   = 'txt/log_diff_pass.txt'
LOG_FAIL   = 'txt/log_diff_fail.txt'

class RandomTesting:
  """
  A random tester for sat_solver.o. This creates a CNF input with a random
  number of variables and clauses. The output is then compared against
  minisat. If the outputs do not match, the test fails.
  """

  def __init__(self, path, max_vars, max_clauses, max_pures, itrs):
    """
    Initializes the random testing.

    path -- file path for log file
    max_num -- the maximum number of variables and clauses
    itrs -- the number of tests to run

    """
    self.path        = path
    self.max_vars    = max_vars
    self.max_clauses = max_clauses
    self.max_pures   = max_clauses * max_pures
    self.itrs        = itrs
    self.ms          = Minisat()
    self.t7          = T7_sat()
    self.init_random()

  def init_random(self):
    """
    Initializes the random number generator with the current time.
    """
    random.seed(time.time())

  def gen_rand_input(self):
    """
    Generates a random input file for testing.
    """
    self.nbvars    = random.randint(1, self.max_vars)
    self.nbclauses = random.randint(1, self.max_clauses)
    pures_found    = 0

    with open(self.path, 'wb') as f:
      f.write('p cnf ' + str(self.nbvars) + ' ' + str(self.nbclauses) + ' \n')
      
      for i in range(0, self.nbclauses):
        # Use list to store used variables per clause
        used_vars = []
        attempts  = 0
        for j in range(0, random.randint(1, self.nbvars)):
          if attempts > 10000:
            # do waste time trying to generate random values if duplicates keep occuring
            continue
          var = random.randint(-self.nbvars, self.nbvars)
          if var == 0:
            # only write '0' if terminating the clause
            continue 
          elif var in used_vars:
            # do not write duplicate variables (per clause) to file
            continue
          elif (abs(var) in used_vars) or (var * -1 in used_vars):
            # do not allow the clause to become pure if there many pure clauses exist
            pures_found += 1
            if pures_found >= self.max_pures:
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
    pass_log = Logger(LOG_PASS, False)
    fail_log = Logger(LOG_FAIL, True)
    passed   = 0

    pass_log.write('# \tV \tC \tTime \n')

    for i in range(0, self.itrs):
      self.gen_rand_input()
      prev_pass  = passed
      passed    += self.test()
      if prev_pass == passed:
        input_file  = None
        with open(self.path, 'r') as f:
          input_file = f.read()
        fail_log.write('Test FAILED with input:\n' + input_file)
      else:
        pass_log.write(str(i) + '\t' + str(self.nbvars) + '\t' + str(self.nbclauses) + '\t' + self.t7.get_cpu_time() + '\n')
    pass_log.close()
    fail_log.close()
    return passed

  def test(self):
    """
    Represents an individual test. Compares the output of
    minisat to sat_solver.o.
    """
    self.ms.run(self.path)
    self.t7.run(self.path)

    if self.ms.get_result() == self.t7.get_result():
      return 1
    else:
      return 0
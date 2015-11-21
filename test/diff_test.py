
"""
This performs differential testing between Minisat 2.2.0 and Team7dot3's SAT solver.
"""
from lib.sat_solver.sat_random import *

MAX_VARS    = 20 # The maximum number of variables
MAX_CLAUSES = 1000 # The maximum number of clauses
MAX_PURES   = 0.20 # The maximum ration of pure clauses to clauses
TEST_RUNS   = 10 # The number of tests to run

if __name__ == '__main__':
  # init_random()
  passed = RandomTesting(INPUT_PATH, MAX_VARS, MAX_CLAUSES, MAX_PURES, TEST_RUNS).run()

  print '\n\n\nDifferential Testing:'
  print '  PASSED: ' + str(passed)
  print '  FAILED: ' + str(TEST_RUNS - passed)

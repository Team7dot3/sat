
"""
This performs differential testing between Minisat 2.2.0 and Team7dot3's SAT solver.
"""
from lib.sat_solver.sat_random import *
from lib.sat_solver.colors import *

INPUT_PATH  = 'txt/diff_test.txt'
MAX_VARS    = 150  # The maximum number of variables
MAX_CLAUSES = 1000 # The maximum number of clauses
MAX_PURES   = 0.20 # The maximum ration of pure clauses to clauses
TEST_RUNS   = 1000 # The number of tests to run

if __name__ == '__main__':
  diff = Colors.BOLD + '\n\n\nDifferential Testing:' + Colors.ENDC
  
  print diff
  passed = RandomTesting(INPUT_PATH, MAX_VARS, MAX_CLAUSES, MAX_PURES, TEST_RUNS).run()
  
  print diff
  print Colors.BOLD + '  PASSED: ' + Colors.OKGREEN + str(passed)             + Colors.ENDC
  print Colors.BOLD + '  FAILED: ' + Colors.FAIL    + str(TEST_RUNS - passed) + Colors.ENDC

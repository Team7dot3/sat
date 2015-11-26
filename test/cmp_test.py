import os
from lib.sat_solver.process import *
from lib.sat_solver.opponent import *
from lib.sat_solver.colors import *
from lib.sat_solver.sat import *
import sys
import re

MS_TIMEOUT = 180 # Minisat Timeout Limit in seconds
T7_TIMEOUT = 300 # Team7 Timeout Limit in seconds
OP_TIMEOUT = 300 # Opponents Timeout Limit in seconds

if __name__ == '__main__':
  input_path = None
  root_path  = os.getcwd()

  for arg in sys.argv:
    # find if an input file was passed an a command line argument
    if re.search('.txt', arg) or re.search('.cnf', arg):
      input_path = str(arg[2:])
    if input_path is None:
      input_path = 'txt/input.txt'

  # execute and print results of Minisat
  print '\n'

  # print which input path will be used
  print Colors.BOLD + input_path + Colors.ENDC + '\n\n'

  print Colors.HEADER + Colors.BOLD + 'Minisat' + Colors.ENDC
  ms = Minisat(MS_TIMEOUT)
  ms.run(input_path)
  print Colors.OKGREEN + Colors.BOLD + ms.get_result() + Colors.ENDC + '\n'

  opponents  = Opponent.setup_opponents(root_path, OP_TIMEOUT)
  for op in opponents:
    print Colors.HEADER + Colors.BOLD + op.name + Colors.ENDC

    if not os.path.exists(op.clone_path):
      op.clone()
      op.build()
    if '--b' in sys.argv:
      # command line argument to clone, pull, build opponents source code
      if not os.path.isdir(op.clone_path):
        op.clone()
      op.fetch()
      op.pull()
      op.build()

    # exeucte and print results of teams SAT Solver
    print Colors.OKGREEN + Colors.BOLD + op.run(input_path) + Colors.ENDC + '\n'

  # execute and print results of our SAT Solver
  print Colors.HEADER + Colors.BOLD + 'Team7' + Colors.ENDC
  t7 = T7_sat(T7_TIMEOUT)
  print Colors.OKBLUE + Colors.BOLD + 'RUNNING\t\t Team7' + Colors.ENDC
  t7.run(input_path)
  print Colors.OKGREEN + Colors.BOLD + t7.get_result() + Colors.ENDC + '\n\n'



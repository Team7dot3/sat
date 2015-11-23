import os
from lib.sat_solver.process import *
from lib.sat_solver.opponent import *
from lib.sat_solver.colors import *
from lib.sat_solver.sat import *
import sys
import re

if __name__ == '__main__':
  input_path = None
  root_path  = os.getcwd()
  opponents  = Opponent.setup_opponents(root_path)
  for team in opponents:
    print Colors.HEADER + Colors.BOLD + team.name + Colors.ENDC

    if '--b' in sys.argv:
      if not os.path.exists(team.clone_path):
        team.clone()
      team.fetch()
      team.pull()
      team.build()

    for arg in sys.argv:
      if re.search('.txt', arg) or re.search('.cnf', arg):
        input_path = str(arg[2:])
    if input_path is None:
      input_path = 'txt/input.txt'
    print Colors.OKGREEN + Colors.BOLD + team.run(input_path) + Colors.ENDC + '\n'

  print Colors.HEADER + Colors.BOLD + 'Team7' + Colors.ENDC
  t7 = T7_sat()
  t7.run(input_path)
  print Colors.OKGREEN + Colors.BOLD + t7.get_result() + Colors.ENDC + '\n'

  print Colors.HEADER + Colors.BOLD + 'Minisat' + Colors.ENDC
  ms = Minisat()
  ms.run(input_path)
  print Colors.OKGREEN + Colors.BOLD + ms.get_result() + Colors.ENDC + '\n'

  print Colors.BOLD + input_path + Colors.ENDC

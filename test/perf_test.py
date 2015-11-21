import os
from lib.sat_solver.process import Process
from lib.sat_solver.opponent import Opponent
from lib.sat_solver.colors import Colors

if __name__ == '__main__':
  root_path = os.getcwd()
  opponents = Opponent.setup_opponents(root_path)
  for team in opponents:
    print Colors.HEADER + Colors.BOLD + team.name() + Colors.ENDC
    if not os.path.exists(team.clone_path):
      team.clone()
    team.fetch()
    team.pull()
    team.build()
    print Colors.OKGREEN + Colors.BOLD + team.run('txt/input.txt') + Colors.ENDC


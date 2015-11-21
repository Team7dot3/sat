import os
from lib.sat_solver.process import Process

ROOT_PATH = ''

class bcolors:
  # http://stackoverflow.com/questions/287871/print-in-terminal-with-colors-using-python
  HEADER    = '\033[95m'
  OKBLUE    = '\033[94m'
  OKGREEN   = '\033[92m'
  WARNING   = '\033[93m'
  FAIL      = '\033[91m'
  ENDC      = '\033[0m'
  BOLD      = '\033[1m'
  UNDERLINE = '\033[4m'

class Opponent:
  def __init__(self, team_name, repo_url, clone_path, exe_path):
    self.team_name  = team_name
    self.repo_url   = repo_url
    self.clone_path = clone_path
    self.exe_path   = exe_path

  def build(self):
    print bcolors.OKBLUE + 'BUILDING' + bcolors.ENDC
    os.chdir(self.clone_path)
    ret = Process().run(['make'])
    os.chdir(ROOT_PATH)
    return ret

  def clone(self):
    print bcolors.OKBLUE + 'CLONING' + bcolors.ENDC
    return Process().run(['git', 'clone', self.repo_url, self.clone_path])

  def fetch(self):
    print bcolors.OKBLUE + 'FETCHING' + bcolors.ENDC
    os.chdir(self.clone_path)
    ret = Process().run(['git', 'fetch'])
    os.chdir(ROOT_PATH)
    return ret

  def name(self):
    return self.team_name

  def pull(self):
    print bcolors.OKBLUE + 'PULLING' + bcolors.ENDC
    os.chdir(self.clone_path)
    ret = Process().run(['git', 'pull'])
    os.chdir(ROOT_PATH)
    return ret

  def run(self, input_path):
    print bcolors.OKBLUE + 'RUNNING' + bcolors.ENDC
    executable = self.clone_path + self.exe_path
    if os.path.isfile(executable):
      return Process().run([self.clone_path + self.exe_path, input_path])
    else:
      return 'EXECUTABLE NOT FOUND\n'

def setup_opponents():
  opponents = [];
  opponents.append(Opponent(
      'CompUtahs', 
      'https://github.com/CompUtahs/sat-solver.git',
      'opponents/computahs',
      '/dpll_solver',
    )
  )
  opponents.append(Opponent(
      'TeamNighthawk', 
      'https://github.com/TeamNighthawk/sat.git',
      'opponents/nighthawk',
      '/bin/satsolv'
    )
  )
  opponents.append(Opponent(
      'SegmentationFaults', 
      'https://github.com/michaelandersonb/segmentationfaults.git',
      'opponents/segfaults',
      '/solver'
    )
  )
  opponents.append(Opponent(
      'Toianoke', 
      'https://github.com/Toianoke/SAT.git',
      'opponents/taianoke',
      '/sat'
    )
  )
  return opponents

if __name__ == '__main__':
  ROOT_PATH = os.getcwd()
  opponents = setup_opponents()
  for team in opponents:
    print bcolors.HEADER + bcolors.BOLD + team.name() + bcolors.ENDC
    if not os.path.exists(team.clone_path):
      team.clone()
    team.fetch()
    team.pull()
    team.build()
    print bcolors.OKGREEN + bcolors.BOLD + team.run('txt/input.txt') + bcolors.ENDC


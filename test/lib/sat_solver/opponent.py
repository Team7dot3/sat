import os
from process import Process
from colors import Colors

class Opponent:
  def __init__(self, root_path, team_name, repo_url, clone_path, exe_path):
    self.root_path  = root_path
    self.team_name  = team_name
    self.repo_url   = repo_url
    self.clone_path = clone_path
    self.exe_path   = exe_path

  def build(self):
    print Colors.OKBLUE + 'BUILDING' + Colors.ENDC
    os.chdir(self.clone_path)
    ret = Process().run(['make'])
    os.chdir(self.root_path)
    return ret

  def clone(self):
    print Colors.OKBLUE + 'CLONING' + Colors.ENDC
    return Process().run(['git', 'clone', self.repo_url, self.clone_path])

  def fetch(self):
    print Colors.OKBLUE + 'FETCHING' + Colors.ENDC
    os.chdir(self.clone_path)
    ret = Process().run(['git', 'fetch'])
    os.chdir(self.root_path)
    return ret

  def name(self):
    return self.team_name

  def pull(self):
    print Colors.OKBLUE + 'PULLING' + Colors.ENDC
    os.chdir(self.clone_path)
    ret = Process().run(['git', 'pull'])
    os.chdir(self.root_path)
    return ret

  def run(self, input_path):
    print Colors.OKBLUE + 'RUNNING' + Colors.ENDC
    executable = self.clone_path + self.exe_path
    if os.path.isfile(executable):
      return Process().run([self.clone_path + self.exe_path, input_path])
    else:
      return 'EXECUTABLE NOT FOUND\n'

  @staticmethod
  def setup_opponents(root_path):
    opponents = [];
    opponents.append(Opponent(
        root_path,
        'CompUtahs', 
        'https://github.com/CompUtahs/sat-solver.git',
        'opponents/computahs',
        '/dpll_solver',
      )
    )
    opponents.append(Opponent(
        root_path,
        'TeamNighthawk', 
        'https://github.com/TeamNighthawk/sat.git',
        'opponents/nighthawk',
        '/bin/satsolv'
      )
    )
    opponents.append(Opponent(
        root_path,
        'SegmentationFaults', 
        'https://github.com/michaelandersonb/segmentationfaults.git',
        'opponents/segfaults',
        '/solver'
      )
    )
    opponents.append(Opponent(
        root_path,
        'Toianoke', 
        'https://github.com/Toianoke/SAT.git',
        'opponents/taianoke',
        '/sat'
      )
    )
    return opponents  

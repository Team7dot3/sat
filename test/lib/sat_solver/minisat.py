import os
import exec_process

class Minisat:
  """
  Provides an easy mechanism for calling minisat with an input file.
  """

  def __init__(self):
    """
    This first checks if minisat was compiled in the extras folder.
    If so, the compiled executable is used.
    Otherwise, this assumes minisat is setup properly in the environment. 
    """
    opt_path = 'extras/minisat/core/minisat'
    if os.path.isfile(opt_path):
      self.path = opt_path
    else:
      self.path = 'minisat'

  def run(self, input_path):
    """
    Executes minisat and saves the result and cpu_time.
    """
    out           = exec_process([self.path, input_path])
    self.cpu_time = ((out[len(out) - 4]).split())[3]
    self.result   = out[len(out) - 2]

  def get_result(self):
    return self.result

  def get_cpu_time(self):
    return self.cpu_time


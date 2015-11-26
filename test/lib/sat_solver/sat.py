import os
from process import Process
import time
from colors import *

class Sat:
  def get_result(self):
    """
    Returns the result.
    """
    return self.result

  def get_cpu_time(self):
    """
    Returns the cpu time.
    """
    return self.cpu_time

class Minisat(Sat):
  """
  Provides an easy mechanism for calling minisat with an input file.
  """

  def __init__(self, timeout):
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

    self.timeout = timeout

  def run(self, input_path):
    """
    Executes minisat and saves the result and cpu_time.
    """
    ps            = Process([self.path, input_path], self.timeout)
    ps.Run()
    out           = ps.output().split('\n')
    try:
      self.cpu_time = ((out[len(out) - 4]).split())[3]
      self.result   = out[len(out) - 2]
    except (IndexError):
      print Colors.FAIL + Colors.BOLD + 'UNEXPECTED ERROR!\n' + Colors.ENDC
      self.cpu_time = -1
      self.result   = 'UNKNOWN'

class T7_sat(Sat):
  """
  Provides an easy mechanism for calling sat_solver with an input file.
  """

  def __init__(self, timeout):
    self.path    = 'bin/sat_solver.o'
    self.timeout = timeout

  def run(self, input_path):
    """
    Executes sat_solver and saves the result and cpu_time.
    """
    ps            = Process([self.path, input_path], self.timeout)
    start_time    = time.time()
    ps.Run()
    end_time      = time.time()
    out           = ps.output().split('\n')
    self.result   = out[0]
    self.cpu_time = str(end_time - start_time)

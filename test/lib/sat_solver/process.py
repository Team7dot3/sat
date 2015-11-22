import os
from subprocess import Popen, PIPE
import sys
import threading
import time

class Process(threading.Thread):
  def __init__(self, cmd, timeout):
    threading.Thread.__init__(self)
    self.cmd     = cmd
    self.timeout = timeout

  def run(self):
    """
    Executes a program and passes to it any accompanied arguments.
    Input args must be an array with the path to the program executable in the first index.
    Returns the stdout printout of the program.
    """
    self.ps    = Popen(self.cmd, stdout=PIPE)
    (out, err) = self.ps.communicate()
    exit_code  = self.ps.wait()
    self.out   = out
    self.err   = err

  def Run(self):
    self.start()
    self.join(self.timeout)

    if self.is_alive():
      self.out = 'TIMEDOUT\n'
      self.ps.terminate()
      self.join()
      time.sleep(0.275)

  def output(self):
    return self.out

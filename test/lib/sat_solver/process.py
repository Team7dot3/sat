import os
from subprocess import Popen, PIPE
import sys
import threading
import time

class Process(threading.Thread):
  def __init__(self, cmd, timeout):
    """
    Sets up a process to execute a command. The command to execute must be an
    array containing all arguments for the command. This also sets up a timeout
    value that when reached kills the running process.

    cmd -- command and arguments as an array that is to be executed
    timeout -- the amount of time allowed for the process to run
    """
    threading.Thread.__init__(self)
    self.cmd     = cmd
    self.timeout = timeout

  def run(self):
    """
    Executes a program and passes to it any accompanied arguments.
    Input args must be an array with the path to the program executable in the first index.
    """
    self.ps    = Popen(self.cmd, stdout=PIPE)
    (out, err) = self.ps.communicate()
    exit_code  = self.ps.wait()
    self.out   = out
    self.err   = err

  def Run(self):
    """
    Starts process thread (executes run method). This blocks and forces a join 
    with the spawned thread when the timeout limit is reached.
    """
    self.start()
    self.join(self.timeout)

    if self.is_alive():
      self.out = 'TIMEDOUT\n'
      self.ps.terminate()
      self.join()

    while self.is_alive():
      print 'WTF'
      time.sleep(0.1)

  def output(self):
    """
    Returns output result from executed process.
    """
    return self.out

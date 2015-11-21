import os
from subprocess import Popen, PIPE

class Process():
  def run(self, args):
    """
    Executes a program and passes to it any accompanied arguments.
    Input args must be an array with the path to the program executable in the first index.
    Returns the stdout printout of the program.
    """
    ps         = Popen(args, stdout=PIPE)
    (out, err) = ps.communicate()
    exit_code  = ps.wait()
    return out

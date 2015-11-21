import os

class Logger:
  """
  Logger is a wrapper for a file writer. 
  """

  def __init__(self, path, delim):
    """
    Initializes the Logger with the input path.
    The input path represents the file to write log messages to.
    """
    self.log_file = open(path, 'wb')
    self.delim    = delim

  def write(self, str):
    """
    Writes the input string to the log file.
    """
    if self.delim == True:
      self.log_file.write('==============================\n\n') 
    self.log_file.write(str)
    if self.delim == True:
      self.log_file.write('\n==============================\n')
    
  def close(self):
    """
    Closes the log file. Do not call write() after calling close()!
    """
    self.log_file.close()


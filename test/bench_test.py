import os
from subprocess import Popen, PIPE
import time

ROOT_PATH = ''

def exec_process(args):
  """
  Executes a program and passes to it any accompanied arguments.
  Input args must be an array with the path to the program executable in the first index.
  Returns the stdout printout of the program.
  """
  ps         = Popen(args, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  return out

class Logger:
  """
  Logger is a wrapper for a file writer. 
  """

  def __init__(self, path):
    """
    Initializes the Logger with the input path.
    The input path represents the file to write log messages to.
    """
    self.log_file = open(path, 'wb')

  def write(self, str):
    """
    Writes the input string to the log file.
    """
    
    self.log_file.write(str)
    
    
  def close(self):
    """
    Closes the log file. Do not call write() after calling close()!
    """
    self.log_file.close()

def get_files(path):
  os.chdir(path)
  files = os.listdir(os.getcwd())
  os.chdir(ROOT_PATH)
  return files

def run_minisat_benchmarks(inputs):
  log = Logger('txt/log_minisat_benchmarks.txt')
  log.write('program \t result \t cpu_time \t input_file \n')
  for input in inputs:
    print 'RUNNING TEST ON ' + input
    
    ms_out    = exec_process([program, 'benchmarks/' + input]).split('\n')
    ms_time   = ((ms_out[len(ms_out) - 4]).split())[3]
    ms_result = ms_out[len(ms_out) - 2]

    print ms_time
    log.write('minisat \t ' + ms_result + ' \t ' + ms_time + ' \t ' + input + '\n')

def get_minisat_benchmarks():
  lines = None
  with open('txt/log_minisat_benchmarks.txt') as f:
    lines = f.read().split('\n')
      # print lines[1]
      # print (lines[1].split())[2] + '<<<'
  return lines

def run_satsolver_benchmarks(inputs):
  log = Logger('txt/log_satsolver_benchmarks.txt')
  log.write('program \t result \t cpu_time \t input_file \n')
  for input in inputs:
    print 'RUNNING TEST ON ' + input
    start_time = time.time()
    t7_out     = (exec_process(['bin/sat_solver.o', 'txt/input.txt']).split('\n'))[0]
    end_time   = time.time()
    log.write('team7 \t ' + t7_out + ' \t ' + str(end_time - start_time) + ' \t ' + input + '\n')


if __name__ == '__main__':
  ROOT_PATH = os.getcwd()
  print ROOT_PATH
  inputs = get_files('benchmarks')
  run_minisat_benchmarks(inputs)


  # get_minisat_benchmarks()

  # run_satsolver_benchmarks(inputs)

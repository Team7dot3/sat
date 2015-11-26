import os
from lib.sat_solver.process import *
from lib.sat_solver.logger import *
from lib.sat_solver.sat import *
from lib.sat_solver.opponent import *
from lib.sat_solver.colors import *
from lib.sat_solver.sat_random import *
from subprocess import Popen, PIPE
import time
import sys

ROOT_PATH   = ''
INPUT_PATH  = 'txt/diff_test.txt' # Each test file is written here
MAX_VARS    = 2000 # The maximum number of variables
MAX_CLAUSES = 2000 # The maximum number of clauses
MAX_PURES   = 0.20 # The maximum ration of pure clauses to clauses
TEST_RUNS   = 1000 # The number of tests to run

MS_TIMEOUT = 180 # Minisat Timeout Limit in seconds
T7_TIMEOUT = 300 # Team7 Timeout Limit in seconds
OP_TIMEOUT = 300 # Opponents Timeout Limit in seconds

def get_files(path):
  """
  Returns a list of all files in the path parameter.

  path -- a string representing the path to a directory containing files
  """
  os.chdir(path)
  files = os.listdir(os.getcwd())
  os.chdir(ROOT_PATH)
  return files

def run_minisat_benchmarks(inputs):
  """
  Executes Minisat on a set of input files. The results are recorded in a log file.

  inputs -- a list of strings representing paths to input files to test
  """
  ms  = Minisat(MS_TIMEOUT)

  # record results in log file
  log = Logger('txt/log_minisat_benchmarks.txt', False)
  log.write('program \t result \t cpu_time \t input_file \n')
  
  for input in inputs:
    if input == 'minisat-results.txt':
      # skip Zvonimir's benchmark result file
      continue
    print Colors.BOLD + 'RUNNING TEST ON ' + input + Colors.ENDC
    ms.run('benchmarks/' + input)
    log.write('minisat \t ' + ms.get_result() + ' \t ' + ms.get_cpu_time() + ' \t ' + input + '\n')

def get_minisat_benchmarks():
  """
  Fetches Minisat benchmark results from text file. Returns results as an array.

  raises IOError if 'txt/minisat_benchmarks' does not exist
  """
  lines = None
  with open('txt/minisat_benchmarks') as f:
    lines = f.read().split('\n')
  return lines

def run_satsolver_benchmarks(inputs):
  """
  Executes the Team7 SAT Solver on a set of input files. The results are recorded
  in a log file.

  inputs -- a list of strings representing input files to test against
  """
  t7  = T7_sat(T7_TIMEOUT)
  log = Logger('txt/log_satsolver_benchmarks.txt', False)
  log.write('program \t result \t cpu_time \t input_file \n')
  for input in inputs:
    print 'RUNNING MINISAT TEST ON ' + input
    t7.run('benchmarks/' + input)
    log.write('team7 \t ' + t7.get_result() + ' \t ' + t7.get_cpu_time() + ' \t ' + input + '\n')

def run_opponents_benchmarks(inputs):
  """
  Exeuctes Minisat, Team7, and Opponents SAT Solver on a set of input files.
  Each output is verified against Minisat's output. The results are recorded
  in a log file.

  inputs -- a list of strings representing input files to test against
  """
  ms   = Minisat(MS_TIMEOUT)
  t7   = T7_sat(T7_TIMEOUT)
  log  = Logger('txt/log_opponents_benchmarks.txt', False)
  opps = Opponent.setup_opponents(os.getcwd(), OP_TIMEOUT)
  for op in opps:
    print Colors.BOLD + op.name + Colors.ENDC
    
    if not os.path.isdir(op.clone_path):
      op.clone()
      op.build()
    if '--b' in sys.argv:
      # command line argument to clone, pull, build opponents source code
      if not os.path.isdir(op.clone_path):
        op.clone()
      op.fetch()
      op.pull()
      op.build()

  if inputs:
    # test against the set of received input files

    log.write('ms_result \t ms_cpu_time \t ' + opps[0].name + ' \t ' + opps[1].name + ' \t ' + opps[2].name + ' \t ' + opps[3].name + ' \t ' + 'Team7' + ' \t benchmark \n')
    ms_results = get_minisat_benchmarks()
    for m in ms_results:
      tokens = m.split()
      if tokens[-1] == 'input_file':
        # skip column header
        continue

      print Colors.BOLD + 'benchmarks/' + tokens[-1]
      
      # execute our SAT Solver
      t7.run('benchmarks/' + tokens[-1])

      # lists to store results
      results     = []
      times       = []
      to_log_file = []
      for op in opps:
        # execute our Opponents' SAT Solver
        start_time = time.time()
        res        = op.run('benchmarks/' + tokens[-1])
        end_time   = time.time()
        results.append(res)
        times.append(end_time - start_time)
      
      # Check Opponents' results
      for i in range(0, len(opps)):
        if tokens[1] == results[i]:
          to_log_file.append(times[i])
        elif 'ERROR' not in results[i]:
          if times[-1] < OP_TIMEOUT:
            to_log_file.append('CRASHED')
          else:
            to_log_file.append('TIMEDOUT')
        else:
          to_log_file.append('FAILED')

      # Check Team7's sat_solver results
      if tokens[1] == t7.get_result():
        to_log_file.append(t7.get_cpu_time())
      elif 'ERROR' not in t7.get_result():
        if t7.get_cpu_time() < T7_TIMEOUT:
          to_log_file.append('CRASHED')
        else:
          to_log_file.append('TIMEDOUT')
      else:
        print t7.get_result()
        to_log_file.append('FAILED')

      # record results to log file
      to_log_file.append(tokens[-1])
      print Colors.BOLD + tokens[2] + Colors.ENDC
      print to_log_file
      log.write(tokens[1] + ' \t ' + tokens[2] + ' \t ' + str(to_log_file[0]) + ' \t ' + str(to_log_file[1]) + ' \t ' + str(to_log_file[2]) + ' \t' + str(to_log_file[3]) + ' \t ' + str(to_log_file[4]) +' \t ' + str(to_log_file[5]) + '\n')

  else:
    # test against randomly generated input files

    log.write('ms_result \t ms_cpu_time \t ' + opps[0].name + ' \t ' + opps[1].name + ' \t ' + opps[2].name + ' \t ' + opps[3].name + ' \t ' + 'Team7' + ' \t nbvars \t nbclauses \n')
    rt = RandomTesting(INPUT_PATH, MAX_VARS, MAX_CLAUSES, MAX_PURES, TEST_RUNS, MS_TIMEOUT, T7_TIMEOUT)
    for i in range(0, TEST_RUNS):
      rt.gen_rand_input()

      # execute Minisat and Team7 SAT Solvers
      ms.run(INPUT_PATH)
      t7.run(INPUT_PATH)
      
      # lists to store results
      results     = []
      times       = []
      to_log_file = []
      for op in opps:
        # execute our Opponents' SAT Solver
        start_time = time.time()
        res        = op.run(INPUT_PATH)
        end_time   = time.time()
        results.append(res)
        times.append(end_time - start_time)

      # Check Opponents' results
      for i in range(0, len(opps)):
        if ms.get_result() == results[i]:
          to_log_file.append(times[i])
        elif 'ERROR' not in results[i]:
          if times[-1] < OP_TIMEOUT:
            to_log_file.append('CRASHED')  
          else:
            to_log_file.append('TIMEDOUT')
        else:
          to_log_file.append('FAILED')

      # Check Team7's sat_solver results
      if ms.get_result() == t7.get_result():
        to_log_file.append(t7.get_cpu_time())
      elif 'ERROR' not in t7.get_result():
        if t7.get_cpu_time() < T7_TIMEOUT:
          to_log_file.append('CRASHED')
        else:
          to_log_file.append('TIMEDOUT')
      else:
        to_log_file.append('FAILED')

      # record results to log file
      to_log_file.append(rt.nbvars)
      to_log_file.append(rt.nbclauses)
      print Colors.BOLD + ms.get_cpu_time() + Colors.ENDC
      print to_log_file
      log.write(ms.get_result() + ' \t ' + ms.get_cpu_time() + ' \t ' + str(to_log_file[0]) + ' \t ' + str(to_log_file[1]) + ' \t ' + str(to_log_file[2]) + ' \t' + str(to_log_file[3]) + ' \t ' + str(to_log_file[4]) +' \t ' + str(to_log_file[5]) +' \t ' + str(to_log_file[6]) + '\n')

    # close the log file
    log.close()

if __name__ == '__main__':
  ROOT_PATH = os.getcwd()
  inputs = get_files('benchmarks')

  if '--minisat' in sys.argv:
    run_minisat_benchmarks(inputs)

  if '--t7' in sys.argv:
    run_satsolver_benchmarks(inputs)  

  if '--opponents' in sys.argv:
    if '--random' in sys.argv:
      run_opponents_benchmarks(None)
    else:
      run_opponents_benchmarks(inputs)

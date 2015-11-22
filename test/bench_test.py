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
INPUT_PATH  = 'txt/diff_test.txt'
MAX_VARS    = 100   # The maximum number of variables
MAX_CLAUSES = 1000 # The maximum number of clauses
MAX_PURES   = 0.20 # The maximum ration of pure clauses to clauses
TEST_RUNS   = 1000 # The number of tests to run

def get_files(path):
  os.chdir(path)
  files = os.listdir(os.getcwd())
  os.chdir(ROOT_PATH)
  return files

def run_minisat_benchmarks(inputs):
  ms  = Minisat()
  log = Logger('txt/log_minisat_benchmarks.txt', False)
  log.write('program \t result \t cpu_time \t input_file \n')
  for input in inputs:
    if input == 'minisat-results.txt':
      continue
    print 'RUNNING TEST ON ' + input
    ms.run('benchmarks/' + input)
    log.write('minisat \t ' + ms.get_result() + ' \t ' + ms.get_cpu_time() + ' \t ' + input + '\n')

def get_minisat_benchmarks():
  lines = None
  with open('txt/minisat_benchmarks') as f:
    lines = f.read().split('\n')
    # print lines[1]
    # print (lines[1].split())[2] + '<<<'
  return lines

def run_satsolver_benchmarks(inputs):
  t7  = T7_sat()
  log = Logger('txt/log_satsolver_benchmarks.txt', False)
  log.write('program \t result \t cpu_time \t input_file \n')
  for input in inputs:
    print 'RUNNING TEST ON ' + input
    t7.run('benchmarks/' + input)
    log.write('team7 \t ' + t7.get_result() + ' \t ' + t7.get_cpu_time() + ' \t ' + input + '\n')

def run_opponents_benchmarks(inputs):
  ms   = Minisat()
  t7   = T7_sat()
  log  = Logger('txt/log_opponents_benchmarks.txt', False)
  opps = Opponent.setup_opponents(os.getcwd())
  for op in opps:
    print Colors.BOLD + op.name + Colors.ENDC
    if '--b' in sys.argv:
      if not os.path.isdir(op.clone_path):
        op.clone()
      op.fetch()
      op.pull()
      op.build()

  if inputs:
    log.write('ms_result \t ms_cpu_time \t ' + opps[0].name + ' \t ' + opps[1].name + ' \t ' + opps[2].name + ' \t ' + opps[3].name + ' \t ' + 'Team7' + ' \t benchmark \n')
    ms_results = get_minisat_benchmarks()
    for m in ms_results:
      tokens = m.split()
      if tokens[-1] == 'input_file':
        # skip column header
        continue

      print Colors.BOLD + 'benchmarks/' + tokens[-1]
      t7.run('benchmarks/' + m[-1])

      # Save results to lists
      results     = []
      times       = []
      to_log_file = []
      for op in opps:
        start_time = time.time()
        res        = op.run('benchmarks/' + tokens[-1])
        end_time   = time.time()
        results.append(res)
        times.append(end_time - start_time)
      
      # Check Opponents' results
      for i in range(0, len(opps)):
        if tokens[1] == results[i]:
          to_log_file.append(times[i])
        else:
          to_log_file.append('FAILED')

      # Check Team7's sat_solver results
      if tokens[1] == t7.get_result():
        to_log_file.append(t7.get_cpu_time())
      else:
        to_log_file.append('FAILED')

      to_log_file.append(tokens[-1])
      print to_log_file
      log.write(tokens[1] + ' \t ' + tokens[2] + ' \t ' + str(to_log_file[0]) + ' \t ' + str(to_log_file[1]) + ' \t ' + str(to_log_file[2]) + ' \t' + str(to_log_file[3]) + ' \t ' + str(to_log_file[4]) +' \t ' + str(to_log_file[5]) + '\n')

  else:
    log.write('ms_result \t ms_cpu_time \t ' + opps[0].name + ' \t ' + opps[1].name + ' \t ' + opps[2].name + ' \t ' + opps[3].name + ' \t ' + 'Team7' + ' \t nbvars \t nbclauses \n')
    rt = RandomTesting(INPUT_PATH, MAX_VARS, MAX_CLAUSES, MAX_PURES, TEST_RUNS)
    for i in range(0, TEST_RUNS):
      rt.gen_rand_input()
      ms.run(INPUT_PATH)
      t7.run(INPUT_PATH)
      
      # Save results to lists
      results     = []
      times       = []
      to_log_file = []
      for op in opps:
        start_time = time.time()
        res        = op.run(INPUT_PATH)
        end_time   = time.time()
        results.append(res)
        times.append(end_time - start_time)

      # Check Opponents' results
      for i in range(0, len(opps)):
        if ms.get_result() == results[i]:
          to_log_file.append(times[i])
        else:
          to_log_file.append('FAILED')

      # Check Team7's sat_solver results
      if ms.get_result() == t7.get_result():
        to_log_file.append(t7.get_cpu_time())
      else:
        to_log_file.append('FAILED')

      to_log_file.append(rt.nbvars)
      to_log_file.append(rt.nbclauses)
      print to_log_file
      log.write(ms.get_result() + ' \t ' + ms.get_cpu_time() + ' \t ' + str(to_log_file[0]) + ' \t ' + str(to_log_file[1]) + ' \t ' + str(to_log_file[2]) + ' \t' + str(to_log_file[3]) + ' \t ' + str(to_log_file[4]) +' \t ' + str(to_log_file[5]) +' \t ' + str(to_log_file[6]) + '\n')

    log.close()

if __name__ == '__main__':
  ROOT_PATH = os.getcwd()
  print ROOT_PATH
  print str(sys.argv)

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

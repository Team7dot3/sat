import random
import sys
import re 
import os
from subprocess import Popen, PIPE
import time

MAX_INT = 32767

# returns the output of a process
def exec_process(args):
  ps         = Popen(args, stdout=PIPE)
  (out, err) = ps.communicate()
  exit_code  = ps.wait()
  return out

def init_random():
  NOW = time.time()
  random.seed(NOW)


class Logger:
  def __init__(self, path):
    self.log_file = open(path, 'wb')

  def write(self, str):
    self.log_file.write('==============================\n\n')
    self.log_file.write(str)
    self.log_file.write('\n==============================\n')
    
  def close(self):
    self.log_file.close()


class Minisat:
  def __init__(self, path):
    self.path = path

  def run(self):
    return exec_process(['minisat', self.path])


class Sat:
  def __init__(self, path):
    self.path = path

  def run(self):
    return exec_process(['bin/sat_solver.o', self.path])


class RandomTesting:
  def __init__(self, path, max_num, itrs):
    self.path = path
    self.max  = max_num
    self.itrs = itrs

  def gen_rand_input(self):
    self.nbvars    = random.randint(1, self.max)
    self.nbclauses = random.randint(1, self.max)

    with open(self.path, 'wb') as f:
      f.write('p cnf ' + str(self.nbvars) + ' ' + str(self.nbclauses) + ' \n')
      
      for i in range(0, self.nbclauses):
        for j in range(0, random.randint(1, self.nbvars)):
          if random.randint(0, MAX_INT) % 2 == 0:
            f.write('-')
          f.write(str(random.randint(1, self.nbvars)) + ' ')
        f.write('0 \n')

  def run(self):
    log    = Logger('txt/log_diff_test.txt')
    passed = 0

    for i in range(0, self.itrs):
      self.gen_rand_input()
      prev_pass = passed
      passed   += self.test()
      if prev_pass == passed:
        input_file  = None
        with open(self.path, 'r') as f:
          input_file = f.read()
        log.write('Test FAILED with input:\n' + input_file)

    log.close()
    return passed

  def test(self):
    ms_out    = Minisat(self.path).run().split('\n')
    ms_result = ms_out[len(ms_out) - 2] + '\n'
    t7_out    = Sat(self.path).run()
    
    if ms_result == t7_out:
      return 1
    else:
      return 0


if __name__ == '__main__':
  init_random()
  max_var   = 100
  test_runs = 100
  passed    = RandomTesting('txt/diff_test.txt', max_var, test_runs).run()

  print '\n\n\nDifferential Testing:'
  print '  PASSED: ' + str(passed)
  print '  FAILED: ' + str(test_runs - passed)

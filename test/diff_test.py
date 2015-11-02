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
  print out
  return out

def init_random():
  NOW = time.time()
  random.seed(NOW)

class Minisat():
  def __init__(self, path):
    self.path = path

  def run(self):
    exec_process(['minisat', self.path])

class RandomTesting:
  def __init__(self, path, max):
    self.path = path
    self.max = max

  def gen_rand_input(self):
    self.nbvars = random.randint(1, self.max)
    self.nbclauses = random.randint(1, self.max)
    with open(self.path, 'wb') as f:
      f.write('p cnf ' + str(self.nbvars) + ' ' + str(self.nbclauses) + ' \n')
      for i in range(0, self.nbclauses):
        for j in range(0, random.randint(1, self.max)):
          if random.randint(0, MAX_INT) % 2 == 0:
            f.write('-')
          b = random.randint(1, self.max)
          f.write(str(b) + ' ')
        f.write('0 \n')

  def run(self):
    Minisat(self.path).run()

if __name__ == '__main__':
  init_random()
  rt = RandomTesting('../txt/diff_test.txt', 10)
  rt.gen_rand_input()
  rt.run()


# C UNIT Tests

These Unit Tests, written in C, test basic functionality of the SAT Solver. The tests are separated into 3 groups:

- Argument Checking
- Input Parsing
- Solver (Algorithm Output)

The Unit Tests do not cover End to End tests, that was saved for the Randomized Differential Tests.

## To Run C UNIT Tests

From the project's root directory, execute:

```
make testrun
```

# Python Randomized Differential Tests

The tests created with Python expose the End to End functionality of the SAT Solver. The output of each test is compared to the output of `MINISAT`. If the output results vary, the test fails.

The primary tests we run are from `diff_test.py`. Diff test produces random inputs with variable and clause values capped by variables `MAX_VARS` and `MAX_CLAUSES` respectively. The number of inputs and tests executed by Diff test is capped by the variable `TEST_RUNS`. You can modify these variables to customize the size of each test input.

IMPORTANT: All Python tests are expected to be executed from the project's root directory!

## To Run Diff Tests

From the project's root directory, execute:

```
python test/diff_test.py
```
or
```
make diff_tests
```

## Diff Test Output

The output prints the number of how many variables and clauses were produced for each test, and whether the test passed or failed. Diff Test does not save the input of failed tests. Only the last test input file is saved (and written over on each test run)

A typical output looks like this:
```
Differential Testing:
  Test # [1]  nbvars = 137  nbclauses = 893  P
  Test # [2]  nbvars = 38   nbclauses = 966  P
  Test # [3]  nbvars = 61   nbclauses = 143  P
  Test # [4]  nbvars = 88   nbclauses = 886  P
  Test # [5]  nbvars = 46   nbclauses = 578  P
  Test # [6]  nbvars = 118  nbclauses = 718  P
  Test # [7]  nbvars = 57   nbclauses = 142  P
  Test # [8]  nbvars = 90   nbclauses = 737  P
  Test # [9]  nbvars = 45   nbclauses = 552  P
  Test # [10] nbvars = 2    nbclauses = 155  P



Differential Testing:
  PASSED: 10
  FAILED: 0
```

# Testing for CS 5959 Course Competition

We wanted to see, throughout development, where each team ranked in our class competition. To do so, the `cmp_test.py` and `bench_test.py` were designed to run each teams solution and measure the cpu time required to obtain each output. There are 2 ways to compare outputs between each team:

- cmp_test.py
- bench_test.py

The `cmp_test.py` runs a single input against each teams' solver.
The `bench_test.py` runs multiple inputs against each teams' solver.

IMPORTANT: You must invoke the `--b` argument to either script! This will tell the scripts to clone each teams' repository and compile their source. Here are other command line arguments:

```
cmp_test.py

--b                 # clones, fetches, pulls teams repositories and compiles source code
--some_input_file   # the path for input file to test with
```

Examples:

```
python test/cmp_test.py --b --benchmarks/38bits_10.dimacs.cnf
python test/cmp_test.py --benchmarks/38bits_10.dimacs.cnf
```

```
bench_test.py

--b                 # clones, fetches, pulls teams repositories and compiles source
--minisat           # runs only the minisat benchmarks
--t7                # runs only our team's SAT Solver on the benchmarks
--opponents         # runs opponents and our SAT Solvers on the benchmarks
--random            # user with --opponents, runs our randomized inputs on SAT Solvers
```

Examples:
```
python test/bench_test.py --minisat
python test/bench_test.py --t7
python test/bench_test.py --b --opponents
python test/bench_test.py --b --opponents --random
python test/bench_test.py --opponents --random
python test/bench_test.py --opponents
```


IMPORTANT: in order to run the Python tests you must be able to run MINISAT with one of the following:

```
minisat txt/some_input_file.txt

extras/minisat/core/minisat txt/some_input_file.txt
```

# Log Files

Various tests produce log files saved in the txt directory located in the project's root directory.

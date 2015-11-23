TESTING
=====================================

This directory contains two types of testing: UNIT and Randomized Differential Testing.
The UNIT tests are simple unit tests for the core functions in the SAT solver implementation.
The Randomized Differential Tests (RDT) generates random text files and compares our SAT solver output to the output of MINISAT. The number of variables and clauses for the RDT can be manually altered by modifying the variable `MAX_VARS` in the `diff_test.py` file. The RDT produces can produce thousands of randomized tests. To set the number of tests to execute, manually modify the variable `TEST_RUNS` in `diff_test.py`.

```
MAX_VARS   = 40     # The maximum number of variables and clauses
TEST_RUNS  = 100000 # The number of tests to run
```

# To Run UNIT Tests:

From the project's root directory, execute:

```
make testrun
```

# To Run Randomized Differential Tests (RDT):

From the project's root directory, execute:

```
make diff_test
```

Please note, in order to run the RDT you must be able to run MINISAT with one of the following:

```
minisat txt/some_input_file.txt

extras/minisat/core/minisat txt/some_input_file.txt
```

SAT Solver
=====================================

This program solves the Boolean Satisfiability (SAT) problem using the DPLL algorithm.
Inputs are expected to be in the DIMACS format. All other inputs are ignored.

# To Compile

The Makefile includes various commands for compiling the source code. 

```
make           # cleans and compiles the source
make solve     # cleans, compiles, and runs executable with 'txt/input.txt'
make debug     # cleans, compiles the source with DEBUG/LOG mode
make test      # cleans and compiles the source with testing code
make testrun   # cleans, compiles source with tests, and runs the executable against 'bin/unit_txt.0'
make diff_test # cleans, compiles, and runs executable with generated tests and compares output with minisat
make rebuild   # cleans and rebuilds the project
make clean     # removes executables, and temporary files
```

# To Run

Binaries will be located in the 'bin' directory and .txt input files will be located in the 'txt' directory. To run SAT, execute the following:

```
bin/sat_solver.o txt/input.txt
```

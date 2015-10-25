SAT Solver
=====================================

This program solves the Boolean Satisfiability (SAT) problem using the DPLL algorithm.
Inputs are expected to be in the DIMACS format. All other inputs are ignored.

# To Compile

The Makefile includes various commands for compiling the source code. 

```
make        # cleans, compiles, and runs the program with input 'txt/input.txt'
make debug  # cleans, compiles, and runs the program in DEBUG or LOG mode
make sat    # compiles source
make sat_d  # compiles source in DEBUG or LOG mode
make solve  # runs executable with 'txt/input.txt'
make clean  # removes executables, and temporary files
```

# To Run

Binaries will be located in the 'bin' directory and .txt input files will be located in the 'txt' directory. To run SAT, execute the following:

```
bin/sat_solver.o txt/input.txt
```

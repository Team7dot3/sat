#ifndef UNITS_H
#define UNITS_H

// C libraries
#include <stdio.h>

// Unit Tests
#include "unit_test_check_args.h"
#include "unit_test_input_parser.h"
#include "unit_test_solve.h"

// SAT data types and macros
#include "../src/sat_types.h"

int EXP;
int ACT;
int RES;

#define DELIM "\n==================================================\n"
#define NL "\n"

#define RESULT(str, passed) { \
  if (passed) {               \
    PASS(str);                \
  } else {                    \
    FAIL(str);                \
  }                           \
}

#define PASS(str) {                 \
  printf("  ");                     \
  printf(str);                      \
  printf(KGRN " PASSED. \n" RESET); \
  return (RES = 0);                 \
}

#define FAIL(str) {              \
  printf(RESET "  ");            \
  printf(str);                   \
  printf(KRED  " FAILED. ");     \
  printf(RESET "\t Expected: "); \
  printf(KGRN  "%d", EXP);       \
  printf(RESET "\t Actual: ");   \
  printf(KRED  "%d \n", ACT);    \
  return (RES = 1);              \
}

#endif

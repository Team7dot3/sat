#ifndef UNITS_H
#define UNITS_H

// C libraries
#include <stdio.h>
#include <setjmp.h>

// Unit Tests
#include "unit_test_check_args.h"
#include "unit_test_input_parser.h"
#include "unit_test_solve.h"

int EXP;
int ACT;
int RES;

#define GEN_STRUCTS(void) \
  INPUT in;               \
  in.nbvars    = 0;       \
  in.nbclauses = 0;

#define FREE_STRUCTS(in)   \
{                          \
  free(in.data);           \
  free(in.clause_lengths); \
}

#define DELIM "\n==================================================\n"
#define NL "\n"

#define RESULT(str, passed)   \
{                             \
  if (passed)                 \
  {                           \
    PASS(str);                \
  }                           \
  else                        \
  {                           \
    FAIL(str);                \
  }                           \
}

#define PASS(str) {                   \
  printf(RESET "  ");                 \
  printf(str);                        \
  printf(KGRN "\t PASSED. \n" RESET); \
  return (RES = 0);                   \
}

#define FAIL(str) {              \
  printf(KRED "  ");             \
  printf(str);                   \
  printf(KRED  "\t FAILED. ");   \
  printf(RESET "   Expected: "); \
  printf(KGRN  "%d", EXP);       \
  printf(RESET "   Actual: ");   \
  printf(KRED  "%d \n", ACT);    \
  return (RES = 1);              \
}

#endif

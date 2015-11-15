#include "units.h"
#include "../src/sat_types.h"

#define TEST_SOLVE(is_sat, test_num) \
  GEN_STRUCTS();                     \
  if (is_sat)                        \
  {                                  \
    switch (test_num)                \
    {                                \
      case 1:                        \
        setup_basic_sat_1(&in);      \
        break;                       \
      case 2:                        \
        setup_basic_sat_2(&in);      \
        break;                       \
      case 3:                        \
        setup_basic_sat_3(&in);      \
        break;                       \
      case 4:                        \
        setup_sat_4(&in);            \
        break;                       \
      default:                       \
        NULL;                        \
    }                                \
  }                                  \
  else                               \
  {                                  \
    switch (test_num)                \
    {                                \
      case 1:                        \
        setup_basic_unsat_1(&in);    \
        break;                       \
      case 2:                        \
        setup_basic_unsat_2(&in);    \
        break;                       \
      case 3:                        \
        setup_unsat_3(&in);          \
        break;                       \
      case 4:                        \
        setup_unsat_4(&in);          \
        break;                       \
      default:                       \
        NULL;                        \
    }                                \
  }                                  \
  ACT = solve(&in);           \
  FREE_STRUCTS(in);

int test_basic_sat_1(void);
int test_basic_sat_2(void);
int test_basic_sat_3(void);
int test_sat_4(void);
int test_basic_unsat_1(void);
int test_solver(void);

void setup_basic_sat_1(UNMOLESTED_INPUT *in);
void setup_basic_sat_2(UNMOLESTED_INPUT *in);
void setup_basic_sat_3(UNMOLESTED_INPUT *in);
void setup_sat_4(UNMOLESTED_INPUT *in);
void setup_basic_unsat_1(UNMOLESTED_INPUT *in);
void setup_basic_unsat_2(UNMOLESTED_INPUT *in);
void setup_unsat_3(UNMOLESTED_INPUT *in);
void setup_unsat_4(UNMOLESTED_INPUT *in);

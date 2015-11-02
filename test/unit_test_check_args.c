#include "unit_test_check_args.h"

int test_not_enough_args_1(void) 
{
  RESULT("test_not_enough_args_1", (EXP = 0) == (ACT = (int)check_args(0, NULL)));
}

int test_not_enough_args_2(void) 
{
  RESULT("test_not_enough_args_2", (EXP = 0) == (ACT = (int)check_args(1, NULL)));
}

int test_too_many_args(void) 
{
  RESULT("test_too_many_args_1", (EXP = 0) == (ACT = (int)check_args(3, NULL)));
}

int test_invalid_path_1(void) 
{
  char s1[]   = "program";
  char s2[]   = "invalid.txt"; 
  char *arr[] = { s1, s2 };
  RESULT("test_invalid_path_1", (EXP = 0) == (ACT = (int)check_args(2, arr)));
}

int test_invalid_path_2(void) 
{
  char s1[]   = "program";
  char s2[]   = "txt/input"; 
  char *arr[] = { s1, s2 };
  RESULT("test_invalid_path_2", (EXP = 0) == (ACT = (int)check_args(2, arr)));
}

int test_invalid_path_3(void) 
{
  char s1[]   = "program";
  char s2[]   = "mm@#!?(*\\m"; 
  char *arr[] = { s1, s2 };
  RESULT("test_invalid_path_3", (EXP = 0) == (ACT = (int)check_args(2, arr)));
}

int test_null_path(void) 
{
  char s1[]   = "program";
  char *arr[] = { s1, NULL };
  RESULT("test_invalid_path_3", (EXP = 0) == (ACT = (int)check_args(2, arr)));
}

int test_valid_path() 
{
  char s1[]   = "program";
  char s2[]   = "txt/basic_sat_input.txt";
  char *arr[] = { s1, s2 };
  RESULT("test_valid_path", (EXP = 0) != (ACT = (int)check_args(2, arr)));
}

int test_check_args(void) 
{
  int fails = 0;
  
  LOG("TEST CHECK ARGS", 1);
  fails += test_not_enough_args_1();
  fails += test_not_enough_args_1();
  fails += test_too_many_args();
  fails += test_invalid_path_1();
  fails += test_invalid_path_2();
  fails += test_invalid_path_3();
  fails += test_null_path();
  fails += test_valid_path();

  return fails;
}

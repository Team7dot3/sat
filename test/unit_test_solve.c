#include "unit_test_solve.h"

int test_basic_sat_1(void)
{
  TEST_SOLVE(1, 1); 
  RESULT("test_basic_sat_1      ", (EXP = 1) == ACT);
}

int test_basic_sat_2(void)
{
  TEST_SOLVE(1, 2);
  RESULT("test_basic_sat_2      ", (EXP = 1) == ACT);
}

int test_basic_sat_3(void)
{
  TEST_SOLVE(1, 3);
  RESULT("test_basic_sat_3      ", (EXP = 1) == ACT);
}

int test_sat_4(void)
{
  TEST_SOLVE(1, 4);
  RESULT("test_sat_4            ", (EXP = 1) == ACT);
}

int test_basic_unsat_1(void)
{
  TEST_SOLVE(0, 1);
  RESULT("test_basic_unsat_1    ", (EXP = 0) == ACT);
}

int test_basic_unsat_2(void)
{
  TEST_SOLVE(0, 2);
  RESULT("test_basic_unsat_2    ", (EXP = 0) == ACT); 
}

int test_unsat_3(void)
{
  TEST_SOLVE(0, 3);
  RESULT("test_unsat_3          ", (EXP = 0) == ACT);  
}

int test_unsat_4(void)
{
  TEST_SOLVE(0, 4);
  RESULT("test_unsat_4          ", (EXP = 0) == ACT);   
}

int test_solver(void) 
{
  int fails = 0;

  LOG("TEST SOLVE", 1);

  fails += test_basic_sat_1();
  fails += test_basic_sat_2();
  fails += test_basic_sat_3();
  fails += test_sat_4();
  fails += test_basic_unsat_1();
  fails += test_basic_unsat_2();
  fails += test_unsat_3();
  fails += test_unsat_4();

  return fails;
}

void setup_basic_sat_1(INPUT *in) 
{
  int nbvars, nbclauses;

  nbvars = 2;
  nbclauses = 1;

  // (1 || 2)
  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * nbvars);
  in->data[0][0] = 1;
  in->data[0][1] = 2;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 2;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_basic_sat_2(INPUT *in) 
{
  int nbvars, nbclauses;

  nbvars = 2;
  nbclauses = 1;

  // (1 || -1)
  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * nbvars);
  in->data[0][0] = 1;
  in->data[0][1] = -1;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 2;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_basic_sat_3(INPUT *in) 
{
  int nbvars, nbclauses;

  nbvars = 5;
  nbclauses = 5;

  // (1 || -2 || -3) && (-1 || -2 || 3) && (4 || 5) && (-4 || 5) && (-1 || -2 || 3 || 4 || 5)
  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * 3);
  in->data[1] = (int *)malloc(sizeof(int) * 3);
  in->data[2] = (int *)malloc(sizeof(int) * 2);
  in->data[3] = (int *)malloc(sizeof(int) * 2);
  in->data[4] = (int *)malloc(sizeof(int) * 5);

  // (1 || -2 || -3)
  in->data[0][0] =  1;
  in->data[0][1] = -2;
  in->data[0][2] = -3;

  // (-1 || -2 || 3)
  in->data[1][0] = -1;
  in->data[1][1] = -2;
  in->data[1][2] =  3;

  // (4 || 5)
  in->data[2][0] =  4;
  in->data[2][1] =  5;

  // (-4 || 5)
  in->data[3][0] = -4;
  in->data[3][1] =  5;

  // (-1 || -2 || 3 || 4 || 5)
  in->data[4][0] = -1;
  in->data[4][1] = -2;
  in->data[4][2] =  3;
  in->data[4][3] =  4;
  in->data[4][4] =  5;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 3;
  in->clause_lengths[1] = 3;
  in->clause_lengths[2] = 2;
  in->clause_lengths[3] = 2;
  in->clause_lengths[4] = 5;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_sat_4(INPUT *in)
{
  int nbvars, nbclauses; 

  nbvars = 6;
  nbclauses = 10;

  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * 1);
  in->data[1] = (int *)malloc(sizeof(int) * 3);
  in->data[2] = (int *)malloc(sizeof(int) * 1);
  in->data[3] = (int *)malloc(sizeof(int) * 3);
  in->data[4] = (int *)malloc(sizeof(int) * 5);
  in->data[5] = (int *)malloc(sizeof(int) * 4);
  in->data[6] = (int *)malloc(sizeof(int) * 3);
  in->data[7] = (int *)malloc(sizeof(int) * 2);
  in->data[8] = (int *)malloc(sizeof(int) * 5);
  in->data[9] = (int *)malloc(sizeof(int) * 1);

  in->data[0][0] = -2;

  in->data[1][0] = -1;
  in->data[1][1] = -6;
  in->data[1][2] = -4;

  in->data[2][0] = -6;

  in->data[3][0] =  4;
  in->data[3][1] =  5;
  in->data[3][2] = -2;

  in->data[4][0] = -5;
  in->data[4][1] = -2;
  in->data[4][2] =  6;
  in->data[4][3] = -4;
  in->data[4][4] = -6;

  in->data[5][0] =  3;
  in->data[5][1] = -6;
  in->data[5][2] = -2;
  in->data[5][3] =  1;

  in->data[6][0] = -5;
  in->data[6][1] =  4;
  in->data[6][2] = -3;

  in->data[7][0] = -4;
  in->data[7][1] =  4;

  in->data[8][0] =  3;
  in->data[8][1] = -4;
  in->data[8][2] =  6;
  in->data[8][3] = -6;
  in->data[8][4] = -1;

  in->data[9][0] = -2;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 1;
  in->clause_lengths[1] = 3;
  in->clause_lengths[2] = 1;
  in->clause_lengths[3] = 3;
  in->clause_lengths[4] = 5;
  in->clause_lengths[5] = 4;
  in->clause_lengths[6] = 3;
  in->clause_lengths[7] = 2;
  in->clause_lengths[8] = 5;
  in->clause_lengths[9] = 1;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_basic_unsat_1(INPUT *in) 
{
  int nbvars, nbclauses;

  nbvars = 1;
  nbclauses = 2;

  // (1) && (-1)
  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * nbvars);
  in->data[1] = (int *)malloc(sizeof(int) * nbvars);
  in->data[0][0] = 1;
  in->data[1][0] = -1;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 1;
  in->clause_lengths[1] = 1;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_basic_unsat_2(INPUT *in) 
{
  int nbvars, nbclauses;
  
  nbvars = 5;
  nbclauses = 6;

  // (1 || 2) && (-1 || 2) && (-3 || -2) && (-2 || 3 || 4) && (-2 || 3 || 5) && (-2 || 3 || -4 || -5)
  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * 2);
  in->data[1] = (int *)malloc(sizeof(int) * 2);
  in->data[2] = (int *)malloc(sizeof(int) * 2);
  in->data[3] = (int *)malloc(sizeof(int) * 3);
  in->data[4] = (int *)malloc(sizeof(int) * 3);
  in->data[5] = (int *)malloc(sizeof(int) * 4);

  // (1 || 2)
  in->data[0][0] =  1;
  in->data[0][1] =  2;

  // (-1 || 2)
  in->data[1][0] = -1;
  in->data[1][1] =  2;

  // (-3 || -2)
  in->data[2][0] = -3;
  in->data[2][1] = -2;

  // (-2 || 3 || 4)
  in->data[3][0] = -2;
  in->data[3][1] =  3;
  in->data[3][2] =  4;

  // (-2 || 3 || 5)
  in->data[4][0] = -2;
  in->data[4][1] =  3;
  in->data[4][2] =  5;

  // (-2 || 3 || -4 || -5)
  in->data[5][0] = -2;
  in->data[5][1] =  3;
  in->data[5][2] = -4;
  in->data[5][3] = -5;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 2;
  in->clause_lengths[1] = 2;
  in->clause_lengths[2] = 2;
  in->clause_lengths[3] = 3;
  in->clause_lengths[4] = 3;
  in->clause_lengths[5] = 4;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_unsat_3(INPUT *in)
{
  int nbvars, nbclauses; 

  nbvars = 6;
  nbclauses = 10;

  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int) * 1);
  in->data[1] = (int *)malloc(sizeof(int) * 3);
  in->data[2] = (int *)malloc(sizeof(int) * 1);
  in->data[3] = (int *)malloc(sizeof(int) * 3);
  in->data[4] = (int *)malloc(sizeof(int) * 5);
  in->data[5] = (int *)malloc(sizeof(int) * 4);
  in->data[6] = (int *)malloc(sizeof(int) * 3);
  in->data[7] = (int *)malloc(sizeof(int) * 2);
  in->data[8] = (int *)malloc(sizeof(int) * 5);
  in->data[9] = (int *)malloc(sizeof(int) * 1);

  in->data[0][0] = -2;

  in->data[1][0] = -1;
  in->data[1][1] = -6;
  in->data[1][2] = -4;

  in->data[2][0] = -6;

  in->data[3][0] =  4;
  in->data[3][1] =  5;
  in->data[3][2] = -2;

  in->data[4][0] = -5;
  in->data[4][1] = -2;
  in->data[4][2] =  6;
  in->data[4][3] = -4;
  in->data[4][4] = -6;

  in->data[5][0] =  3;
  in->data[5][1] = -6;
  in->data[5][2] = -2;
  in->data[5][3] =  1;

  in->data[6][0] = -5;
  in->data[6][1] =  4;
  in->data[6][2] = -3;

  in->data[7][0] = -4;
  in->data[7][1] =  4;

  in->data[8][0] =  3;
  in->data[8][1] = -4;
  in->data[8][2] =  6;
  in->data[8][3] = -6;
  in->data[8][4] = -1;

  in->data[9][0] =  2;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 1;
  in->clause_lengths[1] = 3;
  in->clause_lengths[2] = 1;
  in->clause_lengths[3] = 3;
  in->clause_lengths[4] = 5;
  in->clause_lengths[5] = 4;
  in->clause_lengths[6] = 3;
  in->clause_lengths[7] = 2;
  in->clause_lengths[8] = 5;
  in->clause_lengths[9] = 1;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_unsat_4(INPUT *in)
{
  int nbvars, nbclauses; 

  nbvars = 1;
  nbclauses = 8;

  in->data = (int **)malloc(sizeof(int*) * nbclauses);
  in->data[0] = (int *)malloc(sizeof(int));
  in->data[1] = (int *)malloc(sizeof(int));
  in->data[2] = (int *)malloc(sizeof(int));
  in->data[3] = (int *)malloc(sizeof(int));
  in->data[4] = (int *)malloc(sizeof(int));
  in->data[5] = (int *)malloc(sizeof(int));
  in->data[6] = (int *)malloc(sizeof(int));
  in->data[7] = (int *)malloc(sizeof(int));

  in->data[0][0] = -1;
  in->data[1][0] =  1;
  in->data[2][0] = -1;
  in->data[3][0] =  1;
  in->data[4][0] = -1;
  in->data[5][0] = -1;
  in->data[6][0] =  1;
  in->data[7][0] =  1;

  // clause lengths
  in->clause_lengths = (int *)malloc(sizeof(int) * nbclauses);
  in->clause_lengths[0] = 1;
  in->clause_lengths[1] = 1;
  in->clause_lengths[2] = 1;
  in->clause_lengths[3] = 1;
  in->clause_lengths[4] = 1;
  in->clause_lengths[5] = 1;
  in->clause_lengths[6] = 1;
  in->clause_lengths[7] = 1;

  // set ints
  in->nbvars = nbvars;
  in->nbclauses = nbclauses;

  setup_val_sums(in);
}

void setup_val_sums(INPUT *in)
{
  int i;

  in->pos_val_sums = malloc(sizeof(int) * in->nbvars);
  in->neg_val_sums = malloc(sizeof(int) * in->nbvars);
  for (i = 0; i < in->nbvars; i++)
  {
    in->pos_val_sums[i] = 0;
    in->neg_val_sums[i] = 0;
  }
}

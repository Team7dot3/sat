#include "unit_test_input_parser.h"

// WARNING !!! This test may seg fault if it fails!
int test_data(void) 
{
  int i, j;
  int size = 63;

  GEN_LADDER_INPUT(size, size);
  PARSE_FILE();

  // in.data = (int **)malloc(sizeof(int*) * size);       // SANITY CHECK, THIS FORCES TEST TO PASS
  for (i = 0; i < size; i++) 
  {
    // in.data[i] = (int *)malloc(sizeof(int) * (i + 1)); // SANITY CHECK, THIS FORCES TEST TO PASS
    for (j = 0; j <= i; j++) 
    {
      // in.data[i][j] = j + 1;                           // SANITY CHECK, THIS FORCES TEST TO PASS
      if ((ACT = in.data[i][j]) != (EXP = j + 1)) 
      { 
        FAIL("test_data")
      }
    }
  }
  PASS("test_data")
}

// WARNING !!! This test may seg fault if it fails!
int test_clause_lengths(void) 
{
  int i;
  int size = 63;

  GEN_LADDER_INPUT(size, size);
  PARSE_FILE();

  // in.clause_lengths = (int *)malloc(sizeof(int) * size); // SANITY CHECK, THIS FORCES TEST TO PASS
  for (i = 0; i < size; i++) 
  {
    // in.clause_lengths[i] = i + 1;                        // SANITY CHECK, THIS FORCES TEST TO PASS
    if ((ACT = in.clause_lengths[i]) != (EXP = i + 1)) 
    {
      FAIL("test_clause_lengths");
    }
  }
  PASS("test_clause_lengths");
}

int test_clauses_count(void) 
{
  GEN_BASIC_INPUT(1, (EXP = 537));
  PARSE_FILE();
  RESULT("test_clauses_count       ", EXP == (ACT = in.nbclauses));
}

int test_vars_count(void) 
{
  GEN_BASIC_INPUT((EXP = 6712), 1);
  PARSE_FILE();
  RESULT("test_vars_count          ", EXP == (ACT = in.nbvars));
}

/* Worst test ever! This will always pass, unless Jared messes up really bad :) */
int test_clause_lengths_size(void) 
{
  GEN_BASIC_INPUT((EXP = 981), 1);
  PARSE_FILE();
  RESULT("test_clause_lengths_size ", EXP == (ACT = sizeof(in.clause_lengths) * EXP) / 4);
}

int test_zero_vars_return(void) 
{
  GEN_BASIC_INPUT(0, 1);
  RESULT("test_zero_vars_return   ", (EXP = 1) == (ACT = (int)input_parser(fp, &in)));
}

int test_zero_vars_count(void) 
{
  GEN_BASIC_INPUT(0, 1);
  PARSE_FILE();
  RESULT("test_zero_vars_count    ", (EXP = 0) == (ACT = (in.nbvars)));
}

int test_zero_clauses_return(void) 
{
  GEN_BASIC_INPUT(1, 0);
  RESULT("test_zero_clauses_return", (EXP = 1) == (ACT = (int)input_parser(fp, &in)));
}

int test_zero_clauses_count(void) 
{
  GEN_BASIC_INPUT(1, 0);
  PARSE_FILE();
  RESULT("test_zero_clauses_count ", (EXP = 0) == (ACT = (in.nbclauses)));
}

int test_input_parser(void) 
{
  int fails = 0;

  LOG("TEST INPUT PARSER", 1);

  fails += test_zero_clauses_return();
  fails += test_zero_clauses_count();
  fails += test_zero_vars_return();
  fails += test_zero_vars_count();
  fails += test_clause_lengths_size();
  fails += test_vars_count();
  fails += test_clauses_count();
  // fails += test_clause_lengths(); // WARNING !!! This test may seg fault if it fails!
  // fails += test_data();           // WARNING !!! This test may seg fault if it fails!

  return fails;
}

void close_sat_file(FILE *fp) 
{
  LOG("CLOSING FILE", 3);
  fclose(fp);
}

FILE* open_sat_file(char *path) 
{
  FILE *fp;
  if ((fp = fopen(path, "r"))) 
  {
    return fp;
  } 
  else 
  {
    LOG("ERROR DURING TEST", 3);
    exit(1);
  }
}

FILE* write_basic_sat_file(char *path, int nbvar, int nbclauses) 
{
  int i, j;
  FILE *fp;

  if ((fp = fopen(path, "w"))) 
  {
    fprintf(fp, "p cnf %d %d\n", nbvar, nbclauses);

    for (i = 0; i < nbclauses; i++) 
    {
      for (j = 1; j <= nbvar; j++) 
      {
        fprintf(fp, "%d ", j);
      }
      fprintf(fp, "0\n");
    }

    // Close the file first, then re-open the file in READ ONLY mode
    // Without this, multiple tests causes undefined behavior 
    //   with what is actually written to disk
    close_sat_file(fp);
    return open_sat_file(path);
  } 
  else 
  {
    LOG("ERROR DURING TEST", 3);
    exit(1);
    
  }
}

FILE* write_ladder_sat_file(char *path, int nbvars, int nbclauses) 
{
  int i, j;
  FILE *fp;

  if ((fp = fopen(path, "w"))) 
  {
    fprintf(fp, "p cnf %d %d\n", nbvars, nbclauses);
    printf("writing nbvars = %d and nbclauses = %d \n", nbvars, nbclauses);

    for (i = 0; i < nbclauses; i++) 
    {
      for (j = 1; j <= i + 1 && j <= nbvars; j++) 
      {
        fprintf(fp, "%d ", j);
      }
      fprintf(fp, "0\n");
    }

    // Close the file first, then re-open the file in READ ONLY mode
    // Without this, multiple tests causes undefined behavior 
    //   with what is actually written to disk
    close_sat_file(fp);
    return open_sat_file(path);
  } 
  else 
  {
    LOG("ERROR DURING TEST", 3);
    exit(1);
  }
}

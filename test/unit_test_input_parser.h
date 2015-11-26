#include "units.h"
#include "../src/sat_types.h"

#define PARSE_FILE(void) \
  input_parser(fp, &in); \
  close_sat_file(fp);

#define TEST_PATH(void)   \
  char p1[] = "txt/test.txt";

#define GEN_BASIC_INPUT(nbvars, nbclauses)                  \
  TEST_PATH();                                              \
  FILE *fp = write_basic_sat_file(p1, nbvars, nbclauses);   \
  GEN_STRUCTS();

#define GEN_LADDER_INPUT(nbvars, nbclauses)                 \
  TEST_PATH();                                              \
  FILE *fp = write_ladder_sat_file(p1, nbvars, nbclauses);  \
  GEN_STRUCTS();

int test_clauses_count(void);
int test_vars_count(void);
int test_clause_lengths_size(void);
int test_zero_vars_return(void);
int test_zero_vars_count(void);
int test_zero_clauses_return(void);
int test_zero_clauses_count(void);
int test_clause_lengths(void);
int test_data(void);
int test_var_bounds_1(void);
int test_var_bounds_2(void);
int test_var_bounds_3(void);
int test_clause_bounds_1(void);
int test_clause_bounds_2(void);
int test_clause_bounds_3(void);

int test_input_parser(void);
FILE* write_basic_sat_file(char *path, int nbvar, int nbclauses);
FILE* write_ladder_sat_file(char *path, int nbvar, int nbclauses);
void close_sat_file(FILE *fp);

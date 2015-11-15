/*******************************************************************************************
 * AUTHOR :     Andrew Hendrix
 * AUTHOR :     Jared Potter
 * AUTHOR :     Leland Stenquist
 * AUTHOR :     Taylor Wilson
 *
 * DATE :       October 24, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 */
#include "input.h"

/*******************************************************************************************
 * NAME :             check_args
 *
 * DESCRIPTION :      Verifies the validity of the arguments.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int       argc            number of arguments
 *          char      *argv[]         input arguments
 *
 * OUTPUTS :
 *      RETURN :
 *          FILE*                       Actual FILE* on success, NULL on failure
 */
FILE* check_args(int argc, char *argv[])
{
  // Checks for the correct number of inputs.
  if (argc != 2)
  {
    printf("ERROR\n");
    return NULL;
  }

  return fopen(argv[1], "r");
}

/*******************************************************************************************
 * NAME :             input_parse
 *
 * DESCRIPTION :      Parses the input from a file of the cnf sat form.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE              *fp     file
 *          INPUT             *input  input
 *
 * OUTPUTS :
 *      RETURN : 1 on success, -1 on failure/error
 */
int input_parser(FILE *fp, UNMOLESTED_INPUT *input)
{
  // Finding the size of the file in bytes.
  int file_size = get_file_size(fp);

  // Pass over comments.
  char* line = parse_comments(fp, file_size);

  int* nbvar               = malloc(sizeof(int)); // ndicates variables will be from [-1, -nbvar] and [1, nbvar].
  if(!nbvar) { return -1; }
  *nbvar = 0;

  int* nbclauses           = malloc(sizeof(int)); // indicates the number of rows (clauses), indicated by the number of zeros.
  if(!nbvar) { return -1; }
  *nbclauses = 0;

  if(parse_cnf_header(line, nbvar, nbclauses) != 1)
  { return -1; }

  int** data               = malloc(sizeof(int)*(*nbclauses)*(*nbvar));
  if(!data) { return -1; }

  int* clause_lengths      = malloc(sizeof(int)*(*nbclauses));
  if(!clause_lengths) { return -1; }

  int* value_sums          = malloc(sizeof(int)*((*nbvar)));
  if(!value_sums) { return -1; }
  for(int i = 0; i < *nbvar; i++) // Load array with 0s.
  { value_sums[i] = 0; }

  // Loops over all clauses. 
  if(parse_clauses(fp, file_size, data, nbclauses, clause_lengths, value_sums) != 1)
  { return -1; }  

  // Load values into structs.
  input->data = data;
  input->nbclauses = *nbclauses; 
  input->nbvars = *nbvar;
  input->clause_lengths = clause_lengths;
  input->value_sums = value_sums;

  free(nbvar);
  free(nbclauses);

  return 1;
}

/*******************************************************************************************
 * NAME :             input_string
 *
 * DESCRIPTION :      Reads a line of data from a file.
 *
 * Method based on solution from 
 * http://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
 * Username: BLUEPIXY
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp            the pointer to the file
 *          size_t      size          the number of bytes to read
 *
 * OUTPUTS :
 *      RETURN :
 *          char*                      the string read from the file on success, 
 *                                     the original string on failure
 */
char* input_string(FILE* fp, size_t size)
{
    //The size is extended by the input with the value of the provisional.
    char *str;
    int ch;
    size_t len = 0;
    str = (char*)malloc(size); //size is start size
    if(!str)
    {
      return str;
    }
    while(EOF != (ch = fgetc(fp)) && ch != '\n')
    { 
      str[len++] = ch;
      if(len == size)
      {
        str = realloc(str, (size += 16));
        if(!str)
        { 
          return str; 
        }
      }
    }
    str[len++] = '\0';

    return realloc(str, len);
}

/*******************************************************************************************
 * NAME :             get_file_size
 *
 * DESCRIPTION :      Returns the sie of a file.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp            the pointer to the file
 *
 * OUTPUTS :
 *      RETURN :
 *          int                      the size of the file in bytes
 */
 int get_file_size(FILE* fp)
 {
  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  return size;
 }

/*******************************************************************************************
 * NAME :             parse_comments
 *
 * DESCRIPTION :      Progresses the file pointer past the commentes.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp            The pointer to the file.
 *          int         file size     The size of the file in bytes.
 *
 * OUTPUTS :
 *      RETURN :
 *          char*                     The line of the next line ("problem" line).
 */
char* parse_comments(FILE* fp, int file_size)
{
  char* line = input_string(fp, file_size);

  while(line != NULL && strcmp(line, ""))
  {
    if(line[0] == 'c') 
    { /* Ignore comments */ 
      free(line);
    }
    else
    {
      return line;
    }
    // Read next line. 
    line = input_string(fp, file_size);
  }
  return line;
}

/*******************************************************************************************
 * NAME :             parse_cnf_header
 *
 * DESCRIPTION :      Parses the cnf header ("problem" line) of the file.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          char*       line          The cnf line.
 *          int*        nbvar         The nbvar variable.
 *          int*        nbclauses     The nbclauses variable.
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on success, -1 on failure/error.
 */
int parse_cnf_header(char* line, int* nbvar, int* nbclauses)
{
  char* end_ptr; // For error checking strtol.

  // The "problem" line.
  char* split_problem_line = strtok(line, " ");

  // This section performs input validation on the "problem" line
  // aka "p cnf nbvar nbclauses"
  if(line[0] == 'p') // TODO: make this consistent with others.
  {
    split_problem_line = strtok (NULL, " ");

    if(!strcmp(split_problem_line, "cnf"))
    {
      split_problem_line = strtok (NULL, " ");
      *nbvar = strtol(split_problem_line, &end_ptr, 0);

      if(*end_ptr == '\0') // Verify int value.
      {
        split_problem_line = strtok (NULL, " ");
        *nbclauses = strtol(split_problem_line, &end_ptr, 0);

        if(*end_ptr == '\0') // Verify int value.
        { 
          free(line);/* "problem" line parse successful. */ 
        }
        else
        { return -1; }
      }
      else
      { return -1; }
    }
    else
    { return -1; }
  }
  else
  { return -1; }
  return 1;
}

/*******************************************************************************************
 * NAME :             parse_clauses
 *
 * DESCRIPTION :      Progresses the file pointer past the commentes.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp                      The pointer to the file.
 *          int         file size               The size of the file in bytes.
 *          int**       data                    The pointer to the set of pointers to the clauses.
 *          int*        nbclauses               The number of expected clauses.
 *          int*        clause_lengths          The array of clause lengths.
 *          int*        value_sums            The array of values of units sumed. Ex. 1 and -1 would result in 0 in the '1's index.
 *
 * OUTPUTS :
 *      RETURN :
 *          int*                     1 on success, -1 on failure/error.
 */
int parse_clauses(FILE* fp, int file_size, int** data, int* nbclauses, int* clause_lengths, int* value_sums)
{
  int current_data_index = 0;
  int current_clause_index = 0;
  int clause_length = 0;

  int actual_clause_count = 0;

  char* end_ptr; // For error checking strtol.

  char* line = input_string(fp, file_size);

  while(line != NULL && strcmp(line, ""))
  {
    actual_clause_count++;

    if(actual_clause_count > *nbclauses) // Prevents over writing memory.
    {
      LOG("Actual clause count has exceeded expected clause count (nbclauses).", 3); 
      return -1; 
    }

    // Create copy of line because strtok() consumes line during count.
    int line_size = strlen(line);

    char* line_copy = malloc(line_size + 1);
    line_copy[line_size] = '\0';

    memcpy(line_copy, line, line_size);

    char* split_clause = strtok(line, " ");

    // Count the number of values in a clause.
    while(split_clause != NULL)
    {
      clause_length++;
      split_clause = strtok (NULL, " "); // Increment to next value.
    }

    // Subtract 1 to account for clause terminating 0.
    clause_length -= 1;

    // Sets clause length in clause_lengths array.
    clause_lengths[current_data_index] = clause_length;

    int* clause = (int *)malloc(sizeof(int) * clause_length); // A clause to hold values.//

    // Start to load values. 
    split_clause = strtok(line_copy, " ");
    

    // Read clause values from char* and place into clause[].
    while(split_clause != NULL)
    {
      // Tries to converts char* to int.
      int clause_value = strtol(split_clause, &end_ptr, 0); 
      
      if(clause_value != 0)
      {
        clause[current_clause_index] = clause_value;

        if(clause_value < 0)
        { value_sums[abs(clause_value) - 1] += -1; }
        else
        { value_sums[abs(clause_value) - 1] +=  1; }
      }

      if(*end_ptr != '\0' && clause_value != 0) { return -1; } // Verify int value.

      split_clause = strtok (NULL, " "); // Increment to next value.
      current_clause_index++; // Increment the clause index.
    }

    data[current_data_index] = clause; // Set clause in data.

    current_data_index++; // Increment the data index.
    current_clause_index = 0; // Reset the clause index.
    clause_length = 0;

    free(line_copy);
    free(line);

    line = input_string(fp, file_size);
  }

  if(actual_clause_count != *nbclauses)
  {
    LOG("Actual clause count != expected clause count (nbclauses).", 3);
    return -1;
  }

  free(line);
  return 1;
} 

/*******************************************************************************************
 * NAME :             input_free
 *
 * DESCRIPTION :      Free all resources after use.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE              *fp     file
 *          INPUT             *input  input
 *
 * OUTPUTS :
 *      RETURN :
 *          void
 */
void input_free(FILE *fp, UNMOLESTED_INPUT *input)
{
  LOG("INPUT FREE CALLED", 1);
  
  // Free all resources after use.
  fclose(fp);
  for(int i = 0; i < input->nbclauses; i++)
  { free(input->data[i]); }
  free(input->data);
  free(input->clause_lengths);
  free(input->value_sums);
  free(input);

  LOG("INPUT FREE RETURNING", 1);
}

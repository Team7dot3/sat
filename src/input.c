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
 *          UNMOLESTED_INPUT  *unin   input
 *          MOLESTED_INPUT    *in     input
 *
 * OUTPUTS :
 *      RETURN : 1 on success, 0 on failure
 */
int input_parser(FILE *fp, UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in)
{
  LOG("INPUT PARSER CALLED", 1);

  // Finding the size of the file in bytes.
  int file_size = get_file_size(fp);

  // Pass over comments.
  char* line = read_comments(fp, file_size);

  int nbvar     = 0; // ndicates variables will be from [-1, -nbvar] and [1, nbvar].
  int nbclauses = 0; // indicates the number of rows (clauses), indicated by the number of zeros
  char* endptr; // For error checking strtol.

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
      nbvar = strtol(split_problem_line, &endptr, 0);

      if(*endptr == '\0') // Verify int value.
      {
        split_problem_line = strtok (NULL, " ");
        nbclauses = strtol(split_problem_line, &endptr, 0);

        if(*endptr == '\0') // Verify int value.
        {
          // "problem" line parse successful.
        }
        else
        { return 0; }
      }
      else
      { return 0; }
    }
    else
    { return 0; }
  }
  else
  { return 0; }

  int** data               = malloc(sizeof(int)*nbclauses*(nbvar - 1));
  int* clause_lengths      = malloc(4*nbclauses);
  int* unit_clauses        = malloc(nbclauses);
  int* unit_clauses_length = malloc(sizeof(int));
  *unit_clauses_length = 0;

  // Loops over all clauses. 
  if(!read_clauses(fp, file_size, data, clause_lengths, unit_clauses, unit_clauses_length))
  { return 0; }

  // Load values into structs.
  unin->data = data;
  unin->nbclauses = nbclauses; 
  unin->nbvars = nbvar;
  unin->clause_lengths = clause_lengths;

  in->data = unit_clauses;
  in->length = *unit_clauses_length;

  LOG("INPUT PARSER RETURNING", 1);
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
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, size); //size is start size
    if(!str)return str;
    while(EOF != (ch = fgetc(fp)) && ch != '\n') // && ch != '\n'
    { 
        str[len++]=ch;
        if(len==size){
            str = realloc(str, (size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

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
 * NAME :             read_comments
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
char* read_comments(FILE* fp, int file_size)
{
  char* line = input_string(fp, file_size);

  while(line != NULL && strcmp(line, ""))
  {
    if(line[0] == 'c')
    { /* Ignore comments */ }
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
 * NAME :             read_clauses
 *
 * DESCRIPTION :      Progresses the file pointer past the commentes.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp                      The pointer to the file.
 *          int         file size               The size of the file in bytes.
 *          int**       data                    The pointer to the set of pointers to the clauses.
 *          int*        clause_lengths          The array of clause lengths.
 *          int*        unit_clauses            The array of clauses of 1 value.
 *          int*        unit_clauses_length     The number of unit clauss.
 *
 * OUTPUTS :
 *      RETURN :
 *          int*                     1 on success, 0 on failure.
 */
int read_clauses(FILE* fp, int file_size, int** data, int* clause_lengths, int* unit_clauses, int* unit_clauses_length)
{
  int current_data_index = 0;
  int current_clause_index = 0;
  int clause_length = 0;

  char* endptr; // For error checking strtol.

  char* line = input_string(fp, file_size);

  while(line != NULL && strcmp(line, ""))
  {
    // Create copy of line because strtok() consumes line during count.
    char* line_copy = malloc(strlen(line));
    strncpy(line_copy, line, strlen(line));

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
      int clause_value = strtol(split_clause, &endptr, 0); 
      clause[current_clause_index] = clause_value;

      if(*endptr != '\0' && clause_value != 0) { return 0; }// Verify int value.
      
      split_clause = strtok (NULL, " "); // Increment to next value.
      current_clause_index++; // Increment the clause index.
    }

    // If clause is only length 1, save value to molested intput struct.
    if(clause_length == 1)
    {
      unit_clauses[*unit_clauses_length] = clause[current_clause_index-2];
      (*unit_clauses_length)++;
    }

    data[current_data_index] = clause; // Set clause in data.

    current_data_index++; // Increment the data index.
    current_clause_index = 0; // Reset the clause index.
    clause_length = 0;

    line = input_string(fp, file_size);
  }
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
 *          UNMOLESTED_INPUT  *unin   input
 *          MOLESTED_INPUT    *in     input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on success, 0 on failure
 */
int input_free(FILE *fp, UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in)
{
  LOG("INPUT FREE CALLED", 1);

  // Free all resources after use.
  fclose(fp);
  free(unin);
  free(in);

  LOG("INPUT FREE RETURNING", 1);
  return 0;
}

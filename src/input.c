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
 * DESCRIPTION :      <DESCRIPTION STUBB>
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

  const char* file_path = argv[1];

  FILE *fp = fopen(file_path, "r");

  return fp;
}

/*******************************************************************************************
 * NAME :             input_parse
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
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
  fseek(fp, 0L, SEEK_END);
  int file_size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  char* result = input_string(fp, file_size);

  // Pass over comments.
  while(result != NULL && strcmp(result, ""))
  {
    if(result[0] == 'c')
    {
      // Ignore comments.
    }
    else
      break; 

    result = input_string(fp, file_size);
  }

  int nbvar     = 0; // 
  int nbclauses = 0; //
  char* endptr; // For error checking strtol.

  // The "problem" line.
  char* split_string = strtok(result, " ");

  // This section performs input validation on the "problem" line
  // aka "p cnf nbvar nbclauses"
  if(result[0] == 'p')
  {
    split_string = strtok (NULL, " ");

    if(!strcmp(split_string, "cnf"))
    {
      split_string = strtok (NULL, " ");
      nbvar = strtol(split_string, &endptr, 0);

      if(*endptr == '\0') // Verify int value.
      {
        split_string = strtok (NULL, " ");
        nbclauses = strtol(split_string, &endptr, 0);

        if(*endptr != '\0') // Verify int value.
        {
          return 0;
        }
      }
      else
        return 0;
    }
    else
      return 0;

    //printf("nbvars: %d\n", nbvar);
    //printf("nbclauses: %d\n", nbclauses);
  }
  else
    return 0;

  int** data = malloc(4*nbclauses*(nbvar - 1));
  int* clause_lengths = malloc(4*nbclauses);
  int* unit_clauses = malloc(nbclauses);
  int unit_clauses_length = 0;

  int current_data_index = 0;
  int current_clause_index = 0;
  int total_value_count = 0;
  int clause_length = 0;

  result = input_string(fp, file_size); // Reds the first clause. 

  // Loops over all clauses. 
  while(result != NULL && strcmp(result, ""))
  {
    // Create copy of result because strtok() consumes result during count.
    char* result_copy = malloc(strlen(result));
    strncpy(result_copy, result, strlen(result));

    char* split_clause = strtok(result, " ");

    // Count the number of values in a clause.
    while(split_clause != NULL)
    {
      clause_length++;
      split_clause = strtok (NULL, " "); // Increment to next value.
    }

    clause_length -= 1; // Subtract 1 to account for clause terminating 0.
    //printf("clause_length: %d\n", clause_length);

    // Sets clause length in clause_lengths array.
    clause_lengths[current_data_index] = clause_length;
    total_value_count += clause_length;

    int* clause = (int *)malloc(sizeof(int) * clause_length); // A clause to hold values.//

    // Start to load values. 
    split_clause = strtok(result_copy, " ");

    // Read clause values from char* and place into clause[].
    while(split_clause != NULL)
    {
      //printf("split_clause: %s\n", split_clause);
      // Tries to converts char* to int.
      clause[current_clause_index] = strtol(split_clause, &endptr, 0); 
      
      // Currently not working.
      //if(*endptr != '\0') { printf("here\n"); return 0; }// Verify int value.
      
      split_clause = strtok (NULL, " "); // Increment to next value.
      current_clause_index++; // Increment the clause index.
    }

    if(clause_length == 1)
    {
      unit_clauses[unit_clauses_length] = clause[current_clause_index-2];
      unit_clauses_length++;
    }

    data[current_data_index] = clause; // Set clause in data.

    current_data_index++; // Increment the data index.
    current_clause_index = 0; // Reset the clause index.
    clause_length = 0;

    result = input_string(fp, file_size);
  }

  printf("unit_clauses_length: %d\n", unit_clauses_length);

  // for(int i = 0; i < unit_clauses_length; i++)
  // {
  //   printf("unit_clause # %d\n", i);
  //   printf("value: %d\n", unit_clauses[i]);
  // }

  // for(int i = 0; i < nbclauses; i++)
  // {
  //   int* tmp_clause = data[i];

  //   int tmp_clause_length = clause_lengths[i];

  //   printf("Clause #: %d\n", i);
  //   printf("Clause Length: %d\n", tmp_clause_length);

  //   for(int j = 0; j < tmp_clause_length; j++)
  //   {
  //     printf("Value[%d]: %d\n", j, tmp_clause[j]);
  //   }
  // }

  unin->data = data;
  unin->nbclauses = nbclauses; 
  unin->nbvars = nbvar;
  unin->clause_lengths = clause_lengths;

  in->data = unit_clauses;
  in->length = unit_clauses_length;

  LOG("INPUT PARSER RETURNING", 1);
  return 1;
}

/*******************************************************************************************
 * NAME :             input_string
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
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
 * NAME :             check_args
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
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

  // Closing the file pointer.
  fclose(fp);

  LOG("INPUT FREE RETURNING", 1);
  return 0;
}
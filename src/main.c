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
#include "sat_types.h"

/*******************************************************************************************
 * NAME :             main
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
 *          int                       returns 0, always
 */
int main(int argc, char *argv[])
{
  LOG("STARTING SAT SOLVER", 3);

  FILE* fp = check_args(argc, argv);

  if (!fp) { LOG("Error while opening/reading file.", 3); printf("ERROR\n"); return 0; }
  
  // TODO: malloc structs
  UNMOLESTED_INPUT *unin = malloc(sizeof(UNMOLESTED_INPUT));

  MOLESTED_INPUT *in = malloc(sizeof(MOLESTED_INPUT));
  
  if (!input_parser (fp, unin, in)) { printf("ERROR\n"); return 0; } // TODO fix args

  // OUTPUT TESTING FOR UNMOLESTED_INPUT
  // for(int i = 0; i < unin->nbclauses; i++)
  // {
  //   int* tmp_clause = unin->data[i];

  //   int tmp_clause_length = unin->clause_lengths[i];

  //   printf("Clause #: %d\n", i);
  //   printf("Clause Length: %d\n", tmp_clause_length);

  //   for(int j = 0; j < tmp_clause_length; j++)
  //   {
  //     printf("Value[%d]: %d\n", j, tmp_clause[j]);
  //   }
  // }

  // OUTPUT TESTING FOR MOLESTED_INPUT
  // for(int i = 0; i < in->length; i++)
  // {
  //   printf("unit_clause # %d\n", i);
  //   printf("value: %d\n", in->data[i]);
  // }

  //if (!solve        (NULL, NULL      )) { printf("ERROR\n"); return 0; } // TODO fix args
  if (!input_free   (fp, NULL, NULL)) { printf("ERROR\n"); return 0; } // TODO fix args
  
  // TODO: call free
  
  LOG("EXITING SAT SOLVER", 3);
  
  return 0;
}
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
 * DESCRIPTION :      Main entry point for the SAT solver.
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

  if(!fp) 
  { 
    LOG("Error while opening/reading file.", 3); 
    printf("ERROR\n");
    return 0; 
  }
  
  INPUT *input = malloc(sizeof(INPUT));
  
  if(input_parser(fp, input) != 1)
  { 
    LOG("Error parsing input from file.", 3); 
    ERROR();
	file_free(fp);
    input_free(input);
    return 0;
  }
  file_free(fp);
  switch(solve(input))
  {
    case 1:
      SATISFIABLE();
      break;
    case 0:
      UNSATISFIABLE();
      break;
    case -1:
      ERROR();
      break;
  }
  input_free(input); 
  
  LOG("EXITING SAT SOLVER", 3);
  
  return 0;
}

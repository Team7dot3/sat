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

  if(!fp) 
  { 
  	LOG("Error while opening/reading file.", 3); 
  	printf("ERROR\n");
  	input_free(fp, NULL, NULL);
  	return 0; 
  }
  
  UNMOLESTED_INPUT *unin = malloc(sizeof(UNMOLESTED_INPUT));
  MOLESTED_INPUT *in = malloc(sizeof(MOLESTED_INPUT));
  
  if(input_parser(fp, unin, in) != 1)
  { 
  	LOG("Error parsing input from file.", 3); 
  	printf("ERROR\n"); 
  	input_free(fp, unin, in);
  	return 0;
  }

  switch(solve(unin, in))
  {
  	case 1:
  	  printf("SATISFIABLE\n");
  	  break;
  	case 0:
  	  printf("UNSATISFIABLE\n");
  	  break;
  	case -1:
  	  printf("ERROR\n");
  	  break;
  }

  input_free(fp, unin, in); 
  
  LOG("EXITING SAT SOLVER", 3);
  
  return 0;
}

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
 *          int                       1 on success, 0 on failure
 */
int check_args(int argc, char *argv[])
{
  // Checks for the correct number of inputs.
  if (argc != 2)
  {
    printf("ERROR\n");
    return 0;
  }
  return 1;
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
 *      RETURN :
 *          int                       1 on success, 0 on failure
 */
int input_parser(FILE *fp, UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in)
{
  LOG("INPUT PARSER CALLED", 1);

  LOG("INPUT PARSER RETURNING", 1);
  return 0;
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

  LOG("INPUT FREE RETURNING", 1);
  return 0;
}

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
	if (!check_args(argc, argv)) { return 0; }

	// TODO: malloc structs
	
	if (!input_parser (NULL, NULL, NULL)) { return 0; } // TODO fix args
	if (!solve        (NULL, NULL      )) { return 0; } // TODO fix args
	if (!input_free   (NULL, NULL, NULL)) { return 0; } // TODO fix args

	// TODO: call free

	printf("EXITING SAT SOLVER\n"); // TODO: remove this before deadline

	return 0;
}

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
#ifndef INPUT_H
#define INPUT_H

#include "sat_types.h"

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
int check_args(int argc, char *argv[]);

/*******************************************************************************************
 * NAME :             input_parser
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
int input_parser(FILE *fp, UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in);

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
int input_free(FILE *fp, UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in);

#endif

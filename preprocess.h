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
#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "sat_types.h"



/*******************************************************************************************
* NAME :             preprocess
*
* DESCRIPTION :      This function rewrites SAT input into an equivilent SAT input that is easier to solve.
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       1 on success, -1 on error
*/
int preprocess(INPUT *in);


#endif
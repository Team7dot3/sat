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
#ifndef SAT_TYPES_H
#define SAT_TYPES_H

#include <stdio.h>
#include <assert.h>

/*******************************************************************************************
 * NAME :             UNMOLESTED_INPUT
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
 */
typedef struct UNMOLESTED_INPUT
{
	int** data;
	int   nbclauses;
	int*  clause_lengths;
	int   nbvars;
} UNMOLESTED_INPUT;

/*******************************************************************************************
 * NAME :             UNMOLESTED_INPUT
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
 */
typedef struct MOLESTED_INPUT
{
	int* data;
	int length;
} MOLESTED_INPUT;

#include "input.h"
#include "solve.h"

#endif 

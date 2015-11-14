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
#ifndef SOLVE_H
#define SOLVE_H

#include "sat_types.h"

/*******************************************************************************************
 * NAME :             solve
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
 *
 * INPUTS :
 *      PARAMETERS :   
 *          UNMOLESTED_INPUT  *unin   input
 *          MOLESTED_INPUT    *in     input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int solve(UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in);
int process_or(int* values, int* data, int datalen);
int process_and(UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in);
void make_val(int* vals, int input, int num_vals);
int solver(int ** values, int val_count, int num_clauses, int * clause_length, int * counts, int * setvals, int pos);
int process_clause(int* values, int val_count, int clause_length, int * setvals);
int printIntArray(int * array, int size);

#endif

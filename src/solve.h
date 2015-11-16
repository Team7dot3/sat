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
 *          INPUT             *input  input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int solve(INPUT *in);

/*******************************************************************************************
* NAME :             solver
*
* DESCRIPTION :      This function does recursive calls to try to find a satisfiable solution.
*
* INPUTS :
*      PARAMETERS :
*          int** values       The values that constitute the list of clauses.
*          int val_count      The number of variables.
*          int num_clauses    The number of clauses in values. (also the length of clause_length below)
*          int* clause_length The length of each clause in values.
*          int* counts        The "count" for each variable that helps statistically determine which initial choice is probably best.
*          int* setvals       The current set position of each variable.
*          int pos            The current variable we're on.
*          int try_num        If this is the first or second try with the variable (e.g. if we've tried true, we want to try false next, and vice versa)
*
* OUTPUTS :
*      RETURN :
*          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
*/
int solver(int ** values, int val_count, int num_clauses, int * clause_length, int * counts, int * setvals, int pos, int try_num);

/*******************************************************************************************
* NAME :             process_clause
*
* DESCRIPTION :      Processes a clause with a current set of variables to see if it is satisfied, unsatisfied, or there's a contradiction.
*
* INPUTS :
*      PARAMETERS :
*          int* values       The values that constitute the list of variables in the clause.
*          int val_count     The number of variables.
*          int clause_length The number of variables in the clause.
*          int* setvals      The current set value of each variable.
*
* OUTPUTS :
*      RETURN :
*          int                       1 on satisfied, 0 on unsatisfied, -1 on contradiction
*/
int process_clause(int* values, int val_count, int clause_length, int * setvals);

#endif

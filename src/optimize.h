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
#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include "sat_types.h"



/*******************************************************************************************
* NAME :             optimize
*
* DESCRIPTION :      This function rewrites SAT input into an equivilent SAT input that is easier to solve.
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in        input
*          int    run_type   0 if it's the first run, 1 afterwards
*
* OUTPUTS :
*      RETURN :
*          int                       3 on satisfiable, 2 on unsatisfiable/contradiction, 1 on optimized, 0 on couldn't optimize, -1 on error
*/
int optimize(INPUT *in, int run_type);

void print_clauses(INPUT *in);

void rename_variables(INPUT *in);

void reorder_rows(INPUT *in, int start, int end);

/*******************************************************************************************
* NAME :             pure_clauses
*
* DESCRIPTION :        If there is a pure_clause (contains a positive and negative of the same value),
*                      remove it while keeping all numbers correct (removing a line will decrement several variables elsewhere.)
*                      Note: we don't keep the number of variables correct until we rename variables
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       3 on satisfiable, 1 on clause removed, 0 on nothing removed, -1 on error
*/
int pure_clauses(INPUT *in);

/*******************************************************************************************
* NAME :             unit_propagation
*
* DESCRIPTION :        If there is a unit clause (size 1),
*                      propigate it by checking if there is an opposing unit clause (instant contradiction),
*                      assigning it (to true if positive, or false if negative),
*                      remove it everywhere it appears by removing the line if it evaluates to true on a given line, or removing it from the line if it evaluates to false
*                      Keep all numbers correct (removing a variable will decrement several values elsewhere, and removing a line will decrement several variables elsewhere.)
*                      Note: we don't keep the number of variables correct until we rename variables
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       3 on satisfiable, 2 on unsatisfiable, 1 on unit propagated, 0 on nothing propagated, -1 on error
*/
int unit_propagation(INPUT *in);

/*******************************************************************************************
* NAME :             similar_clauses
*
* DESCRIPTION :        If there is a similar_clauses, remove it. An example of this would be 
*                      if we had the clause (1,-3) and the similar clause (1, -3, 4, 5) we 
*                      could get rid of the longer clause because IFF the shorter clause is 
*                      true then the longer clause must be true also.
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       3 on satisfiable, 1 on variable removed, 0 on nothing removed, -1 on error
*/
int similar_clauses(INPUT *in);

/*******************************************************************************************
* NAME :             pure_literals
*
* DESCRIPTION :        If there is a pure_literal (only appears as positive or negative),
*                      assign it (to true if positive, or false if negative),
*                      remove it everywhere it appears by removing the lines it appears on
*                      Keep all numbers correct (removing a variable will decrement several values elsewhere, and removing a line will decrement several variables elsewhere.)
*                      Note: we don't keep the number of variables correct until we rename variables
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       3 on satisfiable, 1 on variable removed, 0 on nothing removed, -1 on error
*/
int pure_literals(INPUT *in);

/*******************************************************************************************
* NAME :             set_variable
*
* DESCRIPTION :        Parses the input and sets the variable to true or false by
*                      removing all clauses containing the variable when it evaluates to true (after applying any not operators)
*                      removing all instances of the variable from a clause when it evaluates to false (after applying any not operators)
*                      Note that if we've removed the last clause, it's now considered "satisfiable"
*                      however, if we remove the last variable from a clause, it's considered "unsatisfiable"
*
* INPUTS :
*      PARAMETERS :
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       3 on satisfiable, 2 on unsatisfiable, 1 on variable set, -1 on error
*/
int set_variable(INPUT *in, int variable, int set);

int remove_variable(INPUT *in, int clausenum, int varposnum);

int remove_clause(INPUT *in, int clausenum);

int input_copy(INPUT *in, INPUT *cp_in);


#endif

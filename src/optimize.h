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
*          INPUT  *in   input
*
* OUTPUTS :
*      RETURN :
*          int                       1 on success, -1 on error
*/
int optimize(INPUT *in);

/*******************************************************************************************
* NAME :             unit_propagation
*
* DESCRIPTION :        If there is a unit clause (size 1),
*                      propigate it by checking if there is an opposing unit clause (instant contradiction),
*                      assigning it (to true if positive, or false if negative),
*                      remove it everywhere it appears by removing the line if it evaluates to true on a given line, or removing it from the line if it evaluates to false
*                      Keep all numbers correct (removing a variable will decrement several values elsewhere, and removing a line will decrement several variables elsewhere.
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

INPUT* input_copy(INPUT *in);


#endif
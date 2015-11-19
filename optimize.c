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
#include "optimize.h"

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
int optimize(INPUT *in)
{
  int** data = in->data;
  int nbclauses = in->nbclauses;
  int* clause_lengths = in->clause_lengths;
  int nbvars = in->nbvars;
  int pos_val_sums = in->pos_val_sums;
  int neg_val_sums = in->neg_val_sums;
  //Optimization types
  //
  //Unit propigation
  //
  //Pure Literals
  //If a variable exists as only positive, or only negative, all rows it exists on can be removed. (They can always evaluate to true from that one variable)
  //
  //Pure Clauses
  //If a clause contains both positive and negative values for a variable, remove the clause.
  //
  //Increase chance of contradictions early on.
  //Reorder rows from smallest to largest
  //
  //Rename variables
  //Rename the variables in the order you find them after reordering
  //Remove all variables that don't appear (decrement the counter)



}


/*******************************************************************************************
* NAME :             unit_propigation
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
*          int                       1 on unit propigated, 0 on nothing propigated, -1 on error
*/
int unit_propigation(INPUT *in)
{
  int i;
  int toReturn = 0;
  for (i = 0; i < in->nbclauses; i++)
  {
    if (clause_lengths[i] == 1)
    {
      toReturn = 1;

      break;
    }
  }
  return toReturn;
}

int set_variable(INPUT *in, int variable, int set)
{

}

INPUT* make_copy(INPUT *in)
{

}
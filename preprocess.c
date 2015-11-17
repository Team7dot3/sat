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
#include "preprocess.h"

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
int preprocess(INPUT *in)
{
  int** data = in->data;
  int nbclauses = in->nbclauses;
  int* clause_lengths = in->clause_lengths;
  int nbvars = in->nbvars;
  int pos_val_sums = in->pos_val_sums;
  int neg_val_sums = in->neg_val_sums;




}
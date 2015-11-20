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
*          int                       3 on satisfiable, 2 on unsatisfiable/contradiction, 1 on optimized, 0 on couldn't optimize, -1 on error
*/
int optimize(INPUT *in)
{
  LOG("OPTIMIZE CALLED", 2);
  int did_optimize = 0;
  //int** data = in->data;
  //int nbclauses = in->nbclauses;
  //int* clause_lengths = in->clause_lengths;
  //int nbvars = in->nbvars;
  //int pos_val_sums = in->pos_val_sums;
  //int neg_val_sums = in->neg_val_sums;
  //Optimization types
  //
  //Unit Propagation
  int var;
  while ((var = unit_propagation(in)) == 1)//keep propagating units while there are still units to propagate
  {
    did_optimize = 1;
  }
  if (var == 2)
  {
    LOG("OPTIMIZE SOLVED", 2);
    return 2;
  }
  if (var == 3)
  {
    LOG("OPTIMIZE SOLVED", 2);
    return 3;
  }
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
  LOG("OPTIMIZE RETURNING", 2);
  return did_optimize;
}


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
int unit_propagation(INPUT *in)
{
  int i;
  int var = 0;
  for (i = 0; i < in->nbclauses; i++)
  {
    if (in->clause_lengths[i] == 1)
    {
      var = in->data[i][0];
      if (var > 0)
      {
        var = set_variable(in, var, 1);//set it equal to true
      }
      else
      {
        var = 0 - var;//make it positive for identification purposes
        var = set_variable(in, var, 0);//set it equal to false;
      }
      break;//we're unable to anticipate how the object may have changed. It's better to start over.
    }
  }
  return var;
}

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
int set_variable(INPUT *in, int variable, int set)
{
  int i;
  int var;
  for (i = 0; i < in->nbclauses; i++)
  {
    int j;
    for (j = 0; j < in->clause_lengths[i]; j++)
    {
      var = in->data[i][j];
      if (var == variable)//variable in the clause as a positive variable
      {
        if (set)//variable set to true
        {
          var = remove_clause(in, i--);//remove the clause, and go back one so when we increment, we go to the "next" clause
          if (var == 3)//the case where we've removed all the clauses
            return 3;
          break;//break out of the inner for loop
        }
        else //variable set to false
        {
          var = remove_variable(in, i, j--);//remove the variable, and go back one in the inner loop (we go back one in case there's a variable that is equal and opposite)
          if (var == 2)//the case where we've removed all the variables
            return 2;
          continue;
        }
      }
      else if ((0 - var) == variable)//variable in the clause as a negative variable
      {
        if (set)//variable set to true
        {
          var = remove_variable(in, i, j--);//remove the variable, and go back one in the inner loop (we go back one in case there's a variable that is equal and opposite)
          if (var == 2)//the case where we've removed all the variables
            return 2;
          continue;
        }
        else
        {
          var = remove_clause(in, i--);//remove the clause, and go back one so when we increment, we go to the "next" clause
          if (var == 3)//the case where we've removed all the clauses
            return 3;
          break;//break out of the inner for loop
        }
      }
    }
  }
  return 1;
}

int remove_variable(INPUT *in, int clausenum, int varposnum)
{
  //int i;
  int var = in->data[clausenum][varposnum];
  if (var > 0)
  {
    in->pos_val_sums[var - 1] = in->pos_val_sums[var - 1] - 1;//remove it's count from the sum array
  }
  else
  {
    var = 0 - var;//make it positive
    in->neg_val_sums[var - 1] = in->neg_val_sums[var - 1] - 1;//remove it's count from the sum array
  }
  in->data[clausenum][varposnum] = in->data[clausenum][in->clause_lengths[clausenum] - 1];//move the object at the end of the array to the position we're removing
  in->clause_lengths[clausenum] = in->clause_lengths[clausenum] - 1;//reduce the size of the array
  if (in->clause_lengths[clausenum] == 0)
  {
    return 2;//if there are no variables in a clause, it's unsatisfiable
  }
  return 1;
}

int remove_clause(INPUT *in, int clausenum)
{
  while (remove_variable(in, clausenum, 0) == 1);//calls the remove variable function on all the variables in the clause to remove them (we ignore the unsatisfiable condition, because we're removing the clause)
  free(in->data[clausenum]);//since we're removing our reference to it, we need to free it.
  in->data[clausenum] = in->data[in->nbclauses - 1];//move the last clause into the position of the clause we're removing
  in->nbclauses = in->nbclauses - 1;//decrease the length of our clauses
  if (in->nbclauses == 0)
  {
    return 3;//if we've eliminated the last clause, it's satisfiable
  }
  return 1;
}

INPUT* input_copy(INPUT *in)
{
  INPUT *cp_in = malloc(sizeof(INPUT));

  int   clause, var, **cp_data, *cp_clause_lengths, *cp_pos_val_sums, *cp_neg_val_sums;
  int** data           = in->data;
  int   nbclauses      = in->nbclauses;
  int*  clause_lengths = in->clause_lengths;
  int   nbvars         = in->nbvars;
  int*  pos_val_sums   = in->pos_val_sums;
  int*  neg_val_sums   = in->neg_val_sums;

  cp_data = malloc(sizeof(int) * (nbclauses)*(nbvars));

  cp_clause_lengths = malloc(sizeof(int) * (nbclauses));
  
  cp_pos_val_sums = malloc(sizeof(int) * ((nbvars)));

  cp_neg_val_sums = malloc(sizeof(int) * ((nbvars)));
  
  for (clause = 0; clause < nbclauses; clause++)
  {
    cp_clause_lengths[clause] = clause_lengths[clause];
    
    for (var = 0; var < clause_lengths[clause]; var++)
    {
      cp_data[clause][var] = data[clause][var];
    }
  }
  
  for (var = 0; var < nbvars; var++)
  {
    cp_pos_val_sums[var] = pos_val_sums[var];
    cp_neg_val_sums[var] = neg_val_sums[var];
  }
  
  cp_in -> data           = cp_data;
  cp_in -> nbvars         = nbvars;
  cp_in -> nbclauses      = nbclauses;
  cp_in -> clause_lengths = cp_clause_lengths;
  cp_in -> pos_val_sums   = cp_pos_val_sums;
  cp_in -> neg_val_sums   = cp_neg_val_sums; 
 
  return cp_in;
}
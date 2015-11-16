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
#include "solve.h"

/*******************************************************************************************
 * NAME :             solve
 *
 * DESCRIPTION :      This function breaks down a cnf and tryies to prove if it is solvable 
 *                    or not.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          INPUT  *in   input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int solve(INPUT *in)
{
  LOG("solve CALLED", 2);
  int nbvars = in->nbvars;
  //int toReturn = process_and(in); //brute force version
  int * setvals = (int*)malloc(sizeof(int)* nbvars);//this is the set of values that the solver will use to keep track of our guesses for each variable
  int i;
  for (i = 0; i < nbvars; i++)//here we preinitialize those values to -1 so they're "not set"
  {
    setvals[i] = -1;
  }
  int toReturn;
  if (solver(in->data, nbvars, in->nbclauses, in->clause_lengths, in->value_sums, setvals, 0, 0))//call the solver and tell it to use the more likely value for the first variable
  {
    toReturn = 1;//It's satisfiable because the solver returned true.
  }
  else
  {
    toReturn = solver(in->data, nbvars, in->nbclauses, in->clause_lengths, in->value_sums, setvals, 0, 1);//call the solver and tell it to use the less likely value for the first variable (because we tried the more likely one)
  }
  free(setvals);//free our malloced memory
  LOG("solve RETURNING", 2);
  return toReturn;//return whatever we saved here.
}


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
int solver(int ** values, int val_count, int num_clauses, int * clause_length, int * counts, int * setvals, int pos, int try_num)
{
  if (pos >= val_count)//check if we've hit the end of the variables we can set, in which case, there's nothing left to do here.
  {
    return 0;
  }

  if (try_num ^ (counts[pos] >= 0))//exclusive or so that when the try_num changes, we'll try the "other" one.
  {
    setvals[pos] = 0;//this sets the current variable to "false"
  }
  else
  {
    setvals[pos] = 1;//this sets the current variable to "true"
  }


  int sat_level = 0;
  int i;
  for (i = 0; i < num_clauses; i++)
  {
    int clause_result = process_clause(values[i], val_count, clause_length[i], setvals);//check the clause with our current variables
      switch (clause_result)
      {
      case -1://Contradiction we have to go back
        setvals[pos] = -1;//this unsets the current variable before returning a contradiction
        return 0;
      case 1://The clause was satisfied
        sat_level++;//we count this so we'll know if all the clauses were satisfied
        break;
      default://The clause is not satisfied, but still can be.
        break;
      }
  }
  if (sat_level == num_clauses)//All clauses were satisfied! We're done!
  {
    return 1;
  }
  //If we reach here, it means we're still unsatisfied, but we haven't hit a contradiction yet.
  if (solver(values, val_count, num_clauses, clause_length, counts, setvals, pos + 1, 0))//check the more likely path
  {
    return 1;//pass the satified condition up the tree
  }
  else
  {
    if (solver(values, val_count, num_clauses, clause_length, counts, setvals, pos + 1, 1))//check the less likely path
    {
      return 1;//pass the satified condition up the tree
    }
    else
    {
      setvals[pos] = -1;//this unsets the current variable before returning a contradiction
      return 0;//Somewhere down below we hit a contradiction
    }
  }
}


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
int process_clause(int* values, int val_count, int clause_length, int * setvals)
{
  int setcount = 0;
  int i;
  for (i = 0; i < clause_length; i++)//Goes through the variables in the clause
  {
    int val;
    int variable = values[i];//Get the variable "name" at the ith position
    if (variable < 0)//Checks if it's negative (a false value will satisfy the clause) or positive (a true value will satisfy the clause)
    {
      //negative
      val = setvals[(-1 * variable) - 1];//Gets the saved value for the variable "name" (1 for true, 0 for false, -1 for not set)
      if (val == 0)//This inverts it because we're dealing with negative. However, it leaves a value of "-1" alone because it's "not set"
      {
        val = 1;
      }
      else if (val == 1)//still part of the inversion
      {
        val = 0;
      }
    }
    else
    {
      //positive
      val = setvals[variable - 1];//since it's positive, we can load it without inverting it.
    }
    //At this point if val is 1 the clause is satisfied, if it's 0 or -1 the clause isn't satisfied yet, 
    switch (val)
    {
    case 1:
      return 1;//the clause is satisfied.
    case 0:
      setcount++;//if it's 0 we need to keep track of it, because if we have all 0s for the clause then we've hit a "contradiction"
      break;
    case -1:
      break;
    }
  }
  if (setcount == clause_length)//checks for the contradiction case mentioned above
  {
    return -1;
  }
  return 0;//otherwise, we return 0, because we weren't able to satify the clause, but it's not unsatisfiable yet.
}

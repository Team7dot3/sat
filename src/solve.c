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
 * NAME :             pre_init
 *
 * DESCRIPTION :      Preinitializes values to -1 so they're "not set"
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int nbvars       The number of variables
 *
 * OUTPUTS :
 *      RETURN :
 *          int*             An preinitialized array of -1s
 */
int* pre_init(int nbvars)
{
  int i, *setvals;
  setvals = (int *)malloc(sizeof(int)* nbvars);
  for (i = 0; i < nbvars; i++)
  {
    setvals[i] = -1;
  }
  return setvals;
}

/*******************************************************************************************
 * NAME :             solve_helper
 *
 * DESCRIPTION :      Calls the solver and tell sit to use the less likely value for the 
 *                    first variable if the more likely one didn't work.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          INPUT *in        input
 *          int   *setvals   The current set position of each variable.
 *
 * OUTPUTS :
 *      RETURN :
 *          int*             An preinitialized array of -1s
 */
int solve_helper(INPUT *in, int *setvals)
{
  if (solver(in, setvals, 0, 0))
  {
    return 1;
  }
  return solver(in, setvals, 0, 1);
}

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
  int to_return = -1;
  LOG("SOLVE CALLED", 2);
  int optisolve = optimize(in, 0);
  while (optisolve == 1)
  {
    optisolve = optimize(in, 1);
  }
  if (optisolve == 2)
  {
    to_return = 0;
  }
  if (optisolve == 3)
  {
    to_return = 1;
  }
  if (to_return == -1)
  {
    int *setvals;
    setvals = pre_init(in->nbvars);
    to_return = solve_helper(in, setvals);
    free(setvals);
  }
  
  LOG("SOLVE RETURNING", 2);
  
  return to_return;
}

/*******************************************************************************************
 * NAME :             check_if_satisfied
 *
 * DESCRIPTION :      Checks if the input has been satisifed. If not, it continues to call the solver.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          INPUT  *in          input
 *          int    *setvals     The current set position of each variable.
 *          int     sat_level   A counter to check if all variables were solved.
 *          int     pos         The current variable we're on.
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfied, 0 on unsatisfied
 */
int check_if_satisfied(INPUT *in, int *setvals, int sat_level, int pos)
{
  // All clauses were satisfied! We're done!
  if (sat_level == in->nbclauses)
  {
    return 1;
  }
  
  // If we reach here, it means we're still unsatisfied, but we haven't hit a contradiction yet.
  // check the more likely path
  if (solver(in, setvals, pos + 1, 0))
  {
    // pass the satified condition up the tree
    return 1;
  }

  // check the less likely path
  if (solver(in, setvals, pos + 1, 1))
  {
    // pass the satified condition up the tree
    return 1;
  }

  // Somewhere down below we hit a contradiction
  // this unsets the current variable before returning a contradiction
  setvals[pos] = -1;
  return 0;
}

/*******************************************************************************************
* NAME :             solver
*
* DESCRIPTION :      This function does recursive calls to try to find a satisfiable solution.
*
* INPUTS :
*      PARAMETERS :
*          INPUT *in          The CNF input to solve.
*          int   *setvals     The current set position of each variable.
*          int    pos         The current variable we're on.
*          int    try_num     If this is the first or second try with the variable (e.g. if we've tried true, we want to try false next, and vice versa)
*
* OUTPUTS :
*      RETURN :
*          int                1 on satisfiable, 0 on unsatisfiable, -1 on error
*/
int solver(INPUT *in, int *setvals, int pos, int try_num)
{ 
  int i, sat_level, clause_result;
  i = sat_level = clause_result = 0;

  CHECK_BASE_CASE(pos, in->nbvars)
  UPDATE_SET_POSITION(setvals, in->pos_val_sums, in->neg_val_sums, pos, try_num);

  for (i = 0; i < in->nbclauses; i++)
  {
    // check the clause with our current variables
    clause_result = process_clause(in->data[i], in->clause_lengths[i], setvals);
      switch (clause_result)
      {
        case -1: 
          // Contradiction we have to go back
          // this unsets the current variable before returning a contradiction
          setvals[pos] = -1;
          return 0;
        case 1:
          // The clause was satisfied
          // we count this so we'll know if all the clauses were satisfied
          sat_level++;
          break;
        default:
          // The clause is not satisfied, but still can be.
          break;
      }
  }
  return check_if_satisfied(in, setvals, sat_level, pos);
}


/*******************************************************************************************
* NAME :             process_clause
*
* DESCRIPTION :      Processes a clause with a current set of variables to see if it is satisfied, unsatisfied, or there's a contradiction.
*
* INPUTS :
*      PARAMETERS :
*          int* values       The values that constitute the list of variables in the clause.
*          int clause_length The number of variables in the clause.
*          int* setvals      The current set value of each variable. 
*
* OUTPUTS :
*      RETURN :
*          int                       1 on satisfied, 0 on unsatisfied, -1 on contradiction
*/
int process_clause(int* values, int clause_length, int * setvals)
{
  int i, setcount, val;
  i = setcount = val = 0;

  // Goes through the variables in the clause
  for (i = 0; i < clause_length; i++)
  {
    // Checks if it's negative (a false value will satisfy the clause) or positive (a true value will satisfy the clause)
    CHECK_VARIABLE_VALUE(val, setvals, values[i]);
    CHECK_VAL_SATISFIABILITY(val, setcount);
  }

  // checks for the contradiction case mentioned above
  if (setcount == clause_length)
  {
    return -1;
  }
  // otherwise, we return 0, because we weren't able to satify the clause, but it's not unsatisfiable yet.
  return 0;
}

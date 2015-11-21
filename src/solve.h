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

#define CHECK_BASE_CASE(pos, nbvars) { if (pos >= nbvars) { return 0; } }

#define CHECK_VARIABLE_VALUE(val, setvals, variable) \
{                                                    \
  if (variable < 0)                                  \
  {                                                  \
    NEGATIVE_VAL(val, setvals, variable);            \
  }                                                  \
  else                                               \
  {                                                  \
    POSTIVE_VAL(val, setvals, variable);             \
  }                                                  \
}

#define CHECK_VAL_SATISFIABILITY(val, setcount)                                      \
{                                                                                    \
  /* At this point if val is 1 the clause is satisfied, */                           \
  /*    if it's 0 or -1 the clause isn't satisfied yet  */                           \
  if (val == 0)                                                                      \
  {                                                                                  \
    /* if it's 0 we need to keep track of it, */                                     \
    /* because if we have all 0s for the clause then we've hit a "contradiction" */  \
    setcount++;                                                                      \
  }                                                                                  \
  else if (val == 1)                                                                 \
  {                                                                                  \
    /* the clause is satisfied. */                                                   \
    return 1;                                                                        \
  }                                                                                  \
}

#define NEGATIVE_VAL(val, setvals, variable)                                                   \
{                                                                                              \
  /* Gets the saved value for the variable "name" (1 for true, 0 for false, -1 for not set) */ \
  val = setvals[(-1 * variable) - 1];                                                          \
  if (val == 0)                                                                                \
  {                                                                                            \
    /* This inverts it because we're dealing with negative. */                                 \
    /* However, it leaves a value of "-1" alone because it's "not set" */                      \
    val = 1;                                                                                   \
  }                                                                                            \
  else if (val == 1)                                                                           \
  {                                                                                            \
    /* still part of the inversion */                                                          \
    val = 0;                                                                                   \
  }                                                                                            \
}

#define POSTIVE_VAL(val, setvals, variable)                       \
{                                                                 \
  /* since it's positive, we can load it without inverting it. */ \
  val = setvals[variable - 1];                                    \
}

#define UPDATE_SET_POSITION(setvals, pos_val_sums, neg_val_sums, pos, try_num)                    \
{                                                                                 \
  /* exclusive or so that when the try_num changes, we'll try the "other" one. */ \
  if (try_num ^ (pos_val_sums[pos] - neg_val_sums[pos] >= 0))                                           \
  {                                                                               \
    /* this sets the current variable to "false" */                               \
    setvals[pos] = 0;                                                             \
  }                                                                               \
  else                                                                            \
  {                                                                               \
    /* this sets the current variable to "true" */                                \
    setvals[pos] = 1;                                                             \
  }                                                                               \
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
int solve(INPUT *in);

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
int solve_helper(INPUT *in, int *setvals);

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
int* pre_init(int nbvars);

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
int solver(INPUT *in, int *setvals, int pos, int try_num);

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
int check_if_satisfied(INPUT *in, int *setvals, int sat_level, int pos);

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
int process_clause(int* values, int clause_length, int * setvals);

#endif

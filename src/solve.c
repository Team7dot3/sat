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
 * DESCRIPTION :      This function breaks down a cnf and tryies to proveif it is solvable 
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
  int toReturn = process_and(in);
  LOG("solve RETURNING", 2);
  return toReturn;
}

/*******************************************************************************************
 * NAME :             process_or
 *
 * DESCRIPTION :      This function processes one clause againts input represented as an 
 *                    array of binary numbers. Example:
 *                      data: 1 -2 4 (this is the clause)
 *                      input: [1,0,0,1]
 *                    This would pass the clause because the vales in the array at n -1 
 *                    represents its the n clause variable. If the input vaule is a 0 the 
 *                    variable should be negative. If the input value is 1 the variable 
 *                    should be positive. The example above would pass.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int*  unin     input
 *          int*  in       input
 *          int   datalen   input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int process_or(int* values, int* data, int datalen)
{
  LOG("process_or CALLED", 2);
  int i;
  for (i = 0; i < datalen; i++)
  {
    int val = data[i];
    if (val < 0)
    {
      val = -val;
      val = !values[val - 1];
    }
    else
    {
      val = values[val - 1];
    }
    if (val)
    {
      LOG("process_or RETURNING", 2);
      return 1;
    }
  }
  LOG("process_or RETURNING", 2);
  return 0;
}

/*******************************************************************************************
 * NAME :             process_and
 *
 * DESCRIPTION :      This function loops through a the binary possibilities 0 to the number 
 *                    of variables. It then processes all of the clauses against each other 
 *                    for the fiven binary input.  For example if you have this file:
 *                      p cnf 3 2 
 *                      -1 2 3 0 
 *                      2 0
 *                    The process and would have the inputs "0 0 0", "1 0 0"...."1 1 1". It 
 *                    would process these iputs until it found one that processed true for all the clauses
 *                    or until it had run through all of them  and none of them had processed true for all 
 *                    clauses.  
 *
 * INPUTS :
 *      PARAMETERS :   
 *          MOLESTED_INPUT    *in     input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int process_and(INPUT *in)
{
  LOG("process_and CALLED", 2);
  int i, j;
  int nbvars = in->nbvars;
  int nbclauses = in->nbclauses;
  int * input = (int*)malloc(sizeof(int)* nbvars);
  if (!input)
  {
    LOG("process_and RETURNING", 2);
    free(input);
    return -1;//TODO: look into this
  }

  for (i = 0; i < (1 << nbvars); i++)
  {
    make_val(input, i, nbvars);

    for (j = 0; j < nbclauses; j++)
    {
      if (process_or(input, in->data[j], in->clause_lengths[j]) == 0)
      {
        break;
      }
    }

    if (j == nbclauses)//If it got to the end of the for loop
    {
      free(input);
            LOG("process_and RETURNING", 2);
      return 1;
    }
  }
  free(input);
  LOG("process_and RETURNING", 2);
  return 0;
}

/*******************************************************************************************
 * NAME :             make_val
 *
 * DESCRIPTION :      fill and array with binary numbers.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int*  vals       input
 *          int   input      input
 *          int   num_vals   input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
void make_val(int* vals, int input, int num_vals)
{
  int i;
  for (i = num_vals - 1; i >= 0; i--)
  {
    if (input / (1 << i))
    {
      input = input - (1 << i);
      vals[i] = 1;
    }
    else
    {
      vals[i] = 0;
    }
  }
}

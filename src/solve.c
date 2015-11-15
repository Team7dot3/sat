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
  int nbvars = in->nbvars;
  //int toReturn = process_and(in);
  //int * counts = (int*)malloc(sizeof(int)* nbvars);
  int * setvals = (int*)malloc(sizeof(int)* nbvars);
  int i;
  for (i = 0; i < nbvars; i++)
  {
    //counts[i] = 0;
    setvals[i] = -1;
  }
  int toReturn;
  if (solver(in->data, nbvars, in->nbclauses, in->clause_lengths, in->value_sums, setvals, 0, 0))
  {
    toReturn = 1;
  }
  else
  {
    setvals[0] = !setvals[0];
    toReturn = solver(in->data, nbvars, in->nbclauses, in->clause_lengths, in->value_sums, setvals, 0, 1);
  }


  //free(counts);
  free(setvals);
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

int solver(int ** values, int val_count, int num_clauses, int * clause_length, int * counts, int * setvals, int pos, int try_num)
{
  if (pos >= val_count)
  {
    return 0;
  }

  if (try_num ^ (counts[pos] >= 0))
  {
    setvals[pos] = 0;
  }
  else
  {
    setvals[pos] = 1;
  }


  int sat_level = 0;
  int i;
  for (i = 0; i < num_clauses; i++)
  {
    int clause_result = process_clause(values[i], val_count, clause_length[i], setvals);
      switch (clause_result)
      {
      case -1:
        setvals[pos] = -1;
        return 0;
      case 1:
        sat_level++;
        break;
      default:
        break;
      }
  }
  if (sat_level == num_clauses)
  {
    return 1;
  }

  if (solver(values, val_count, num_clauses, clause_length, counts, setvals, pos + 1, 0))
  {
    return 1;
  }
  else
  {
    if (solver(values, val_count, num_clauses, clause_length, counts, setvals, pos + 1, 1))
    {
      return 1;
    }
    else
    {
      setvals[pos] = -1;
      return 0;
    }
  }
}

int process_clause(int* values, int val_count, int clause_length, int * setvals)
{
  int setcount = 0;
  int i;
  for (i = 0; i < clause_length; i++)
  {
    int val;
    int variable = values[i];
    if (variable < 0)
    {
      val = setvals[(-1 * variable) - 1];
      if (val == 0)
      {
        val = 1;
      }
      else if (val == 1)
      {
        val = 0;
      }
    }
    else
    {
      val = setvals[variable - 1];
    }

    switch (val)
    {
    case 1:
      return 1;
    case 0:
      setcount++;
      break;
    case -1:
      break;
    }
  }
  if (setcount == clause_length)
  {
    return -1;
  }
  return 0;
}

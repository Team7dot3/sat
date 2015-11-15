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
 * DESCRIPTION :      <DESCRIPTION STUBB>
 *
 * INPUTS :
 *      PARAMETERS :   
 *          UNMOLESTED_INPUT  *unin   input
 *          MOLESTED_INPUT    *in     input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int solve(UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in)
{
  LOG("solve CALLED", 2);
  int nbvars = unin->nbvars;
  //int toReturn = process_and(unin, in);
  int * counts = (int*)malloc(sizeof(int)* nbvars);
  int * setvals = (int*)malloc(sizeof(int)* nbvars);
  int i;
  for (i = 0; i < nbvars; i++)
  {
    counts[i] = 0;
    setvals[i] = -1;
  }
  int toReturn;
  if (solver(unin->data, nbvars, unin->nbclauses, unin->clause_lengths, counts, setvals, 0))
  {
    toReturn = 1;
  }
  else
  {
    setvals[0] = !setvals[0];
    toReturn = solver(unin->data, nbvars, unin->nbclauses, unin->clause_lengths, counts, setvals, 0);
  }


  free(counts);
  free(setvals);
  LOG("solve RETURNING", 2);
  return toReturn;
}

/*******************************************************************************************
 * NAME :             process_or
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
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
 * DESCRIPTION :      <DESCRIPTION STUBB>
 *
 * INPUTS :
 *      PARAMETERS :   
 *          UNMOLESTED_INPUT  *unin   input
 *          MOLESTED_INPUT    *in     input
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       1 on satisfiable, 0 on unsatisfiable, -1 on error
 */
int process_and(UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in)
{
  LOG("process_and CALLED", 2);
  int i, j;
  int nbvars = unin->nbvars;
  int nbclauses = unin->nbclauses;
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
      if (process_or(input, unin->data[j], unin->clause_lengths[j]) == 0)
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
 * DESCRIPTION :      <DESCRIPTION STUBB>
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

int solver(int ** values, int val_count, int num_clauses, int * clause_length, int * counts, int * setvals, int pos)
{
  if (pos >= val_count)
  {
    return 0;
  }
  if (setvals[pos] < 0)
  {
    if (counts[pos] < 0)
    {
      setvals[pos] = 0;
    }
    else
    {
      setvals[pos] = 1;
    }
  }

  int sat_level = 0;
  int i;
  for (i = 0; i < num_clauses; i++)
  {
    int clause_result = process_clause(values[i], val_count, clause_length[i], setvals);
      switch (clause_result)
      {
      case -1:
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

  if (solver(values, val_count, num_clauses, clause_length, counts, setvals, pos + 1))
  {
    return 1;
  }
  else
  {
    setvals[pos + 1] = !setvals[pos + 1];

    return solver(values, val_count, num_clauses, clause_length, counts, setvals, pos + 1);
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

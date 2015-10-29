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
  int toReturn = process_and(unin, in);
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



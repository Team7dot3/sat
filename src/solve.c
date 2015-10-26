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
 *          int                       1 on success, 0 on failure
 */
int solve(UNMOLESTED_INPUT *unin, MOLESTED_INPUT *in)
{
  LOG("solve CALLED", 2);
  
  LOG("solve RETURNING", 2);
  return 0;
}

int process_or(int* values, int* data, int datalen)
{
  LOG("process_or CALLED", 2);
  int i;
  for(i = 0; i < datalen; i++)
  {
    int val = data[i];
    if(val < 0)
    {
      val = -val;
      val = !values[val];
    }else
    {
      val = values[val];
    }
    if(val)
    {
      LOG("process_or RETURNING",2);
      return 1;
    }
  }
  LOG("process_or RETURNING",2);
  return 0;
}

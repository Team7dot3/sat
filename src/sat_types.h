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
#ifndef SAT_TYPES_H
#define SAT_TYPES_H

#include <stdio.h>
#include <assert.h>

/*******************************************************************************************
 * Color codes for printing to stdout.
 */
#define KGRN  "\x1b[32m"
#define KCYN  "\x1B[36m"
#define KRED  "\x1B[31m"
#define RESET "\033[0m"

/*******************************************************************************************
 * NAME :             LOG
 *
 * DESCRIPTION :      Prints to stdout if binary was compiled with -DDEBUG. This 
 *                    automatically appends "\n" to the input string.
 * INPUTS :
 *      PARAMETERS :   
 *          char*     str         The string to print to stdout.
 *          int       color       [1 => green], [2 => cyan], [3 => red]
 */
#ifdef DEBUG
#define LOG(str, color) { \
  switch (color)          \
  {                       \
    case 1:               \
      printf(KGRN);       \
      break;              \
    case 2:               \
      printf(KCYN);       \
      break;              \
    case 3:               \
      printf(KRED);       \
      break;              \
    default:              \
      NULL;               \
  }                       \
  printf(str);            \
  printf("\n");           \
  printf(RESET);          \
}
#else
#define LOG(str, color) { /* DO NOTHING */}
#endif

/*******************************************************************************************
 * NAME :             UNMOLESTED_INPUT
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
 */
typedef struct UNMOLESTED_INPUT
{
	int** data;
	int   nbclauses;
	int*  clause_lengths;
	int   nbvars;
} UNMOLESTED_INPUT;

/*******************************************************************************************
 * NAME :             UNMOLESTED_INPUT
 *
 * DESCRIPTION :      <DESCRIPTION STUBB>
 */
typedef struct MOLESTED_INPUT
{
	int* data;
	int length;
} MOLESTED_INPUT;

#include "input.h"
#include "solve.h"

#endif 

#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <assert.h>

typedef struct UNMOLESTED_INPUT
{
	int** data;
	int nbclauses;
	int* clause_lengths;
	int nbvars;

} UNMOLESTED_INPUT;

typedef struct MOLESTED_INPUT
{
	int* data;
	int length;
} MOLESTED_INPUT;
#endif 

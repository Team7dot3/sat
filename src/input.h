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
#ifndef INPUT_H
#define INPUT_H

#include "sat_types.h"
#include <string.h>

/*******************************************************************************************
 * NAME :             check_args
 *
 * DESCRIPTION :      Verifies the validity of the arguments.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int       argc            number of arguments
 *          char      *argv[]         input arguments
 *
 * OUTPUTS :
 *      RETURN :
 *          FILE*                       Actual FILE* on success, NULL on failure
 */
FILE* check_args(int argc, char *argv[]);

/*******************************************************************************************
 * NAME :             input_parse
 *
 * DESCRIPTION :      Parses the input from a file of the cnf sat form.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE              *fp     file
 *          INPUT             *input  input
 *
 * OUTPUTS :
 *      RETURN : 1 on success, -1 on failure/error
 */
int input_parser(FILE *fp, UNMOLESTED_INPUT *input);

/*******************************************************************************************
 * NAME :             input_string
 *
 * DESCRIPTION :      Reads a line of data from a file.
 *
 * Method based on solution from 
 * http://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
 * Username: BLUEPIXY
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp            the pointer to the file
 *          size_t      size          the number of bytes to read
 *
 * OUTPUTS :
 *      RETURN :
 *          char*                      the string read from the file on success, 
 *                                     the original string on failure
 */
char* input_string(FILE* fp, size_t size);

/*******************************************************************************************
 * NAME :             get_file_size
 *
 * DESCRIPTION :      Returns the sie of a file.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp            the pointer to the file
 *
 * OUTPUTS :
 *      RETURN :
 *          int                      the size of the file in bytes
 */
 int get_file_size(FILE* fp);

/*******************************************************************************************
 * NAME :             parse_comments
 *
 * DESCRIPTION :      Progresses the file pointer past the commentes.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp            The pointer to the file.
 *          int*        file size     The size of the file in bytes.
 *
 * OUTPUTS :
 *      RETURN :
 *          char*                     The line of the next line ("problem" line).
 */
char* parse_comments(FILE* fp, int file_size);

/*******************************************************************************************
 * NAME :             parse_cnf_header
 *
 * DESCRIPTION :      Parses the cnf header ("problem" line) of the file.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          char*       line          The cnf line.
 *          int*        nbvar         The nbvar variable.
 *          int*        nbclauses     The nbclauses variable.
 *
 * OUTPUTS :
 *      RETURN :
 *          char*                     The line of the next line ("problem" line).
 */
int parse_cnf_header(char* line, int* nbvar, int* nbclauses);

/*******************************************************************************************
 * NAME :             parse_clauses
 *
 * DESCRIPTION :      Progresses the file pointer past the commentes.
 *
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE*       fp                      The pointer to the file.
 *          int         file size               The size of the file in bytes.
 *          int**       data                    The pointer to the set of pointers to the clauses.
 *          int*        nbclauses               The number of expected clauses.
 *          int*        clause_lengths          The array of clause lengths.
 *          int*        value_sums              The array of values of units sumed. Ex. 1 and -1 would result in 0 in the '1's index.
 *
 * OUTPUTS :
 *      RETURN :
 *          int*                     1 on success, -1 on failure/error.
 */
int parse_clauses(FILE* fp, int file_size, int** data, int* nbclauses, int* clause_lengths, int* value_sums);

/*******************************************************************************************
 * NAME :             input_free
 *
 * DESCRIPTION :      Free all resources after use.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          FILE              *fp     file
 *          INPUT             *input  input
 *
 * OUTPUTS :
 *      RETURN :
 *          void
 */
void input_free(FILE *fp, UNMOLESTED_INPUT *input);

#endif

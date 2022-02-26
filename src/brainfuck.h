#include <stdlib.h>

#ifndef __BRAINFUCK_H__
#define __BRAINFUCK_H__

/**
 * Determine whether a source string has any input "," characters.
 *
 * @param source    source string
 * @return int      1 if "," found, 0 otherwise
 */
int hasInput(char * source);



/**
 * Create an array of loops from a source string.
 *
 * This creates an array with length equal to the length of the source file.
 * The majority of cells will be set to 0, but indices corresponding to loop
 * operations ("[" or "]") will contain a "pointer" to their matching
 * counterpart.
 *
 * Example: The source string ">+++++[<++++++>-]<++" will result in the
 * array
 * {0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0}.
 *
 * @param source      source string
 * @return size_t*    pointer to the loop array
 */
size_t * getLoops(char* source);


/**
 * Execute a Brainfuck program given strings for the source and input as well
 * as the width of the cells to be used.
 *
 * @param source      source string
 * @param input       input string
 * @param bitWidth    width of cells (8, 16, etc.)
 * @return int        nonzero on failure
 */
int execute(char * source, char * input, size_t bitWidth);

#endif
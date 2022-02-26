#include <stdlib.h>

#ifndef __BRAINFUCK_H__
#define __BRAINFUCK_H__

//Return whether a source has any ',' characters.
int hasInput(char * source);

/*
Create an array of loops from the source. Each index in the array points to
the other side (i.e. closed->open, open->closed).
*/
size_t * getLoops(char* source);

/*
Execute a brainfuck program given source/input strings and the width of the
cells to be used. Return nonzero on failure.
*/
int execute(char * source, char * input, size_t bitWidth);

#endif
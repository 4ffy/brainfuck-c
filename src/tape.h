#include <stdlib.h>

#ifndef __MAZE_H__
#define __MAZE_H__

typedef struct Tape Tape;
struct Tape
{
    size_t * data; //Cell memory
    size_t   cell; //Current memory index
    size_t  csize; //Maximum cell value
    size_t length; //Current length of memory
};

//Initialize a new tape object.
Tape * initTape(size_t bitWidth);

//Free a tape object from memory.
void freeTape(Tape * t);

//Reallocate tape memory to change size. Return nonzero on failure.
int resizeTape(Tape * t, size_t size);

//Move to the previous cell, if possible. Return nonzero on failure.
int moveLeft(Tape * t);

//Move to the next cell, if possible. Return nonzero on failure.
int moveRight(Tape * t);

//Add one to the current cell. Wrap around if limit reached.
void increment(Tape* t);

//Subtract one from the current cell. Wrap around if limit reached.
void decrement(Tape* t);

//Set the current cell to the given value.
void setCell(Tape* t, size_t value);

//Return the value of the current cell.
size_t getCell(Tape* t);

//Print the value of the current cell as a character, if applicable.
void printCell(Tape* t);

//Print debug tape information
void printDebug(Tape* t);

#endif
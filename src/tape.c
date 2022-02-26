#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tape.h"

//Initialize a new tape object.
Tape * initTape(size_t bitWidth)
{
    Tape * t = malloc(sizeof(Tape));
    if (t == NULL) return NULL;

    t->data = calloc(1, sizeof(size_t));
    if (t->data == NULL) return NULL;

    t->cell  = 0;
    t->csize = 2 << (bitWidth - 1);
    t->length = 1;

    return t;
}



//Free a tape object from memory.
void freeTape(Tape * t)
{
    if (t == NULL) return;
    free(t->data);
    free(t);
}



//Reallocate tape memory to change size. Return nonzero on failure.
int resizeTape(Tape * t, size_t size)
{
    t->data = realloc(t->data, size * sizeof(size_t));
    if (t->data == NULL) return 1;

    for (size_t i = t->length; i < size; i++)
        t->data[i] = 0;

    t->length = size;
    return 0;
}



//Move to the previous cell, if possible. Return nonzero on failure.
int moveLeft(Tape * t)
{
    if (t->cell > 0)
    {
        t->cell--;
        return 0;
    }
    return 1;
}



//Move to the next cell, if possible. Return nonzero on failure.
int moveRight(Tape * t)
{
    if (t->cell + 1 == t->length)
        if (resizeTape(t, t->length * 2) != 0)
            return 1;

    t->cell++;
    return 0;
}



//Add one to the current cell. Wrap around if limit reached.
void increment(Tape* t)
{
    t->data[t->cell] = (t->data[t->cell] + 1) % t->csize;
}



//Subtract one from the current cell. Wrap around if limit reached.
void decrement(Tape* t)
{
    t->data[t->cell] = (t->data[t->cell] + t->csize - 1) % t->csize;
}


//Set the current cell to the given value.
void setCell(Tape* t, size_t value)
{
    t->data[t->cell] = value;
}



//Return the value of the current cell.
size_t getCell(Tape* t)
{
    return t->data[t->cell];
}



//Print the value of the current cell as a character, if applicable.
void printCell(Tape* t)
{
    size_t cell = getCell(t);
    if (cell < CHAR_MAX)
        putchar(cell);
}



//Print debug tape information
void printDebug(Tape* t)
{
    printf(
        "Cell        : %zu\n"
        "Cell Value  : %zu\n"
        "Max Size    : %zu\n"
        "Tape Length : %zu\n"
        "\n",
        t->cell, t->data[t->cell], t->csize, t->length
    );

    printf("Memory:\n");
    for (size_t i = 0; i < t->length; i++)
        printf("%zu ", t->data[i]);

    printf("\n");
}
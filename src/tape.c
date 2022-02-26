/**
 * @file tape.c
 * @author 4ffy
 * @version 1.0.0
 * @date 2022-02-26
 * 
 * @copyright Copyright (c) 2022 4ffy
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tape.h"



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



void freeTape(Tape * t)
{
    if (t == NULL) return;
    free(t->data);
    free(t);
}



int resizeTape(Tape * t, size_t size)
{
    t->data = realloc(t->data, size * sizeof(size_t));
    if (t->data == NULL) return 1;

    for (size_t i = t->length; i < size; i++)
        t->data[i] = 0;

    t->length = size;
    return 0;
}



int moveLeft(Tape * t)
{
    if (t->cell > 0)
    {
        t->cell--;
        return 0;
    }
    return 1;
}



int moveRight(Tape * t)
{
    if (t->cell + 1 == t->length)
        if (resizeTape(t, t->length * 2) != 0)
            return 1;

    t->cell++;
    return 0;
}



void increment(Tape* t)
{
    t->data[t->cell] = (t->data[t->cell] + 1) % t->csize;
}



void decrement(Tape* t)
{
    t->data[t->cell] = (t->data[t->cell] + t->csize - 1) % t->csize;
}


void setCell(Tape* t, size_t value)
{
    t->data[t->cell] = value;
}



size_t getCell(Tape* t)
{
    return t->data[t->cell];
}



void printCell(Tape* t)
{
    size_t cell = getCell(t);
    if (cell < CHAR_MAX)
        putchar(cell);
}



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
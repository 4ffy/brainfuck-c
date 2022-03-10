/**
 * @file brainfuck.c
 * @author Cameron Norton
 * @copyright Copyright (c) 2022 Cameron Norton
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "brainfuck.h"
#include "tape.h"



int hasInput(char* source)
{
    for (char* srcptr = source; *srcptr != '\0'; srcptr++)
        if (*srcptr == ',') return 1;
    return 0;
}



size_t* getLoops(char* source)
{
    size_t srclen = strlen(source);
    size_t* loops = calloc(srclen, sizeof(size_t));
    size_t* stack = calloc(srclen, sizeof(size_t));
    size_t stackptr = 0;

    //Loop through source.
    for (size_t srcptr = 0; srcptr < srclen; srcptr++)
    {
        switch (source[srcptr])
        {
            case '[':
            stack[stackptr] = srcptr;
            stackptr++;
            break;

            case ']':
            if (!stackptr) //Stack empty
            {
                free(stack);
                free(loops);
                return NULL;
            }
            stackptr--;
            loops[srcptr] = stack[stackptr];
            loops[stack[stackptr]] = srcptr;
            stack[stackptr] = 0;
            break;
        }
    }

    if (stackptr) //stack not empty
    {
        free(stack);
        free(loops);
        return NULL;
    }

    free(stack);
    return loops;
}



int execute(char* source, char* input, size_t bitWidth)
{
    //Setup
    Tape*   tape  = initTape(bitWidth);
    size_t* loops = getLoops(source);
    if (loops == NULL)
    {
        fprintf(stderr, "Error: Couldn't create loop array (Unclosed loops?)\n");
        freeTape(tape);
        free(loops);
        return 1;
    }
    size_t srclen = strlen(source) + 1;
    size_t inplen = strlen(input) + 1;

    //Loop through source.
    size_t srcptr = 0;
    size_t inpptr = 0;
    char opcode = 0;
    for (srcptr = 0; srcptr < srclen; srcptr++)
    {
        opcode = source[srcptr];
        switch (opcode)
        {
            case '+':
            increment(tape);
            break;

            case '-':
            decrement(tape);
            break;

            case '<':
            if (moveLeft(tape))
            {
                fprintf(stderr, "Pos:%zu Op:%c\n", srcptr, opcode);
                fprintf(stderr, "Error: Couldn't move left (out of bounds?)\n");
                freeTape(tape);
                free(loops);
                return 1;
            }
            break;

            case '>':
            if (moveRight(tape))
            {
                fprintf(stderr, "Pos:%zu Op:%c\n", srcptr, opcode);
                fprintf(stderr, "Error: Couldn't move right (out of memory?)\n");
                freeTape(tape);
                free(loops);
                return 1;
            }
            break;

            case '[':
            if (!getCell(tape))
                srcptr = loops[srcptr];
            break;

            case ']':
            if (getCell(tape))
                srcptr = loops[srcptr];
            break;

            case '.':
            printCell(tape);
            break;

            case ',':
            if (inpptr < inplen)
            {
                setCell(tape, input[inpptr]);
                inpptr++;
            }
            else
            {
                setCell(tape, 0);
            }
            break;
        }
    }

    freeTape(tape);
    free(loops);
    return 0;
}

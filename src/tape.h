/**
 * @file tape.h
 * @author 4ffy
 * @copyright Copyright (c) 2022 4ffy
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

#include <stdlib.h>

#ifndef __TAPE_H__
#define __TAPE_H__

/**
 * Tape memory type.
 */
typedef struct
{
    size_t * data; /**< cell memory              */
    size_t   cell; /**< current memory cell      */
    size_t  csize; /**< maximum cell value       */
    size_t length; /**< current length of memory */
} Tape;



/**
 * Initialize a new Tape object.
 * 
 * @param bitWidth    width of cells (8 bit, 16 bit, etc.)
 * @return Tape*      pointer to the new Tape, or NULL if initialization
 *                    failed
 */
Tape * initTape(size_t bitWidth);



/**
 * Free a tape object from memory.
 * @param t    target Tape
 */
void freeTape(Tape * t);



/**
 * Reallocate tape to change its size.
 * 
 * @param t       target Tape
 * @param size    new target size
 * @return int    nonzero on failure
 */
int resizeTape(Tape * t, size_t size);



/**
 * Move to the previous cell, if possible.
 *
 * @param t       target Tape
 * @return int    nonzero on failure
 */
int moveLeft(Tape * t);



/**
 * Move to the next cell. Resize memory if necessary.
 *
 * @param t       target Tape
 * @return int    nonzero on failure
 */
int moveRight(Tape * t);



/**
 * Add one to the current cell. Wrap around if limit reached.
 *
 * @param t    target Tape
 */
void increment(Tape* t);



/**
 * Subtract one from the current cell. Wrap around if limit reached.
 *
 * @param t    target Tape
 */
void decrement(Tape* t);



/**
 * Set the current cell to the given value.
 *
 * @param t        target Tape
 * @param value    target value
 */
void setCell(Tape* t, size_t value);



/**
 * Get the value of the current cell.
 *
 * @param t          target Tape
 * @return size_t    value of the current cell
 */
size_t getCell(Tape* t);



/**
 * Print the value of the current cell as a character, if applicable.
 *
 * @param t    target Tape
 */
void printCell(Tape* t);



/**
 * Print debug tape information.
 *
 * @param t    target Tape
 */
void printDebug(Tape* t);

#endif
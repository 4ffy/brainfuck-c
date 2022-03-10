/**
 * @file main.c
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
#include <string.h>
#include <time.h>
#include "brainfuck.h"



char* readSource(char* filename)
{
    //Open file.
    FILE* inf = fopen(filename, "r");
    if (inf == NULL) return NULL;
    
    //Get size.
    fseek(inf, 0, SEEK_END);
    size_t inflen = ftell(inf);
    fseek(inf, 0, SEEK_SET);

    //Allocate memory.
    char* source = malloc(inflen + 1);
    if (source == NULL)
    {
        fclose(inf);
        return NULL;
    }

    //Read file.
    fread(source, 1, inflen, inf);
    source[inflen] = '\0';
    fclose(inf);

    return source;
}



char* readInput()
{
    char buf[100];
    fgets(buf, 100, stdin);

    char* input = malloc(strlen(buf) + 1);
    if (input == NULL) return NULL;

    strcpy(input, buf);
    input[strlen(input) - 1] = '\0';
    return input;
}



int main(int argc, char* argv[])
{
    srand(time(NULL));

    //Parse options.
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage: %s /input/file bitwidth\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t bitwidth = 8;
    if (argv[2])
        bitwidth = atoi(argv[2]);

    //Read source.
    char* source = readSource(argv[1]);
    if (source == NULL)
    {
        fprintf(stderr, "Error: couldn't read source file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    //Read input, if necessary.
    char* input = NULL;
    if (hasInput(source))
    {
        input = readInput();
        if (input == NULL)
        {
            fprintf(stderr, "Error, couldn't read input.\n");
            free(source);
            return EXIT_FAILURE;
        }
    }
    
    //Execute Brainfuck.
    execute(source, input, bitwidth);
    printf("\n");

    free(input);
    free(source);
    return EXIT_SUCCESS;
}
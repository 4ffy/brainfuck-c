#include <stdio.h>
#include <string.h>
#include <time.h>
#include "brainfuck.h"



char * readSource(char* filename)
{
    FILE* inf = fopen(filename, "r");
    if (inf == NULL) return NULL;
    
    fseek(inf, 0, SEEK_END);
    size_t inflen = ftell(inf);
    fseek(inf, 0, SEEK_SET);

    char * source = malloc(inflen + 1);
    if (source == NULL)
    {
        fclose(inf);
        return NULL;
    }

    fread(source, 1, inflen, inf);
    source[inflen] = '\0';
    
    fclose(inf);
    return source;
}



char * readInput()
{
    char buf[100];
    fgets(buf, 100, stdin);

    char * input = malloc(strlen(buf) + 1);
    if (input == NULL) return NULL;

    strcpy(input, buf);
    input[strlen(input) - 1] = '\0';
    return input;
}



int main(int argc, char * argv[])
{
    srand(time(NULL));

    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage: %s /input/file bitwidth\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t bitwidth = 8;
    if (argv[2])
        bitwidth = atoi(argv[2]);

    char * source = readSource(argv[1]);
    if (source == NULL)
    {
        fprintf(stderr, "Error: couldn't read source file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char * input = NULL;
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
    
    execute(source, input, bitwidth);
    printf("\n");

    free(input);
    free(source);
    return EXIT_SUCCESS;
}
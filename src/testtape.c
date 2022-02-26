#include <stdio.h>
#include "tape.h"

int main()
{
    Tape * tape = initTape(8);
    size_t choice = 0;
    size_t input = 0;

    while (1)
    {
        printf(
            "Tape Test:          \n"
            "  1. Move Left      \n"
            "  2. Move Right     \n"
            "  3. Increment cell \n"
            "  4. Decrement cell \n"
            "  5. Set cell       \n"
            "  6. Get cell       \n"
            "  7. Print Cell     \n"
            "  8. Quit           \n"
            "Enter Choice: "
        );
        scanf("%zu", &choice);

        switch (choice)
        {
            case 1:
                if (moveLeft(tape))
                {
                    printf("Error moving left (out of bounds?)\n");
                    freeTape(tape);
                    return EXIT_FAILURE;
                }
                break;

            case 2:
                if (moveRight(tape))
                {
                    printf("Error moving right\n");
                    freeTape(tape);
                    return EXIT_FAILURE;
                }
                break;

            case 3:
                increment(tape);
                break;

            case 4:
                decrement(tape);
                break;

            case 5:
                printf("Enter value: ");
                scanf("%zu", &input);
                setCell(tape, input);
                break;

            case 6:
                printf("%zu\n", getCell(tape));
                break;

            case 7:
                printCell(tape);
                printf("\n");
                break;

            case 8:
                freeTape(tape);
                return EXIT_SUCCESS;
        }

        printf("\n");
        printDebug(tape);
        printf("\n");
    }
}
//
// Created by David Okocha on 29/04/2026.
//

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf(
            "Usage: %s <input file> <output file>\n\n"
            "Description:\n"
            "  Reads a text file and writes a character-reversed version to an output file.\n\n"
            "Arguments:\n"
            "  <input file>    Path to the file you want to reverse\n"
            "  <output file>   Path to the output file to write to\n\n"
            "Example:\n"
            "  %s input.txt output.txt\n",
            argv[0], argv[0]
        );
        return 0;
    }
    else if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\nRun %s --help for more information.\n", argv[0], argv[0]);
        return 1;
    }

    FILE* pF = fopen(argv[1], "r"); // fOpen returns memory address of file, *pF (pointer) stores the address

    char buffer[255];
    // temporary storage for each line read from the file, holds up to 254 characters plus a null terminator

    if (pF == NULL) // if file is null, exit
    {
        printf("Couldn't open input file");
        return 1;
    }
    else // else proceed
    {
        FILE* pOutputF = fopen(argv[2], "w"); // open to write to a file

        if (pOutputF == NULL)
        {
            printf("Couldn't open output file");
            fclose(pF);
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), pF) != NULL)
        {
            size_t length = strlen(buffer);

            if (buffer[length - 1] == '\n') // if it's a new line replace with a null terminator
            {
                buffer[length - 1] = '\0';
                length -= 1; // decrement length to exclude the newline we just stripped
            }

            // use size_t because length is unsigned — if length is 0, i-- wraps to an
            // enormous number, making i < length false and stopping the loop safely
            for (size_t i = length - 1; i < length; i--)

            {
                fprintf(pOutputF, "%c", buffer[i]);
            }

            fprintf(pOutputF, "\n"); // at the end of each iteration/cycle, add a new line for better formatting
        }

        fclose(pF);
        fclose(pOutputF);
    }


    return 0;
}

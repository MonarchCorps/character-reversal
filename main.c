//
// Created by David Okocha on 29/04/2026.
//

#include <stdio.h>
#include <string.h>

int main()
{
    FILE* pF = fopen("input.txt", "r"); // fOpen returns memory address of file, *pF (pointer) stores the address

    char buffer[255];
    // temporary storage for each line read from the file, holds up to 254 characters plus a null terminator

    if (pF == NULL) // if file is null, exit
    {
        printf("Couldn't open input file");
        return 1;
    }
    else // else proceed
    {
        FILE* pOutputF = fopen("output.txt", "w"); // open to write to a file

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

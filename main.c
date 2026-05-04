#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
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
        printf(
            "Usage: %s <input file> <output file>\nRun %s --help for more information.\n",
            argv[0],
            argv[0]
        );
        return 1;
    }

    FILE* pF = fopen(argv[1], "r");

    if (pF == NULL)
    {
        perror("Failed to open input file");
        return 1;
    }

    FILE* pOutputF = fopen(argv[2], "w");

    if (pOutputF == NULL)
    {
        perror("Failed to open output file");
        fclose(pF);
        return 1;
    }

    size_t capacity = 128;
    size_t length = 0;
    int c;

    // ReSharper disable once CppDFAMemoryLeak
    char* buffer = malloc(capacity); // allocates 128 bytes on the heap

    if (buffer == NULL)
    {
        perror("Out of memory");
        fclose(pF);
        fclose(pOutputF);
        return 1;
    }

    while ((c = fgetc(pF)) != EOF)
    {
        if (c != '\n')
        {
            if (length >= capacity)
            {
                capacity *= 2;
                // ReSharper disable once CppDFAMemoryLeak
                char* temp = realloc(buffer, capacity);
                if (temp == NULL)
                {
                    perror("Out of memory");
                    free(buffer);
                    fclose(pF);
                    fclose(pOutputF);
                    // ReSharper disable once CppDFAMemoryLeak
                    return 1;
                }

                buffer = temp;
            }

            buffer[length++] = (char)c;
        }
        else
        {
            for (size_t i = length; i > 0; i--)
            {
                fputc(buffer[i - 1], pOutputF);
            }
            fputc('\n', pOutputF);
            length = 0;
        }
    }

    if (length > 0)
    {
        for (size_t i = length; i > 0; i--)
        {
            fputc(buffer[i - 1], pOutputF);
        }
        fputc('\n', pOutputF);
    }

    free(buffer);
    fclose(pF);
    fclose(pOutputF);

    // ReSharper disable once CppDFAMemoryLeak
    return 0;
}

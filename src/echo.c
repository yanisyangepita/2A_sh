#include "../include/echo.h"

void echo(char* to_echo, char* file)
{
    // If one parameter is passed:
    if (file == NULL)
    {
        if (access(to_echo, F_OK) == 0)
        {
            // print the contents of the file.
            cat(to_echo, NULL);
        }
        else
        {
            // copy the standard input to the standard output.
            printf("%s\n", to_echo);
        }
    }

    // If two parameters are passed, copy the first file to the second file.
    else
    {
        if (access(to_echo, F_OK) == 0)
        {
            touch(file);
            cp(to_echo, file);
        }
        else
        {
            FILE *filefile;
            filefile = fopen(file, "w");
            if (filefile == NULL)
                errx(EXIT_FAILURE, "file opening error");

            fputs(to_echo, filefile);
            fclose(filefile);
        }
    }
}

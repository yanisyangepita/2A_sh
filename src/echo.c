#include "../include/echo.h"

void echo(char* to_echo, char* file, char **res)
{
    char *result = *res;
    // If one parameter is passed:
    if (file == NULL)
    {
        if (access(to_echo, F_OK) == 0)
        {
            // print the contents of the file.
            cat(to_echo, NULL, &result);
        }
        else
        {
            errno = 0;
            // copy the standard input to the standard output.
            /* printf("%s\n", to_echo); */
            result = realloc(result, sizeof(char) * (strlen(to_echo) + 1));
            sprintf(result, "%s\n", to_echo);
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
            errno = 0;
            FILE *filefile;
            filefile = fopen(file, "w");
            if (filefile == NULL)
            {
                errno = E_INVALID_FILE;
                return;
            }

            fputs(to_echo, filefile);
            fclose(filefile);
        }
    }
    *res = result;
}

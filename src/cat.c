#include "../include/cat.h"

void cat(char* filename, char* options)
{
    FILE* file = NULL;
    file = fopen(filename, "r");

    if(file == NULL)
        errx(EXIT_FAILURE, "Could not open the file\n");

    char c;
    char* end = "";
    if(options != NULL && !strcmp(options, "-e"))
        end = "$";
    while((c = fgetc(file)) != EOF)
    {
        if(c == '\n')
            printf("%s", end);
        printf("%c", c);
    }

    fclose(file);
}

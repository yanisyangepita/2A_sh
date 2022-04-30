#include "../include/cp.h"

void cp(char* source, char* dest)
{
    FILE* file1 = NULL;
    FILE* file2 = NULL;

    file1 = fopen(source, "r");
    file2 = fopen(dest, "w");

    if(file1 == NULL || file2 == NULL)
        errx(EXIT_FAILURE, "not valid argument()s)\n");

    char c;
    while((c = fgetc(file1)) != EOF)
    {
        fputc(c, file2);
    }

    fclose(file1);
    fclose(file2);
}

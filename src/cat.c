/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/cat.h"


/* ------------------------------------------------------------------------- */
/* Function     : cat                                                        */
/*                                                                           */
/* Description  : if the filename is valid, cat its content                  */
/*                option : e or NULL                                         */
/* ------------------------------------------------------------------------- */
void cat(char* filename, char** options)
{
    FILE* file = NULL;
    file = fopen(filename, "r");

    if(file == NULL)
    {
        errno = E_INVALID_FILE;
        return;
    }
    char c;
    char* end = "";
    if(options != NULL)
        end = "$";
    while((c = fgetc(file)) != EOF)
    {
        if(c == '\n')
            printf("%s", end);
        printf("%c", c);
    }

    fclose(file);
}

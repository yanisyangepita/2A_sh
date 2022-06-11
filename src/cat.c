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
void cat(char* filename, char** options, char **res)
{
    char *result = *res;
    FILE* file = NULL;
    file = fopen(filename, "r");

    if(file == NULL)
    {
        errno = E_INVALID_FILE;
        return;
    }
    char c;
    size_t len = strlen(result);
    while((c = fgetc(file)) != EOF)
    {
        if(c == '\n' && options != NULL)
        {
            result = realloc(result, sizeof(char) * (len + 2));
            result[len] = '$';
            len++;
            result[len] = '\0';
        }
        result = realloc(result, sizeof(char) * (len + 2));
        result[len] = c;
        len++;
        result[len] = '\0';
    }

    fclose(file);
    *res = result;
}

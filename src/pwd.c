/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/pwd.h"


/* ------------------------------------------------------------------------- */
/* Function     : pwd                                                        */
/*                                                                           */
/* Description  : print the current work directory                           */
/* ------------------------------------------------------------------------- */
void pwd()
{
    char wd[1024];
    printf("%s", getcwd(wd, sizeof(wd)));
}


/* ------------------------------------------------------------------------- */
/* Function     : get_wd                                                     */
/*                                                                           */
/* Description  : return the current working directory                       */
/* ------------------------------------------------------------------------- */
char* get_wd()
{
    char wd[1024];
    getcwd(wd, sizeof(wd));

    char* res = malloc(sizeof(char));
    size_t i = 0;

    while(wd[i] != '\0')
    {
        res = realloc(res, sizeof(char) * (i + 2));
        res[i] = wd[i];
        i++;
    }
    res[i] = '\0';

    return res;
}

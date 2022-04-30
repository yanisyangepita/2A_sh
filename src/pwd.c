#include "../include/pwd.h"

void pwd()
{
    char wd[1000];
    printf("%s", getcwd(wd, sizeof(wd)));
}

char* get_wd()
{
    char* wd = malloc(sizeof(char) * 1000);
    getcwd(wd, sizeof(wd));

    return wd;
}

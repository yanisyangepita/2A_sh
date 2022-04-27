#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "../include/token.h"


int front()
{
   char *wd[PATH_MAX];
   getcwd(wd, PATH_MAX);
   printf("\e[H\e[2J\e[3J")


}

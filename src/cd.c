#include "../include/cd.h"

void cd(char* path)
{
    if (chdir(path) == -1)
        errx(EXIT_FAILURE, "no such directory found: %s", path);
}

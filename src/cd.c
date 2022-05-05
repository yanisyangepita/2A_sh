#include "../include/cd.h"

void cd(char* path)
{
    if (chdir(path) == -1)
    {
        errno = E_INVALID_DIR;
        return;
    }
}

#include "../include/mkdir.h"

void my_mkdir(char* directory_name)
{
    DIR* dir = opendir(directory_name);
    if (!dir)
    {
        mkdir(directory_name, S_IRWXU);
        errno = 0;
    }
    else
    {
        errno = E_INVALID_DIR;
        closedir(dir);
    }
}

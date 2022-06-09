#include "../include/rm.h"

void rm(const char* filename)
{
    int err;
    err = remove(filename);
    if (err != 0)
        errx(EXIT_FAILURE, "rm failure");
}

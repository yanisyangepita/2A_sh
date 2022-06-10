#include "../include/mv.h"

void mv(char* source, char* dest)
{
    cp(source, dest);
    rm(source);
}

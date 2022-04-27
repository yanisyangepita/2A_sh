#include "../include/touch.h"

void touch(char* filename)
{
    FILE* file;
    file = fopen(filename, "w");
    fclose(file);
}

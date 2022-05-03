/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/touch.h"


/* ------------------------------------------------------------------------- */
/* Function     : touch                                                      */
/*                                                                           */
/* Description  : create a file called filename in the working directory     */
/* ------------------------------------------------------------------------- */
void touch(char* filename)
{
    FILE* file;
    file = fopen(filename, "w");
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "../include/test_lexer.h"
#include "../include/cp.h"

int main(int argc, char** argv)
{
    if(argc == 4)
        cp(argv[2], argv[3]);
    return 0;
}

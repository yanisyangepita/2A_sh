#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "../include/test_lexer.h"
#include "../include/cat.h"

int main(int argc, char** argv)
{
    if(argc < 2)
        errx(EXIT_FAILURE, "oh no\n");

    cat(argv[1], argv[2]);

    return 0;
}

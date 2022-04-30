#include "../include/test_lexer.h"

void test_lexer(int argc, char** argv)
{
    if(argc != 2)
        errx(EXIT_FAILURE, "Need a line to parse\n");

    printf("%s\n", argv[1]);

#ifdef DEBUG
    printf("uwu\n");
#endif
}

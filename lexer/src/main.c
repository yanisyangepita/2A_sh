#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char** argv)
{
    if(argc != 2)
        errx(EXIT_FAILURE, "Need a string to lex\n");

    printf("TODO:\n");
    printf("Implement the lexer\n\n");

    printf("Cannot lex %s", argv[1]);

    return 0;
}

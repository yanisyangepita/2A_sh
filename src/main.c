#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "../include/test_lexer.h"
#include "../include/test_command.h"

int main(int argc, char** argv)
{
    test_lexer(argc, argv);
    return 0;
}

#include "../include/test_parser.h"

void test_parser(int argc, char** argv)
{
    if(argc != 2)
        errx(EXIT_FAILURE, "Need a line to parse\n");

    s_token_list tokens = create_token_list(1);
    lex(&tokens, argv[1]);

    parse(tokens);
}


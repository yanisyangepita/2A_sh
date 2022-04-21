#include "../include/test_parser.h"
#include "../include/test_lexer.h"

void test_parser(int argc, char** argv)
{
    if(argc != 2)
        errx(EXIT_FAILURE, "Need a line to parse\n");

    s_token_list tokens = create_token_list(1);
    lex(&tokens, argv[1]);

    for (size_t i = 0; i < tokens.token_count; i++)
        printf("%s\n", tokens.data[i].str);

    //parse(&tokens);
}


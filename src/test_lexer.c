#include "../include/test_lexer.h"

void test_lexer(int argc, char** argv)
{
    if(argc != 2)
        return;

    // Create the list of tokens
    s_token_list tokens;
    create_token_list(&tokens, 1);

    // Create the tree
    s_node* root_node = malloc(sizeof(s_node));
    init_tree(root_node);

    // Lexing uwu
    better_lex(&tokens, argv[1], root_node);
    //lex(&tokens, argv[1]);

    // Free the list of tokens
    //free_tokens(&tokens);
    test_free_better_tokens(&tokens);

    // Free the tree
    free_tree(root_node);
}

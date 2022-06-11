#include "../include/parse_func.h"

void parse_echo(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}


#include "../include/ast.h"

s_ast *ast_create(s_token token)
{
    s_ast *ast = malloc(sizeof(s_ast));
    if (ast == NULL)
        errx(1, "Not enough memory to create AST");
    ast->token = token;
    ast->right = NULL;
    ast->left = NULL;
    return ast;
}

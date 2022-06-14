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

void ast_free(s_ast* ast)
{
    if (ast->right == NULL && ast->left == NULL)
    {
        free(ast->token.str);
        free(ast);
    }
    else
    {
        if (ast->right != NULL)
            ast_free(ast->right);
        if (ast->left != NULL)
            ast_free(ast->left);
        free(ast->token.str);
        free(ast);
    }
}

#include "../include/parse_func.h"

void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        errno = E_NEED_PARAMETERS;
        return;
    }
}

void parse_cd(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}

void parse_clear(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right != NULL)
    {
        errno = E_NACCEPT_PARAMETERS;
        return;
    }
}

void parse_cp(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}

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

void parse_ls(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}

void parse_mkdir(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        errno = E_NEED_PARAMETERS;
        return;
    }
}

void parse_mv(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        errno = E_NEED_PARAMETERS;
        return;
    }
}

void parse_pwd(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right != NULL)
    {
        errno = E_NACCEPT_PARAMETERS;
        return;
    }
}

void parse_quit(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right != NULL)
    {
        errno = E_NACCEPT_PARAMETERS;
        return;
    }
}

void parse_rm(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        errno = E_NEED_PARAMETERS;
        return;
    }
}

void parse_touch(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}

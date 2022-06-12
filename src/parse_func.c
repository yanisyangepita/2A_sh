#include "../include/parse_func.h"

/* ------------------------------------------------------------------------- */
/* Function     : parse_cat                                                  */
/*                                                                           */
/* Description  : parse the ast with the cat token and fill tne child        */
/* ------------------------------------------------------------------------- */
void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        // Cat need to be called with at least a parameter
        errno = E_NEED_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_cd                                                   */
/*                                                                           */
/* Description  : parse the ast with the cd token and fill tne child         */
/* ------------------------------------------------------------------------- */
void parse_cd(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Cd can't be called with option
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_clear                                                */
/*                                                                           */
/* Description  : parse the ast with the clear token and fill tne child      */
/* ------------------------------------------------------------------------- */
void parse_clear(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Clear can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right != NULL)
    {
        // Clear can't be called with parameters
        errno = E_NACCEPT_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_cp                                                   */
/*                                                                           */
/* Description  : parse the ast with the cp token and fill tne child         */
/* ------------------------------------------------------------------------- */
void parse_cp(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Cp can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_echo                                                 */
/*                                                                           */
/* Description  : parse the ast with the echo token and fill tne child       */
/* ------------------------------------------------------------------------- */
void parse_echo(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Echo can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_grep                                                 */
/*                                                                           */
/* Description  : parse the ast with the grep token and fill tne child       */
/* ------------------------------------------------------------------------- */
void parse_grep(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Grep can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the left ast with the pattern
    ast->left = get_pattern(tkl, &current, end);
    if (ast->left == NULL)
    {
        // Grep need a pattern
        errno = E_NEED_PARAMETERS;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    // Grep can be called without parameters if there is a pipe !
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_ls                                                   */
/*                                                                           */
/* Description  : parse the ast with the ls token and fill tne child         */
/* ------------------------------------------------------------------------- */
void parse_ls(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_mkdir                                                */
/*                                                                           */
/* Description  : parse the ast with the mkdir token and fill tne child      */
/* ------------------------------------------------------------------------- */
void parse_mkdir(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Mkdir can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        // Mkdir nee to be called with paramaters
        errno = E_NEED_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_mv                                                   */
/*                                                                           */
/* Description  : parse the ast with the mv token and fill tne child         */
/* ------------------------------------------------------------------------- */
void parse_mv(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Mv can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        // Mv need to be called with parameters
        errno = E_NEED_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_pwd                                                  */
/*                                                                           */
/* Description  : parse the ast with the pwd token and fill tne child        */
/* ------------------------------------------------------------------------- */
void parse_pwd(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Pwd can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right != NULL)
    {
        // Pwd can't be called with parameters
        errno = E_NACCEPT_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_quit                                                 */
/*                                                                           */
/* Description  : parse the ast with the quit token and fill tne child       */
/* ------------------------------------------------------------------------- */
void parse_quit(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Quit can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right != NULL)
    {
        // Quit can't be called with parameters
        errno = E_NACCEPT_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_rm                                                   */
/*                                                                           */
/* Description  : parse the ast with the rm token and fill tne child         */
/* ------------------------------------------------------------------------- */
void parse_rm(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        // Rm need to be called with parameters
        errno = E_NEED_PARAMETERS;
        return;
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : parse_touch                                                */
/*                                                                           */
/* Description  : parse the ast with the touch token and fill tne child      */
/* ------------------------------------------------------------------------- */
void parse_touch(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    // Fill the left children with the options
    // The ast will be equal to NULL if there is no options
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        // Touch can't be called with options
        errno = E_NACCEPT_OPTION;
        return;
    }
    // Fill the right children with the parameters
    // The ast will be equal to NULL if there is no parameters
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
}

#include "../include/exec_func.h"

char* options_ls[2] = {"a", "l"};
char* options_cat[1] = {"e"};
char* options_echo[1] = {"<<"};
char* options_rm[1] = {"r"};


/* ------------------------------------------------------------------------- */
/* Function     : exec_cat                                                   */
/*                                                                           */
/* Description  : exec the ast with the cat token and fill tne res string    */
/* ------------------------------------------------------------------------- */
void exec_cat(s_ast *ast, char **res)
{
    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

    size_t len_valid = 0;
    char **valid_options = NULL;
    if (ast->left != NULL)
    {
        valid_options = get_options(len_opt, opt, 1, options_cat, &len_valid);
        if (valid_options == NULL)
        {
            errno = E_INVALID_OPTION;
            return;
        }
    }

    for (size_t i = 0; i < len_files; i++)
    {
        cat(files[i], valid_options, res);
        if (errno != 0)
            return;
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }

    if (opt != NULL)
    {
        for (size_t i = 0; i < len_opt; i++)
            free(opt[i]);
        free(opt);
    }

    if (valid_options != NULL)
        free(valid_options);
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_cd                                                    */
/*                                                                           */
/* Description  : exec the ast with the cd  token and fill tne res string    */
/* ------------------------------------------------------------------------- */
void exec_cd(s_ast *ast, char **res)
{
    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    if (files != NULL)
    {
        cd(files[0]);
        if (errno != 0)
            return;
    }
    else
    {
        char *login = getlogin();
        char *path = malloc(sizeof(char) * (7 + strlen(login)));
        path[0] = '/';
        path[1] = 'h';
        path[2] = 'o';
        path[3] = 'm';
        path[4] = 'e';
        path[5] = '/';
        path[6] = 0;
        path = strcat(path, login);
        /* printf("%s\n", path); */
        cd(path);
        {
            if (errno != 0)
                return;
        }
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
    *res = *res;
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_clear                                                 */
/*                                                                           */
/* Description  : exec the ast with the clear token and fill tne res string  */
/* ------------------------------------------------------------------------- */
void exec_clear(s_ast *ast, char **res)
{
    ast = ast;
    *res = malloc(sizeof(char) * 11);
    sprintf(*res, "\e[1;1H\e[2J");
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_cp                                                    */
/*                                                                           */
/* Description  : exec the ast with the cp token and fill tne res string     */
/* ------------------------------------------------------------------------- */
void exec_cp(s_ast *ast, char **res)
{
    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    if (len_files < 2)
    {
        errno = E_NEED2_PARAMETERS;
        return;
    }

    for (size_t i = 0; i < len_files - 1; i++)
    {
        cp(files[i], files[len_files - 1]);
        if (errno != 0)
            return;
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
    *res = *res;
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_echo                                                  */
/*                                                                           */
/* Description  : exec the ast with the echo token and fill tne res string   */
/* ------------------------------------------------------------------------- */
void exec_echo(s_ast *ast, char **res)
{
    char *result = *res;
    if (ast->right == NULL)
    {
        printf("\n");
        return;
    }

    char **files = malloc(sizeof(char));
    size_t len_files = 0;
    char **opt_files = malloc(sizeof(char));
    size_t len_opt_files = 0;
    char *param = malloc(sizeof(char));
    param[0] = 0;
    horrible_func(&files, &len_files, &opt_files, &len_opt_files, &param,
            ast->right->token);

    if (len_files != 0)
        param[strlen(param) - 1] = 0;

    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

    if (len_files != 0)
    {
        for (size_t i = 0; i < len_files; i++)
        {

            char *to_echo = malloc(sizeof(char) * (strlen(param) + 3));
            strcpy(to_echo, param);
            to_echo = strcat(to_echo, "\n");
            if (strcmp(opt_files[i], ">") == 0)
            {
                echo(to_echo, files[i], &result);
            }
            else
            {

                to_echo = strcat(to_echo, "\n");
                echo(to_echo, files[i], &result);
            }
            free(to_echo);
            if (errno != 0)
                return;
        }
    }
    else
    {
        echo(param, NULL, &result);
        if (errno != 0)
            return;
    }

    if (opt != NULL)
    {
        for (size_t i = 0; i < len_opt; i++)
            free(opt[i]);
        free(opt);
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
    free(param);
    free(opt_files);
    *res = result;
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_exit                                                  */
/*                                                                           */
/* Description  : exec the ast with the exit token and fill tne res string   */
/* ------------------------------------------------------------------------- */
void exec_exit(s_ast *ast, char **res)
{
    ast = ast;
    res = res;
    errno = EXIT;
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_grep                                                  */
/*                                                                           */
/* Description  : exec the ast with the grep token and fill tne res string   */
/* ------------------------------------------------------------------------- */
void exec_grep(s_ast *ast, char **res)
{
    char *pattern = ast->left->token.str;
    if (ast->right != NULL)
    {

        size_t len_files = 0;
        char **files = NULL;
        files = create_files(&len_files, ast->right->token);
        int print = len_files >= 2;
        for (size_t i = 0; i < len_files; i++)
            grep_file(pattern, files[i], res, print);

    }
    else
    {
        grep_buff(pattern, res);
    }

}


/* ------------------------------------------------------------------------- */
/* Function     : exec_ls                                                    */
/*                                                                           */
/* Description  : exec the ast with the ls token and fill tne res string     */
/* ------------------------------------------------------------------------- */
void exec_ls(s_ast *ast, char **res)
{
    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    size_t len_valid = 0;
    char **valid_options = NULL;
    if (ast->left != NULL)
    {
        valid_options = get_options(len_opt, opt, 2, options_ls, &len_valid);
        if (valid_options == NULL)
        {
            errno = E_INVALID_OPTION;
            return;
        }
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
        {
            if (len_files >= 2)
            {
                *res = realloc(*res, (sizeof(char)
                            * (strlen(*res) + strlen(files[i]) + 2)));
                char *tmp = *res;
                sprintf(*res, "%s%s:\n", tmp, files[i]);
            }
            ls(files[i], len_valid, opt, res);
            if (errno != 0)
                return;
            if (len_files > 1 && i != len_files - 1)
            {
                *res = realloc(*res, (sizeof(char) * (strlen(*res) + 2)));
                char *tmp = *res;
                sprintf(*res, "%s\n", tmp);
            }
        }
    }
    else
    {
        ls(NULL, len_valid, opt, res);
        return;
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }

    if (opt != NULL)
    {
        for (size_t i = 0; i < len_opt; i++)
            free(opt[i]);
        free(opt);
    }

    if (valid_options != NULL)
        free(valid_options);
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_mkdir                                                 */
/*                                                                           */
/* Description  : exec the ast with the mkdir token and fill tne res string  */
/* ------------------------------------------------------------------------- */
void exec_mkdir(s_ast *ast, char **res)
{
    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);
    else
        return;

    for (size_t i = 0; i < len_files; i++)
    {
        my_mkdir(files[i]);
        if (errno != 0)
            return;
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
    *res = *res;
}

void exec_mv(s_ast *ast, char **res)
{
    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    if (len_files < 2)
    {
        errno = E_NEED2_PARAMETERS;
        return;
    }

    for (size_t i = 0; i < len_files - 1; i++)
    {
        mv(files[i], files[len_files - 1]);
        if (errno != 0)
            return;
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
    *res = *res;
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_pwd                                                   */
/*                                                                           */
/* Description  : exec the ast with the pwd token and fill tne res string    */
/* ------------------------------------------------------------------------- */
void exec_pwd(s_ast *ast, char **res)
{
    ast = ast;
    char *pwd = get_wd();
    size_t len_pwd = strlen(pwd);
    size_t len = strlen(*res);
    *res = realloc(*res, sizeof(char) * (len + 2 + len_pwd));
    char *tmp = *res;
    sprintf(*res, "%s%s\n", tmp, pwd);
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_rm                                                    */
/*                                                                           */
/* Description  : exec the ast with the rm token and fill tne res string     */
/* ------------------------------------------------------------------------- */
void exec_rm(s_ast *ast, char **res)
{
    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);
    else
        return;

    size_t len_valid = 0;
    char **valid_options = NULL;
    if (ast->left != NULL)
    {
        valid_options = get_options(len_opt, opt, 1, options_rm, &len_valid);
        if (valid_options == NULL)
        {
            errno = E_INVALID_OPTION;
            return;
        }
    }

    for (size_t i = 0; i < len_files; i++)
    {
        rm(files[i], valid_options);
        if (errno != 0)
            return;
    }

    if (files != NULL)
    {
        /* for (size_t i = 0; i < len_files; i++) */
        /*     free(files[i]); */
        free(files);
    }
    *res = *res;
}


/* ------------------------------------------------------------------------- */
/* Function     : exec_touch                                                 */
/*                                                                           */
/* Description  : exec the ast with the touch token and fill tne res string  */
/* ------------------------------------------------------------------------- */
void exec_touch(s_ast *ast, char **res)
{
    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);
    else
        return;

    for (size_t i = 0; i < len_files; i++)
    {
        touch(files[i]);
        if (errno != 0)
            return;
    }

    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
    *res = *res;
}

/* ------------------------------------------------------------------------- */
/* Function     : exec_tree                                                  */
/*                                                                           */
/* Description  : exec the ast with the tree  token and fill tne res string  */
/* ------------------------------------------------------------------------- */
void exec_tree(s_ast *ast, char **res)
{
    ast = ast;
    char *result = *res;
    tree(&result);
    *res = result;
}

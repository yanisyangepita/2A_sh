#include "../include/exec_func.h"

void exec_echo(s_ast *ast, char **res)
{
    char *result = *res;
    if (ast->right == NULL)
    {
        printf("\n");
        return;
    }

    char **files = malloc(sizeof(char *));
    size_t len_files = 0;
    char **opt_files = malloc(sizeof(char *));
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

#ifdef DEBUG
    for (size_t i = 0; i < len_opt; i++)
        printf("opt : %s\n", opt[i]);

    for (size_t i = 0; i < len_files; i++)
        printf("files : %s\n", files[i]);

    for (size_t i = 0; i < len_opt_files; i++)
        printf("opt_files : %s\n", opt_files[i]);
    printf("param : %s\n", param);
#endif

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


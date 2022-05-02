#include "../include/parser.h"

char *str_concat(char* s1, char* s2)
{
    size_t l1 = strlen(s1);
    size_t l2 = strlen(s2);

    char *res = malloc(sizeof(char) * (l1 + l2 + 1));
    if (s1 == NULL)
        errx(1, "Not enough memory to concat str");

    for (size_t i =0; i < l1; i++)
        res[i] = s1[i];
    for (size_t i = 0; i < l2; i++)
        res[l1 + i] = s2[i];
    res[l1 + l2] = 0;

    free(s1);
    free(s2);
    return res;
}

char **create_opt(size_t *len, s_token tok)
{
    char **opt = malloc(sizeof(char *));
    char *str = malloc(sizeof(char));
    str[0] = 0;
    size_t i_str = 0;
    size_t i = 0;
    size_t i_opt = 0;
    while(tok.str[i] != 0)
    {
        if (tok.str[i] == '-')
        {
            i_str = 0;
            i++;
        }
        else if (tok.str[i] == ' ')
        {
            opt = realloc(opt, sizeof(char *) * (i_opt + 1));
            opt[i_opt] = str;
            str = malloc(sizeof(char));
            str[0] = 0;
            i_opt++;
            i_str = 0;
            i++;
        }
        else
        {
            str = realloc(str, sizeof(char) * (i_str + 2));
            str[i_str] = tok.str[i];
            i_str++;
            str[i_str] = 0;
            i++;
        }
    }
    if (i_str != 0)
    {
        opt = realloc(opt, sizeof(char *) * (i_opt + 1));
        opt[i_opt] = str;
        i_opt++;
    }
    /* free(str); */
    *len = i_opt;
    return opt;
}

char **create_files(size_t *len, s_token tok)
{
    char **files = malloc(sizeof(char *));
    char *str = malloc(sizeof(char));
    str[0] = 0;
    size_t i_str = 0;
    size_t i = 0;
    size_t i_files = 0;
    while(tok.str[i] != 0)
    {
        if (tok.str[i] == ' ')
        {
            files = realloc(files, sizeof(char *) * (i_files + 1));
            files[i_files] = str;
            str = malloc(sizeof(char));
            str[0] = 0;
            i_files++;
            i_str = 0;
            i++;
        }
        else
        {
            str = realloc(str, sizeof(char) * (i_str + 2));
            str[i_str] = tok.str[i];
            i_str++;
            str[i_str] = 0;
            i++;
        }
    }
    if (i_str != 0)
    {
        files = realloc(files, sizeof(char *) * (i_files + 1));
        files[i_files] = str;
        i_files++;
    }
    /* free(str); */
    *len = i_files;
    return files;

}

size_t found_token(s_token_list* tkl, e_token_type type,
        size_t start, size_t end)
{
    for (size_t i = start; i < end; i++)
    {
        if (tkl->data[i].token_type == type ||
                tkl->data[i].token_type == NEWLINE)
        {
            return i;
        }
    }
    return end;
}

char *concat_tokens(s_token_list* tkl, size_t start, size_t end)
{
    char *str = malloc(sizeof(char));
    str[0] = 0;
    for (size_t i = start; i < end; i++)
    {
        if (str[0] != 0)
        {
            size_t len = strlen(str);
            str = realloc(str, sizeof(char) * (len + 2));
            str[len] = ' ';
            str[len + 1] = 0;
        }
        str = str_concat(str, tkl->data[i].str);
    }
    return str;
}

s_ast *found_type(s_token_list *tkl, size_t *current, size_t end,
        e_token_type type)
{
    size_t i = *current;
    if (type == IDENTIFIER)
        i = end;
    while (i < end && tkl->data[i].token_type == type)
    {
        i++;
    }
    s_ast *ast = NULL;
    if (i != *current)
    {
        s_token tok = tkl->data[*current];
        tok.token_type = type;
        char *str = concat_tokens(tkl, *current, i);
        /* s_token *tok = malloc(sizeof(s_token)); */
        /* if (tok == NULL) */
        /*     errx(1, "not enough memory to create the token"); */
        /* create_token(tok, str, type); */
        tok.str = str;
        ast = ast_create(tok);

        /* free(tok); */
        *current = i;
        /* free(str); */
    }
    return ast;
}

void parse_echo(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

#ifdef DEBUG
    for (size_t i = 0; i < len_opt; i++)
        printf("opt : %s\n", opt[i]);
#endif
    if (opt != NULL)
    {
        for (size_t i = 0; i < len_opt; i++)
            free(opt[i]);
        free(opt);
    }
}

void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->left != NULL)
        files = create_files(&len_files, ast->right->token);

    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

#ifdef DEBUG
    for (size_t i = 0; i < len_opt; i++)
        printf("opt : %s\n", opt[i]);

    for (size_t i = 0; i < len_files; i++)
        printf("files : %s\n", files[i]);
#endif
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
}

void found_func(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    if (ast->token.token_type == ECHO)
    {
        parse_echo(ast, tkl, current, end);
    }
    else if (ast->token.token_type == CAT)
    {
        parse_cat(ast, tkl, current, end);
    }
    else
        errx(1, "Not a function :x");
}

void parse(s_token_list *tkl)
{
    s_ast *prog = ast_create(tkl->data[0]);
    size_t current_index = 0;
    size_t next_prog = 0;

    while (next_prog != tkl->token_count
            && tkl->data[next_prog].token_type != NEWLINE)
    {
        current_index++;


        next_prog = found_token(tkl, PIPE, current_index, tkl->token_count);
        found_func(prog, tkl, current_index, next_prog);
    }

#ifdef DEBUG
    ast_print(prog, 0);
#endif

    ast_free(prog);
}

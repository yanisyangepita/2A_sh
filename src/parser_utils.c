#include "../include/parser_utils.h"

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
        if (tkl->data[i].token_type != NONE)
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
        tok.str = str;
        ast = ast_create(tok);

        *current = i;
    }
    return ast;
}

void horrible_func(char ***tab_files, size_t *len_files,
        char ***tab_opt_files, size_t *len_opt_files,
        char **tab_param, s_token tok)
{
    char **files = *tab_files;
    char **opt_files = *tab_opt_files;
    char *param = *tab_param;
    size_t i = 0;

    char *str = malloc(sizeof(char));
    str[0] = 0;
    size_t i_str = 0;
    size_t file = 0;

    while (tok.str[i] != 0)
    {
        if (tok.str[i] == ' ' && file == 1)
        {
            //files append
            files = realloc(files, sizeof(char *) * (*len_files + 1));
            files[*len_files] = str;
            str = malloc(sizeof(char));
            str[0] = 0;
            (*len_files)++;
            i_str = 0;

            file = 0;
        }
        else if (tok.str[i] == '>')
        {
            //indent append str
            param = str_concat(param, str);
            str = malloc(sizeof(char));
            str[0] = 0;
            i_str = 0;

            if (tok.str[i + 1] == '>')
            {
                opt_files = realloc(opt_files, sizeof(char *) *
                        (*len_opt_files + 1));
                opt_files[*len_opt_files] = ">>";
                i++;
            }
            else
            {
                //opt_files append ">"
                opt_files = realloc(opt_files, sizeof(char *) *
                        (*len_opt_files + 1));
                opt_files[*len_opt_files] = ">";
            }
            //next is file until ' '
            (*len_opt_files)++;
            if (tok.str[i + 1] == ' ')
                i++;
            file = 1;
        }
        else
        {
            //str append char
            str = realloc(str, sizeof(char) * (i_str + 2));
            str[i_str] = tok.str[i];
            i_str++;
            str[i_str] = 0;
        }
        i++;
    }
    if (i_str != 0)
    {
        if (file == 1)
        {
            files = realloc(files, sizeof(char *) * (*len_files + 1));
            files[*len_files] = str;
            str = malloc(sizeof(char));
            str[0] = 0;
            (*len_files)++;
            i_str = 0;
        }
        else
        {
            param = str_concat(param, str);
            str = malloc(sizeof(char));
            str[0] = 0;
            i_str = 0;
        }
    }
    *tab_param = param;
    *tab_opt_files = opt_files;
    *tab_files = files;
    free(str);
}


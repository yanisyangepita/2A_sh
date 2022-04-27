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

int is_separator(s_token* token)
{
    if (token->token_type == PIPE)
        return 1;
    else if (token->token_type == NEWLINE)
        return 1;
    return 0;
}

void found_next(s_token_list* tkl, size_t *next_prog)
{
    for (size_t i = *next_prog; i < tkl->token_count; i++)
    {
        if (is_separator(&tkl->data[i]) == 1)
        {
            *next_prog = i;
            return;
        }
    }
    *next_prog = tkl->token_count;
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

void found_func(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    if (ast->token.token_type == ECHO)
    {
        ast->left = found_type(tkl, &current, end, OPTION);
        ast->right = found_type(tkl, &current, end, IDENTIFIER);
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


        found_next(tkl, &next_prog);
        found_func(prog, tkl, current_index, next_prog);
    }

#ifdef DEBUG
    ast_print(prog, 0);
#endif

    ast_free(prog);
}

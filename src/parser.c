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

void concat_ident(s_ast *ast, s_token_list* tkl, size_t index)
{
    char *res = malloc(sizeof(char));
    res[0] = 0;
    for (size_t i = 1; i < index; i++)
    {
        if (res[0] != 0)
        {
            size_t len = strlen(res);
            res = realloc(res, sizeof(char) * (len + 2));
            res[len] = ' ';
            res[len + 1] = 0;
        }
        res = str_concat(res, tkl->data[i].str);
    }
    s_token *tok = malloc(sizeof(s_token));
    if (tok == NULL)
        errx(1, "Not enough memory to create the token");

    create_token(tok, res, IDENTIFIER);
    ast->right = ast_create(*tok);

    free(res);
    free(tok);
}

void found_func(s_ast *ast, size_t next_prog, s_token_list *tkl)
{
    if (ast->token.token_type == ECHO)
    {
        printf("echo detected\n");
        concat_ident(ast, tkl, next_prog);
    }
    else
        errx(1, "Not a function :x");
}

void parse(s_token_list *tkl)
{
    s_ast *prog = malloc(sizeof(s_ast));
    size_t next_prog = 0;
    size_t nbr_prog = 0;
    while (next_prog != tkl->token_count
            && tkl->data[next_prog].token_type != NEWLINE)
    {
        nbr_prog++;

        s_ast *func = ast_create(tkl->data[next_prog]);
        prog = (s_ast*) realloc(prog, sizeof(s_ast) * nbr_prog);

        found_next(tkl, &next_prog);
        found_func(func, next_prog, tkl);
        prog[nbr_prog - 1] = *func;
    }

#ifdef DEBUG
    for (size_t i = 0; i < nbr_prog; i++)
        ast_print(&prog[i], 0);
#endif

    for (size_t i = 0; i < nbr_prog; i++)
        ast_free(&prog[i]);
}

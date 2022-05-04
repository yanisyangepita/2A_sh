#include "../include/parser.h"

static s_func reserved_func[46] =
{
    {NULL,      NUMBER},
    {NULL,      STRING},
    {NULL,  IDENTIFIER},
    {parse_cd,          CD},
    {parse_ls,          LS},
    {NULL,       MKDIR},
    {NULL,       TOUCH},
    {NULL,         PWD},
    {NULL,          RM},
    {NULL,          MV},
    {parse_cp,          CP},
    {parse_cat,         CAT},
    {parse_echo,        ECHO},
    {NULL,          IF},
    {NULL,        THEN},
    {NULL,        ELSE},
    {NULL,        ELIF},
    {NULL,          FI},
    {NULL,          DO},
    {NULL,        DONE},
    {NULL,        CASE},
    {NULL,        ESAC},
    {NULL,       WHILE},
    {NULL,       UNTIL},
    {NULL,         FOR},
    {NULL,      LBRACE},
    {NULL,      RBRACE},
    {NULL,        BANG},
    {NULL,          IN},
    {NULL,       AND_IF},
    {NULL,        OR_IF},
    {NULL,       DSEMI},
    {NULL,       DLESS},
    {NULL,      DGREAT},
    {NULL,     LESSAND},
    {NULL,    GREATAND},
    {NULL,   LESSGREAT},
    {NULL,   DLESSDASH},
    {NULL,     CLOBBER},
    {NULL,        PIPE},
    {NULL,      LPAREN},
    {NULL,      RPAREN},
    {NULL,     NEWLINE},
    {NULL,      DQUOTE},
    {NULL,      SQUOTE},
    {NULL,      OPTION}
};


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
                opt_files = realloc(opt_files, sizeof(char *) * (*len_opt_files + 1));
                opt_files[*len_opt_files] = ">>";
                i++;
            }
            else
            {
                //opt_files append ">"
                opt_files = realloc(opt_files, sizeof(char *) * (*len_opt_files + 1));
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

void parse_echo(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    char **files = malloc(sizeof(char *));
    size_t len_files = 0;
    char **opt_files = malloc(sizeof(char *));
    size_t len_opt_files = 0;
    char *param = malloc(sizeof(char));
    param[0] = 0;
    horrible_func(&files, &len_files, &opt_files, &len_opt_files, &param, ast->right->token);

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
}

void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
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

void parse_cp(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
        errx(EXIT_FAILURE, "cp : does not accept options");
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    if (len_files < 2)
        errx(EXIT_FAILURE, "cp need at least 2 parameters");
#ifdef DEBUG
    for (size_t i = 0; i < len_files - 1; i++)
        printf("cp %s into %s\n", files[i], files[len_files - 1]);
#endif
    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
}

void parse_cd(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
        errx(EXIT_FAILURE, "cd : does not accept options");
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);


#ifdef DEBUG
    if (files != NULL)
        printf("cd -> %s\n", files[0]);
    else
        printf("cd ->  ~\n");
#endif
    if (files != NULL)
    {
        for (size_t i = 0; i < len_files; i++)
            free(files[i]);
        free(files);
    }
}

void parse_ls(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_opt = 0;
    char **opt = NULL;
    if (ast->left != NULL)
        opt = create_opt(&len_opt, ast->left->token);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);


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
    if (reserved_func[ast->token.token_type].func != NULL)
        reserved_func[ast->token.token_type].func(ast, tkl, current, end);
    else
        errx(1, "Not a function :x");
}

void check_grammar(s_token_list *tkl)
{
    size_t nbr_dquote = 0;
    size_t nbr_squote = 0;
    int matching_par = 0;
    int matching_bra = 0;
    for (size_t i = 0; i < tkl->token_count; i++)
    {
        if (matching_par < 0)
            errx(EXIT_FAILURE, ") without (");
        if (matching_bra < 0)
            errx(EXIT_FAILURE, "} without {");

        if (tkl->data[i].token_type == DQUOTE)
        {
            if (i > 0 && tkl->data[i - 1].token_type == BACKSLASH)
            {
                tkl->data[i - 1].token_type = NONE;
            }
            else
            {
                nbr_dquote++;
                tkl->data[i].token_type = NONE;
            }
        }
        else if (tkl->data[i].token_type == SQUOTE)
        {
            if (i > 0 && tkl->data[i - 1].token_type == BACKSLASH)
            {
                tkl->data[i - 1].token_type = NONE;
            }
            else
            {
                nbr_squote++;;
                tkl->data[i].token_type = NONE;
            }
        }
        else if (tkl->data[i].token_type == RPAREN)
        {
            if (i > 0 && tkl->data[i - 1].token_type == BACKSLASH)
            {
                tkl->data[i - 1].token_type = NONE;
            }
            else
            {
                matching_par--;
                tkl->data[i].token_type = NONE;
            }
        }
        else if (tkl->data[i].token_type == LPAREN)
        {
            if (i > 0 && tkl->data[i - 1].token_type == BACKSLASH)
            {
                tkl->data[i - 1].token_type = NONE;
            }
            else
            {
                matching_par++;
                tkl->data[i].token_type = NONE;
            }
        }
        else if (tkl->data[i].token_type == RBRACE)
        {
            if (i > 0 && tkl->data[i - 1].token_type == BACKSLASH)
            {
                tkl->data[i - 1].token_type = NONE;
            }
            else
            {
                matching_bra--;
                tkl->data[i].token_type = NONE;
            }
        }
        else if (tkl->data[i].token_type == LBRACE)
        {
            if (i > 0 && tkl->data[i - 1].token_type == BACKSLASH)
            {
                tkl->data[i - 1].token_type = NONE;
            }
            else
            {
                matching_bra++;
                tkl->data[i].token_type = NONE;
            }
        }

    }
    if (nbr_dquote % 2 == 1)
        errx(EXIT_FAILURE, "Expecting another \"");
    if (nbr_squote % 2 == 1)
        errx(EXIT_FAILURE, "Expecting another \'");
    if (matching_par != 0)
        errx(EXIT_FAILURE, "parenthesis not matching");
    if (matching_bra != 0)
        errx(EXIT_FAILURE, "braces not matching");
}

void parse(s_token_list *tkl)
{
    if (tkl->data[0].token_type == NEWLINE)
        return;
    s_ast *prog = ast_create(tkl->data[0]);
    size_t current_index = 0;
    size_t next_prog = 0;

    check_grammar(tkl);

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

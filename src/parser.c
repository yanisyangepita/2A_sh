#include "../include/parser.h"
#include "../include/utils.h"

char* options_ls[2] = {"a", "l"};
char* options_cat[1] = {"e"};
char* options_echo[1] = {"<<"};

static s_func reserved_func[46] =
{
    {NULL,          NULL, NUMBER, 0},
    {NULL,          NULL, STRING, 0},
    {NULL,          NULL, IDENTIFIER, 0},
    {parse_cd,      NULL, CD, 0},
    {parse_ls,      NULL, LS, 0},
    {NULL,          NULL, MKDIR, 0},
    {parse_touch,   NULL, TOUCH, 0},
    {parse_pwd,     NULL, PWD, 0},
    {NULL,          NULL, RM, 0},
    {NULL,          NULL, MV, 0},
    {parse_cp,      NULL, CP, 0},
    {parse_cat,     NULL, CAT, 0},
    {parse_echo,    exec_echo, ECHO, 0},
    {NULL,          NULL, IF, 0},
    {NULL,          NULL, THEN, 0},
    {NULL,          NULL, ELSE, 0},
    {NULL,          NULL, ELIF, 0},
    {NULL,          NULL, FI, 0},
    {NULL,          NULL, DO, 0},
    {NULL,          NULL, DONE, 0},
    {NULL,          NULL, CASE, 0},
    {NULL,          NULL, ESAC, 0},
    {NULL,          NULL, WHILE, 0},
    {NULL,          NULL, UNTIL, 0},
    {NULL,          NULL, FOR, 0},
    {NULL,          NULL, LBRACE, 0},
    {NULL,          NULL, RBRACE, 0},
    {NULL,          NULL, BANG, 0},
    {NULL,          NULL, IN, 0},
    {NULL,          NULL, AND_IF, 0},
    {NULL,          NULL, OR_IF, 0},
    {NULL,          NULL, DSEMI, 0},
    {NULL,          NULL, DLESS, 0},
    {NULL,          NULL, DGREAT, 0},
    {NULL,          NULL, LESSAND, 0},
    {NULL,          NULL, GREATAND, 0},
    {NULL,          NULL, LESSGREAT, 0},
    {NULL,          NULL, DLESSDASH, 0},
    {NULL,          NULL, CLOBBER, 0},
    {NULL,          exec_pipe, PIPE, 1},
    {NULL,          NULL, LPAREN, 0},
    {NULL,          NULL, RPAREN, 0},
    {NULL,          NULL, NEWLINE, 0},
    {NULL,          NULL, DQUOTE, 0},
    {NULL,          NULL, SQUOTE, 0},
    {NULL,          NULL, OPTION, 0}
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
    pwd();
    printf("\n");
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

void exec_pipe(s_ast *prog, char **res)
{
    if (reserved_func[prog->left->token.token_type].is_pipeable
            && reserved_func[prog->right->token.token_type].is_pipeable)
        reserved_func[prog->left->token.token_type].exec(prog->left, res);
    reserved_func[prog->right->token.token_type].exec(prog->right, res);
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

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    if (tkl->data[1].token_type == NEWLINE)
        return;

#ifdef DEBUG
    for (size_t i = 0; i < len_files; i++)
        printf("files : %s\n", files[i]);
#endif

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
}
void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    ast->right = found_type(tkl, &current, end, IDENTIFIER);
    if (ast->right == NULL)
    {
        errno = E_NEED_PARAMETERS;
        return;
    }

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
        cat(files[i], valid_options);
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

void parse_cp(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    ast->left = found_type(tkl, &current, end, OPTION);
    if (ast->left != NULL)
    {
        errno = E_NACCEPT_OPTION;
        return;
    }
    ast->right = found_type(tkl, &current, end, IDENTIFIER);

    size_t len_files = 0;
    char **files = NULL;
    if (ast->right != NULL)
        files = create_files(&len_files, ast->right->token);

    if (len_files < 2)
    {
        errno = E_NEED2_PARAMETERS;
        return;
    }
#ifdef DEBUG
    for (size_t i = 0; i < len_files - 1; i++)
        printf("cp %s into %s\n", files[i], files[len_files - 1]);
#endif

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
        printf("%s\n", path);
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
                printf("%s:\n", files[i]);
            ls(files[i], len_valid, opt);
            if (errno != 0)
                return;
            if (len_files > 1 && i != len_files - 1)
                printf("\n");
        }
    }
    else
    {
        ls(NULL, len_valid, opt);
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

void call_parse_func(s_ast *ast, s_token_list *tkl, size_t current, size_t end)
{
    if (reserved_func[ast->token.token_type].parse != NULL)
    {
        reserved_func[ast->token.token_type].parse(ast, tkl, current, end);
        if (errno != 0)
            return;
    }
    else
    {
        errno = E_INVALID_FUNCTION;
        return;
    }
}

void exec_prog(s_ast *prog, char **res)
{
    if (reserved_func[prog->token.token_type].exec != NULL)
    {
        reserved_func[prog->token.token_type].exec(prog, res);
        if (errno != 0)
            return;
    }
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
        {
            errno = E_GRAMMAR_LPAR;
            return;
        }
        if (matching_bra < 0)
        {
            errno = E_GRAMMAR_LBRA;
            return;
        }

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
        errno = E_GRAMMAR_DQUOTE;
    else if (nbr_squote % 2 == 1)
        errno = E_GRAMMAR_SQUOTE;
    else if (matching_par != 0)
        errno = E_GRAMMAR_PAR;
    else if (matching_bra != 0)
        errno = E_GRAMMAR_BRA;
}

s_ast *make_prog(s_token_list *tkl, size_t start, size_t end)
{
    s_ast *prog = ast_create(tkl->data[start]);
    for (size_t i = end; i > start; i--)
    {
        if (tkl->data[i].token_type == PIPE)
        {
            prog = ast_create(tkl->data[i]);
            prog->right = ast_create(tkl->data[i + 1]);
            if (tkl->data[end].token_type != NEWLINE)
                end++;
            call_parse_func(prog->right, tkl, i + 2, end);
            prog->left = make_prog(tkl, start, i - 1);
            return prog;
        }
    }
    if (tkl->data[end].token_type != NEWLINE)
        end++;
    call_parse_func(prog, tkl, start + 1, end);
    return prog;
}

void parse(s_token_list *tkl)
{
    if (tkl->data[0].token_type == NEWLINE)
        return;

    check_grammar(tkl);
    if (errno != 0)
        return;

    s_ast *prog = make_prog(tkl, 0, tkl->token_count - 1);

    char *res = malloc(sizeof(char));
    res[0] = '\0';

    exec_prog(prog, &res);

    printf("%s", res);

    free(res);

#ifdef DEBUG
    ast_print(prog, 0);
#endif
    ast_free(prog);
}

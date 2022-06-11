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
    {/* parse_cd, */ NULL,     NULL, CD, 0},
    {/* parse_ls,*/ NULL,     NULL, LS, 0},
    {NULL,          NULL, MKDIR, 0},
    {/* parse_touch, */NULL,   NULL, TOUCH, 0},
    {/* parse_pwd, */NULL,     NULL, PWD, 0},
    {NULL,          NULL, RM, 0},
    {NULL,          NULL, MV, 0},
    {/* parse_cp, */NULL,      NULL, CP, 0},
    {/* parse_cat, */NULL,     NULL, CAT, 0},
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
    {NULL,          NULL, PIPE, 1},
    {NULL,          NULL, LPAREN, 0},
    {NULL,          NULL, RPAREN, 0},
    {NULL,          NULL, NEWLINE, 0},
    {NULL,          NULL, DQUOTE, 0},
    {NULL,          NULL, SQUOTE, 0},
    {NULL,          NULL, OPTION, 0}
};

/* void parse_pwd(s_ast *ast, s_token_list *tkl, size_t current, size_t end) */
/* { */
/*     ast->left = found_type(tkl, &current, end, OPTION); */
/*     if (ast->left != NULL) */
/*     { */
/*         errno = E_NACCEPT_OPTION; */
/*         return; */
/*     } */
/*     ast->right = found_type(tkl, &current, end, IDENTIFIER); */
/*     if (ast->right != NULL) */
/*     { */
/*         errno = E_NACCEPT_PARAMETERS; */
/*         return; */
/*     } */
/*     pwd(); */
/*     printf("\n"); */
/* } */

/* void exec_pipe(s_ast *prog, char **res) */
/* { */
/*     if (reserved_func[prog->left->token.token_type].is_pipeable */
/*             && reserved_func[prog->right->token.token_type].is_pipeable) */
/*         reserved_func[prog->left->token.token_type].exec(prog->left, res); */
/*     reserved_func[prog->right->token.token_type].exec(prog->right, res); */
/* } */

/* void parse_touch(s_ast *ast, s_token_list *tkl, size_t current, size_t end) */
/* { */
/*     ast->left = found_type(tkl, &current, end, OPTION); */
/*     if (ast->left != NULL) */
/*     { */
/*         errno = E_NACCEPT_OPTION; */
/*         return; */
/*     } */
/*     ast->right = found_type(tkl, &current, end, IDENTIFIER); */

/*     size_t len_files = 0; */
/*     char **files = NULL; */
/*     if (ast->right != NULL) */
/*         files = create_files(&len_files, ast->right->token); */

/*     if (tkl->data[1].token_type == NEWLINE) */
/*         return; */

/* #ifdef DEBUG */
/*     for (size_t i = 0; i < len_files; i++) */
/*         printf("files : %s\n", files[i]); */
/* #endif */

/*     for (size_t i = 0; i < len_files; i++) */
/*     { */
/*         touch(files[i]); */
/*         if (errno != 0) */
/*             return; */
/*     } */

/*     if (files != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_files; i++) */
/*             free(files[i]); */
/*         free(files); */
/*     } */
/* } */
/* void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end) */
/* { */
/*     ast->left = found_type(tkl, &current, end, OPTION); */
/*     ast->right = found_type(tkl, &current, end, IDENTIFIER); */
/*     if (ast->right == NULL) */
/*     { */
/*         errno = E_NEED_PARAMETERS; */
/*         return; */
/*     } */

/*     size_t len_files = 0; */
/*     char **files = NULL; */
/*     if (ast->right != NULL) */
/*         files = create_files(&len_files, ast->right->token); */

/*     size_t len_opt = 0; */
/*     char **opt = NULL; */
/*     if (ast->left != NULL) */
/*         opt = create_opt(&len_opt, ast->left->token); */

/* #ifdef DEBUG */
/*     for (size_t i = 0; i < len_opt; i++) */
/*         printf("opt : %s\n", opt[i]); */

/*     for (size_t i = 0; i < len_files; i++) */
/*         printf("files : %s\n", files[i]); */
/* #endif */

/*     size_t len_valid = 0; */
/*     char **valid_options = NULL; */
/*     if (ast->left != NULL) */
/*     { */
/*         valid_options = get_options(len_opt, opt, 1, options_cat, &len_valid); */
/*         if (valid_options == NULL) */
/*         { */
/*             errno = E_INVALID_OPTION; */
/*             return; */
/*         } */
/*     } */

/*     for (size_t i = 0; i < len_files; i++) */
/*     { */
/*         cat(files[i], valid_options); */
/*         if (errno != 0) */
/*             return; */
/*     } */

/*     if (files != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_files; i++) */
/*             free(files[i]); */
/*         free(files); */
/*     } */

/*     if (opt != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_opt; i++) */
/*             free(opt[i]); */
/*         free(opt); */
/*     } */

/*     if (valid_options != NULL) */
/*         free(valid_options); */
/* } */

/* void parse_cp(s_ast *ast, s_token_list *tkl, size_t current, size_t end) */
/* { */
/*     ast->left = found_type(tkl, &current, end, OPTION); */
/*     if (ast->left != NULL) */
/*     { */
/*         errno = E_NACCEPT_OPTION; */
/*         return; */
/*     } */
/*     ast->right = found_type(tkl, &current, end, IDENTIFIER); */

/*     size_t len_files = 0; */
/*     char **files = NULL; */
/*     if (ast->right != NULL) */
/*         files = create_files(&len_files, ast->right->token); */

/*     if (len_files < 2) */
/*     { */
/*         errno = E_NEED2_PARAMETERS; */
/*         return; */
/*     } */
/* #ifdef DEBUG */
/*     for (size_t i = 0; i < len_files - 1; i++) */
/*         printf("cp %s into %s\n", files[i], files[len_files - 1]); */
/* #endif */

/*     for (size_t i = 0; i < len_files - 1; i++) */
/*     { */
/*         cp(files[i], files[len_files - 1]); */
/*         if (errno != 0) */
/*             return; */
/*     } */

/*     if (files != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_files; i++) */
/*             free(files[i]); */
/*         free(files); */
/*     } */
/* } */

/* void parse_cd(s_ast *ast, s_token_list *tkl, size_t current, size_t end) */
/* { */
/*     ast->left = found_type(tkl, &current, end, OPTION); */
/*     if (ast->left != NULL) */
/*     { */
/*         errno = E_NACCEPT_OPTION; */
/*         return; */
/*     } */
/*     ast->right = found_type(tkl, &current, end, IDENTIFIER); */

/*     size_t len_files = 0; */
/*     char **files = NULL; */
/*     if (ast->right != NULL) */
/*         files = create_files(&len_files, ast->right->token); */


/* #ifdef DEBUG */
/*     if (files != NULL) */
/*         printf("cd -> %s\n", files[0]); */
/*     else */
/*         printf("cd ->  ~\n"); */
/* #endif */

/*     if (files != NULL) */
/*     { */
/*         cd(files[0]); */
/*         if (errno != 0) */
/*             return; */
/*     } */
/*     else */
/*     { */
/*         char *login = getlogin(); */
/*         char *path = malloc(sizeof(char) * (7 + strlen(login))); */
/*         path[0] = '/'; */
/*         path[1] = 'h'; */
/*         path[2] = 'o'; */
/*         path[3] = 'm'; */
/*         path[4] = 'e'; */
/*         path[5] = '/'; */
/*         path[6] = 0; */
/*         path = strcat(path, login); */
/*         printf("%s\n", path); */
/*         cd(path); */
/*         { */
/*             if (errno != 0) */
/*                 return; */
/*         } */
/*     } */

/*     if (files != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_files; i++) */
/*             free(files[i]); */
/*         free(files); */
/*     } */
/* } */

/* void parse_ls(s_ast *ast, s_token_list *tkl, size_t current, size_t end) */
/* { */
/*     ast->left = found_type(tkl, &current, end, OPTION); */
/*     ast->right = found_type(tkl, &current, end, IDENTIFIER); */

/*     size_t len_opt = 0; */
/*     char **opt = NULL; */
/*     if (ast->left != NULL) */
/*         opt = create_opt(&len_opt, ast->left->token); */

/*     size_t len_files = 0; */
/*     char **files = NULL; */
/*     if (ast->right != NULL) */
/*         files = create_files(&len_files, ast->right->token); */


/* #ifdef DEBUG */
/*     for (size_t i = 0; i < len_opt; i++) */
/*         printf("opt : %s\n", opt[i]); */

/*     for (size_t i = 0; i < len_files; i++) */
/*         printf("files : %s\n", files[i]); */
/* #endif */


/*     size_t len_valid = 0; */
/*     char **valid_options = NULL; */
/*     if (ast->left != NULL) */
/*     { */
/*         valid_options = get_options(len_opt, opt, 2, options_ls, &len_valid); */
/*         if (valid_options == NULL) */
/*         { */
/*             errno = E_INVALID_OPTION; */
/*             return; */
/*         } */
/*     } */

/*     if (files != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_files; i++) */
/*         { */
/*             if (len_files >= 2) */
/*                 printf("%s:\n", files[i]); */
/*             ls(files[i], len_valid, opt); */
/*             if (errno != 0) */
/*                 return; */
/*             if (len_files > 1 && i != len_files - 1) */
/*                 printf("\n"); */
/*         } */
/*     } */
/*     else */
/*     { */
/*         ls(NULL, len_valid, opt); */
/*         return; */
/*     } */

/*     if (files != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_files; i++) */
/*             free(files[i]); */
/*         free(files); */
/*     } */

/*     if (opt != NULL) */
/*     { */
/*         for (size_t i = 0; i < len_opt; i++) */
/*             free(opt[i]); */
/*         free(opt); */
/*     } */

/*     if (valid_options != NULL) */
/*         free(valid_options); */
/* } */

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

#include "../include/parser.h"

static s_func reserved_func[50] =
{
    {NULL,          NULL,       NUMBER,     0},
    {NULL,          NULL,       STRING,     0},
    {NULL,          NULL,       IDENTIFIER, 0},
    {parse_cd,      exec_cd,    CD,         0},
    {parse_ls,      exec_ls,    LS,         0},
    {parse_mkdir,   exec_mkdir, MKDIR,      0},
    {parse_touch,   exec_touch, TOUCH,      0},
    {parse_pwd,     exec_pwd,   PWD,        0},
    {parse_rm,      exec_rm,    RM,         0},
    {parse_mv,      exec_mv,    MV,         0},
    {parse_cp,      exec_cp,    CP,         0},
    {parse_cat,     exec_cat,   CAT,        0},
    {parse_echo,    exec_echo,  ECHO,       0},
    {parse_clear,   exec_clear, CLEAR,      0},
    {parse_quit,    exec_quit,  QUIT,       0},
    {NULL,          NULL,       IF,         0},
    {NULL,          NULL,       THEN,       0},
    {NULL,          NULL,       ELSE,       0},
    {NULL,          NULL,       ELIF,       0},
    {NULL,          NULL,       FI,         0},
    {NULL,          NULL,       DO,         0},
    {NULL,          NULL,       DONE,       0},
    {NULL,          NULL,       CASE,       0},
    {NULL,          NULL,       ESAC,       0},
    {NULL,          NULL,       WHILE,      0},
    {NULL,          NULL,       UNTIL,      0},
    {NULL,          NULL,       FOR,        0},
    {NULL,          NULL,       LBRACE,     0},
    {NULL,          NULL,       RBRACE,     0},
    {NULL,          NULL,       BANG,       0},
    {NULL,          NULL,       IN,         0},
    {NULL,          NULL,       AND_IF,     0},
    {NULL,          NULL,       OR_IF,      0},
    {NULL,          NULL,       DSEMI,      0},
    {NULL,          NULL,       DLESS,      0},
    {NULL,          NULL,       DGREAT,     0},
    {NULL,          NULL,       LESSAND,    0},
    {NULL,          NULL,       GREATAND,   0},
    {NULL,          NULL,       LESSGREAT,  0},
    {NULL,          NULL,       DLESSDASH,  0},
    {NULL,          NULL,       CLOBBER,    0},
    {NULL,          exec_pipe,  PIPE,       1},
    {NULL,          NULL,       LPAREN,     0},
    {NULL,          NULL,       RPAREN,     0},
    {NULL,          NULL,       NEW_LINE,   0},
    {NULL,          NULL,       DQUOTE,     0},
    {NULL,          NULL,       SQUOTE,     0},
    {NULL,          NULL,       OPTION,     0},
    {NULL,          NULL,       BACKSLASH,  0},
    {NULL,          NULL,       NONE,       0}
};

void exec_pipe(s_ast *prog, char **res)
{
    if (reserved_func[prog->left->token.token_type].is_pipeable
            && reserved_func[prog->right->token.token_type].is_pipeable)
        reserved_func[prog->left->token.token_type].exec(prog->left, res);
    reserved_func[prog->right->token.token_type].exec(prog->right, res);
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
            if (tkl->data[end].token_type != NEW_LINE)
                end++;
            call_parse_func(prog->right, tkl, i + 2, end);
            prog->left = make_prog(tkl, start, i - 1);
            return prog;
        }
    }
    if (tkl->data[end].token_type != NEW_LINE)
        end++;
    call_parse_func(prog, tkl, start + 1, end);
    return prog;
}

void parse(s_token_list *tkl)
{
    if (tkl->data[0].token_type == NEW_LINE)
        return;

    check_grammar(tkl);
    if (errno != 0)
        return;

    s_ast *prog = make_prog(tkl, 0, tkl->token_count - 1);
    if (errno != 0)
        return;

    char *res = malloc(sizeof(char));
    res[0] = '\0';

    exec_prog(prog, &res);
    if (errno != 0)
        return;

    printf("%s", res);

    free(res);

#ifdef DEBUG
    ast_print(prog, 0);
#endif
    ast_free(prog);
}

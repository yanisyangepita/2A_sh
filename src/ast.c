#include "../include/ast.h"

#ifdef DEBUG
static s_token reserved_words[49] =
{
    {"NUMBER",      NUMBER},
    {"STRING",      STRING},
    {"IDENTIFIER",  IDENTIFIER},
    {"CD",          CD},
    {"LS",          LS},
    {"MKDIR",       MKDIR},
    {"TOUCH",       TOUCH},
    {"PWD",         PWD},
    {"RM",          RM},
    {"MV",          MV},
    {"CP",          CP},
    {"CAT",         CAT},
    {"ECHO",        ECHO},
    {"CLEAR",       CLEAR},
    {"IF",          IF},
    {"THEN",        THEN},
    {"ELSE",        ELSE},
    {"ELIF",        ELIF},
    {"FI",          FI},
    {"DO",          DO},
    {"DONE",        DONE},
    {"CASE",        CASE},
    {"ESAC",        ESAC},
    {"WHILE",       WHILE},
    {"UNTIL",       UNTIL},
    {"FOR",         FOR},
    {"LBRACE",      LBRACE},
    {"RBRACE",      RBRACE},
    {"BANG",        BANG},
    {"IN",          IN},
    {"ANDIF",       AND_IF},
    {"ORIF",        OR_IF},
    {"DSEMI",       DSEMI},
    {"DLESS",       DLESS},
    {"DGREAT",      DGREAT},
    {"LESSAND",     LESSAND},
    {"GREATAND",    GREATAND},
    {"LESSGREAT",   LESSGREAT},
    {"DLESSDASH",   DLESSDASH},
    {"CLOBBER",     CLOBBER},
    {"PIPE",        PIPE},
    {"LPAREN",      LPAREN},
    {"RPAREN",      RPAREN},
    {"NEW_LINE",    NEW_LINE},
    {"DQUOTE",      DQUOTE},
    {"SQUOTE",      SQUOTE},
    {"OPTION",      OPTION},
    {"BACKSLASH",   BACKSLASH},
    {"NONE",        NONE}
};
#endif

s_ast *ast_create(s_token token)
{
    s_ast *ast = malloc(sizeof(s_ast));
    if (ast == NULL)
        errx(1, "Not enough memory to create AST");
    ast->token = token;
    ast->right = NULL;
    ast->left = NULL;
    return ast;
}

void ast_free(s_ast* ast)
{
    if (ast->right == NULL && ast->left == NULL)
    {
        free(ast->token.str);
        free(ast);
    }
    else
    {
        if (ast->right != NULL)
            ast_free(ast->right);
        if (ast->left != NULL)
            ast_free(ast->left);
        free(ast->token.str);
        free(ast);
    }
}

#ifdef DEBUG
void ast_print(s_ast *ast, int n)
{
    if (ast == NULL)
    {
        printf("null\n");
        return;
    }
    printf("AST : %s -> %s\n", reserved_words[ast->token.token_type].str,
            ast->token.str);
    for (int i = 0; i < n; i++)
        printf(" ");
    printf("{\n");
    for (int i = 0; i < n; i++)
        printf(" ");
    printf(" R : ");
    ast_print(ast->right, n + 1);
    for (int i = 0; i < n; i++)
        printf(" ");
    printf(" L : ");
    ast_print(ast->left, n + 1);
    for (int i = 0; i < n; i++)
        printf(" ");
    printf("}\n");
}
#endif

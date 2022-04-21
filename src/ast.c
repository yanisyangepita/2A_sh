#include "../include/ast.h"

#ifdef DEBUG
static s_token reserved_words[42] =
{
    {"cd",    CD},
    {"ls",    LS},
    {"mkdir", MKDIR},
    {"touch", TOUCH},
    {"pwd",   PWD},
    {"rm",    RM},
    {"mv",    MV},
    {"cp",    CP},
    {"cat",   CAT},
    {"echo",  ECHO},
    {"if",    IF},
    {"then",  THEN},
    {"else",  ELSE},
    {"elif",  ELIF},
    {"fi",    FI},
    {"do",    DO},
    {"done",  DONE},
    {"case",  CASE},
    {"esac",  ESAC},
    {"while", WHILE},
    {"until", UNTIL},
    {"for",   FOR},
    {"{",     LBRACE},
    {"}",     RBRACE},
    {"!",     BANG},
    {"in",    IN},
    {"|",     PIPE},
    {"(",     LPAREN},
    {")",     RPAREN},
    {"\0",    NEWLINE},
    {"\"",    DQUOTE},
    {"\'",    SQUOTE},
    {"&&",    AND_IF},
    {"||",    OR_IF},
    {";;",    DSEMI},
    {"<<",    DLESS},
    {">>",    DGREAT},
    {"<&",    LESSAND},
    {">&",    GREATAND},
    {"<>",    LESSGREAT},
    {"<<-",   DLESSDASH},
    {">|",    CLOBBER}
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

#ifdef DEBUG
void ast_print(s_ast *ast)
{
    if (ast == NULL)
        return;
    printf("AST : %s -> %s\n", reserved_words[ast->token.token_type].str,
            ast->token.str);
    printf("{\nR : ");
    ast_print(ast->right);
    printf("L : ");
    ast_print(ast->left);
    printf("}\n");
}
#endif

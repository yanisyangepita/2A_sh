#ifndef _2ASH_AST_H
#define _2ASH_AST_H

#include "token.h"

struct s_ast
{
    s_token token;
    struct s_ast *right;
    struct s_ast *left;
};

typedef struct s_ast s_ast;

s_ast *ast_create(s_token token);

#ifdef DEBUG
void ast_print(s_ast* ast);
#endif

#endif

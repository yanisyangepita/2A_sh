#ifndef _2ASH_AST_H
#define _2ASH_AST_H

#include "token.h"

typedef struct
{
    s_token token;
    s_ast right;
    s_ast left;
} s_ast;

s_ast *ast_create(s_token token);

#endif

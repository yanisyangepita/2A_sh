#ifndef _2ASH_PARSE_FUNC_H
#define _2ASH_PARSE_func_H

#include "ast.h"

#include "parser_utils.h"
#include "err.h"
#include <errno.h>

void parse_echo(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

#endif

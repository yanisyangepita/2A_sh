#ifndef _2ASH_PARSER_H
#define _2ASH_PARSER_H

#include "ast.h"

int is_separator(s_token* token);

void found_next(s_token_list* tkl, size_t *next_prog);

void found_func(s_ast *ast, size_t next_prog, s_token_list *tkl);

void parse(s_token_list* tkl);

#endif

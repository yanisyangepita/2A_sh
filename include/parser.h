#ifndef _2ASH_PARSER_H
#define _2ASH_PARSER_H

#include "ast.h"

int is_separator(s_token* token);

void found_next(s_token_list* tkl, size_t *next_prog);

char *concat_tokens(s_token_list *tkl, size_t start, size_t end);

s_ast *found_type(s_token_list *tkl, size_t *current, size_t end,
        e_token_type type);

void found_func(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse(s_token_list* tkl);

#endif

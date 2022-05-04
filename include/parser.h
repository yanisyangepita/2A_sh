#ifndef _2ASH_PARSER_H
#define _2ASH_PARSER_H

#include "ast.h"
#include "cat.h"
#include "err.h"
#include <errno.h>

typedef void(*func)(s_ast *ast, s_token_list *tkl, size_t cur, size_t end);

typedef struct s_func
{
    func func;
    e_token_type token_type;
}s_func;

int is_separator(s_token* token);

void found_next(s_token_list* tkl, size_t *next_prog);

char *concat_tokens(s_token_list *tkl, size_t start, size_t end);

s_ast *found_type(s_token_list *tkl, size_t *current, size_t end,
        e_token_type type);

void found_func(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse_cat(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse_cp(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse_cd(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse_ls(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse_echo(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse(s_token_list* tkl);

#endif

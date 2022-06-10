#ifndef _2ASH_PARSER_H
#define _2ASH_PARSER_H

#include "ast.h"
#include "cat.h"
#include "ls.h"
#include "cd.h"
#include "cp.h"
#include "echo.h"
#include "pwd.h"
#include "err.h"
#include <errno.h>

typedef void(*func_parse)(s_ast *ast, s_token_list *tkl, size_t cur, size_t end);
typedef void(*func_exec)(s_ast *ast);

typedef struct s_func
{
    func_parse parse;
    func_exec exec;
    e_token_type token_type;
    int is_pipeable;
}s_func;

int is_separator(s_token* token);

void found_next(s_token_list* tkl, size_t *next_prog);

char *concat_tokens(s_token_list *tkl, size_t start, size_t end);

s_ast *found_type(s_token_list *tkl, size_t *current, size_t end,
        e_token_type type);

void call_parse_func(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void parse_touch(s_ast *ast, s_token_list *tkl,
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

void parse_pwd(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void exec_echo(s_ast *prog);

void exec_pipe(s_ast *prog);

void parse(s_token_list* tkl);

#endif

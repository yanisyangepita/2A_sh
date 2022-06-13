#ifndef _2ASH_PARSER_H
#define _2ASH_PARSER_H

#include <errno.h>

#include "parse_func.h"
#include "exec_func.h"
#include "ast.h"
#include "cat.h"
#include "ls.h"
#include "cd.h"
#include "cp.h"
#include "pwd.h"
#include "err.h"

typedef void(*func_parse)(s_ast *ast, s_token_list *tkl, size_t cur, size_t end);
typedef void(*func_exec)(s_ast *ast, char **res);

typedef struct s_func
{
    func_parse parse;
    func_exec exec;
    e_token_type token_type;
    int is_pipeable;
}s_func;

void exec_and(s_ast *prog, char **res);

void exec_pipe(s_ast *prog, char **res);

void call_parse_func(s_ast *ast, s_token_list *tkl,
        size_t current, size_t end);

void exec_prog(s_ast *prog, char **res);

void check_grammar(s_token_list *tkl);

s_ast *make_prog(s_token_list *tkl, size_t start, size_t end);

void parse(s_token_list* tkl);

#endif

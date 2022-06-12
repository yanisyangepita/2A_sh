#ifndef _2ASH_PARSE_FUNC_H
#define _2ASH_PARSE_func_H

#include "ast.h"

#include "parser_utils.h"
#include "err.h"
#include <errno.h>

void parse_cat(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_cd(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_clear(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_cp(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_echo(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_grep(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_ls(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_mkdir(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_mv(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_pwd(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_quit(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_rm(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

void parse_touch(s_ast *ast, s_token_list *tkl, size_t current, size_t end);

#endif

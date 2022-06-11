#ifndef _2ASH_EXEC_FUNC_H
#define _2ASH_EXEC_FUNC_H

#include "ast.h"
#include "parser_utils.h"
#include "utils.h"

#include "cat.h"
#include "cd.h"
#include "cp.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "touch.h"

#include "err.h"
#include <errno.h>

void exec_cat(s_ast *ast, char **res);

void exec_cd(s_ast *ast, char **res);

void exec_cp(s_ast *ast, char **res);

void exec_echo(s_ast *prog, char **res);

void exec_ls(s_ast *ast, char **res);

void exec_pwd(s_ast *ast, char **res);

void exec_touch(s_ast *ast, char **res);

#endif

#ifndef _2ASH_EXEC_FUNC_H
#define _2ASH_EXEC_FUNC_H

#include "ast.h"
#include "parser_utils.h"
#include "echo.h"
#include "err.h"
#include <errno.h>

void exec_echo(s_ast *prog, char **res);

#endif

#ifndef NEW_FRONT_H
#define NEW_FRONT_H
#define PATH_MAX 4096
#define ARG_MAX 4096
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parser.h"
#include "better_lexer.h"
#include "token.h"
#include "pwd.h"
#include "ls.h"


int new_front(void);

#endif

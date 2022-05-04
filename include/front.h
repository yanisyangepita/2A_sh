#ifndef FRONT_H
#define FRONT_H
#define PATH_MAX 4096
#define ARG_MAX 4096
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "lexer.h"
#include "token.h"
#include "pwd.h"
#include "ls.h"


int front(void);

#endif

#ifndef _2ASH_GREP_H
#define _2ASH_GREP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "err.h"


void update_res(char *str, char *pattern, char **res);

void grep_file(char* pattern, char* filename, char **res);

void grep_buff(char* pattern, char **res);

#endif

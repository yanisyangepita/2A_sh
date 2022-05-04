#ifndef _2ASH_LS_H
#define _2ASH_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

#include "../include/pwd.h"
#include "../include/utils.h"


void ls(char* directory, size_t len_options, char** options);

#endif

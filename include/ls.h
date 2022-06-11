#ifndef _2ASH_LS_H
#define _2ASH_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

#include "pwd.h"
#include "utils.h"
#include "err.h"


void ls(char* directory, size_t len_options, char** options, char **res);

#endif

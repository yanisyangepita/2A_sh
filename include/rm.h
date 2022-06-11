#ifndef _2ASH_RM_H
#define _2ASH_RM_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "err.h"

void rm(char* pathname, char** option);

#endif

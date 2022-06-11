#ifndef _2ASH_MKDIR_H
#define _2ASH_MKDIR_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

#include "err.h"
#include "utils.h"

void my_mkdir(char* directory_name);

#endif

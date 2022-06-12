#ifndef _2ASH_MV_H
#define _2ASH_MV_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <dirent.h>
#include <string.h>

#include "cd.h"
#include "rm.h"
#include "cp.h"
#include "touch.h"
#include "pwd.h"

void mv(char* source, char* dest);

#endif

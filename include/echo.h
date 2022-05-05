#ifndef _2ASH_COMMANDS_H
#define _2ASH_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "touch.h"
#include "cat.h"
#include "cp.h"
#include "err.h"

void echo(char* to_echo, char* file);


#endif

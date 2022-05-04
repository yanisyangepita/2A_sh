#ifndef _2ASH_UTILS_H
#define _2ASH_UTILS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int check_option(char* option, size_t len_valid_options, char** valid_options);
int is_in_options(char* option, size_t len_final_options,
        char** final_options);
char** get_options(size_t len_opt, char** options, size_t len_valid_options,
        char** valid_options, size_t* len_final);
char* lower(char* str);
void ls_sort(size_t len_to_sort, char** to_sort);

#endif

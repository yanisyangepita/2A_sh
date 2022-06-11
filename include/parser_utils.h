#ifndef _2ASH_PARSER_UTILS_H
#define _2ASH_PARSER_UTILS_H

#include "token.h"
#include "ast.h"
#include <errno.h>

char *str_concat(char* s1, char* s2);

char **create_opt(size_t *len, s_token tok);

char **create_files(size_t *len, s_token tok);

char **create_files(size_t *len, s_token tok);

size_t found_token(s_token_list* tkl, e_token_type type,
        size_t start, size_t end);

char *concat_tokens(s_token_list* tkl, size_t start, size_t end);

s_ast *found_type(s_token_list *tkl, size_t *current, size_t end,
        e_token_type type);

void horrible_func(char ***tab_files, size_t *len_files,
        char ***tab_opt_files, size_t *len_opt_files,
        char **tab_param, s_token tok);

#endif

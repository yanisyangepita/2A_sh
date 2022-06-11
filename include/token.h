#ifndef _2ASH_TOKEN_H
#define _2ASH_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#define NB_RESERVED 43

typedef enum
{
    // Number
    NUMBER,

    // String
    STRING,

    // Identifier
    IDENTIFIER,

    // Commands
    CD, LS, MKDIR, TOUCH, PWD, RM,
    MV, CP, CAT, ECHO, CLEAR,

    // Reserved words
    IF, THEN, ELSE, ELIF, FI, DO, DONE,
    CASE, ESAC, WHILE, UNTIL, FOR,
    LBRACE, RBRACE, BANG,
    IN,

    // Operators
    AND_IF, OR_IF, DSEMI,
    DLESS,  DGREAT, LESSAND, GREATAND, LESSGREAT, DLESSDASH,
    CLOBBER,

    // Other
    PIPE, LPAREN, RPAREN, NEW_LINE, SQUOTE, DQUOTE, OPTION, BACKSLASH, NONE
} e_token_type;

typedef struct
{
    char*        str;
    e_token_type token_type;
} s_token;

typedef struct
{
    s_token* data;
    size_t token_count;
    size_t list_size;
} s_token_list;

e_token_type check_reserved(char* str);
e_token_type check_number(char* str);
void search_token(s_token* token, char* str, e_token_type token_type);
void create_token(s_token* token, char* str, e_token_type token_type);

void create_better_token(s_token* current_token, char* str,
        e_token_type token_type);
void add_better_token(s_token_list* tokens, char* str,
        e_token_type token_type);
void free_better_tokens(s_token_list* tokens);
void test_free_better_tokens(s_token_list* tokens);

void create_token_list(s_token_list* tokens, size_t list_size);
void add_token(s_token_list* tokens, s_token token);
s_token* get_token(s_token_list* tokens, size_t index);
void free_tokens(s_token_list* token);

#endif

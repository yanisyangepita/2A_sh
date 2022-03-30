#ifndef _2ASH_TOKEN_H
#define _2ASH_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#define NB_RESERVED 40

typedef enum
{
    // Number
    NUMBER,

    // String
    STRING,

    // Commands
    CD, LS, MKDIR, TOUCH, PWD, RM,
    MV, CP, CAT, ECHO,

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
    PIPE, LPAREN, RPAREN, NEWLINE
} e_token_type;

typedef struct {
    char*        str;
    e_token_type token_type;
} s_token;

e_token_type check_reserved(char* str);
s_token create_token(char* str, e_token_type token_type);
void free_token(s_token* token);

#endif

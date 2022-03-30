#ifndef _2ASH_LEXER_H
#define _2ASH_LEXER_H

#include "token.h"

typedef enum
{
    LEXER_START,
    IN_COMMAND,
    IN_PARAM,
    IN_COMMENT,
    IN_NUM,
    LEXER_DONE
} e_lexer_state;

char get_next_char();
s_token* lex(char* line);
#endif

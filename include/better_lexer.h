#ifndef _2ASH_BETTER_LEXER_H
#define _2ASH_BETTER_LEXER_H

#include "token.h"

typedef enum
{
    LEXER_START,
    LEXER_RECOGNIZED,
    LEXER_NUMBER,
    LEXER_IDENTIFIER,
    LEXER_QUOTED,
    LEXER_END,
} e_lexer_status;

typedef struct
{
    e_lexer_status status;
    s_token current_token;
} s_lexer;

void better_lex();//s_token_list* tokens, char* source);

#endif

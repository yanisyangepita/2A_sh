#ifndef _2ASH_BETTER_LEXER_H
#define _2ASH_BETTER_LEXER_H

#include "token.h"
#include "tree.h"

typedef enum
{
    LEXER_NORMAL,
    LEXER_D_QUOTED,
    LEXER_S_QUOTED,
    LEXER_END_QUOTE,
    LEXER_NEXT,
} e_lexer_status;

typedef struct
{
    e_lexer_status status;
    e_token_type current_token_type;
    char* current_str;
} s_lexer;

void better_lex(s_token_list* tokens, char* source, s_node* root_node);

#endif

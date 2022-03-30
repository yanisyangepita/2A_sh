#include "../include/token.h"

static s_token reserved_words[NB_RESERVED] =
{
    {"cd",    CD},
    {"ls",    LS},
    {"mkdir", MKDIR},
    {"touch", TOUCH},
    {"pwd",   PWD},
    {"rm",    RM},
    {"mv",    MV},
    {"cp",    CP},
    {"cat",   CAT},
    {"echo",  ECHO},
    {"if",    IF},
    {"then",  THEN},
    {"else",  ELSE},
    {"elif",  ELIF},
    {"fi",    FI},
    {"do",    DO},
    {"done",  DONE},
    {"case",  CASE},
    {"esac",  ESAC},
    {"while", WHILE},
    {"until", UNTIL},
    {"for",   FOR},
    {"{",     LBRACE},
    {"}",     RBRACE},
    {"!",     BANG},
    {"in",    IN},
    {"|",     PIPE},
    {"(",     LPAREN},
    {")",     RPAREN},
    {"\0",    NEWLINE},
    {"&&",    AND_IF},
    {"||",    OR_IF},
    {";;",    DSEMI},
    {"<<",    DLESS},
    {">>",    DGREAT},
    {"<&",    LESSAND},
    {">&",    GREATAND},
    {"<>",    LESSGREAT},
    {"<<-",   DLESSDASH},
    {">|",    CLOBBER}
};

e_token_type check_reserved(char* str)
{
    for(size_t i = 0; i < NB_RESERVED; i++)
    {
        if(!strcmp(str, reserved_words[i].str))
            return reserved_words[i].token_type;
    }

    return (e_token_type)-1;
}

s_token create_token(char* str, e_token_type token_type)
{
    if(token_type != NUMBER && token_type != STRING)
        token_type = check_reserved(str);

    s_token token = {str, token_type};

    return token;
}

void free_token(s_token* token)
{
    free(token);
}

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
    {"\"",    DQUOTE},
    {"\'",    SQUOTE},
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

    if(str[0] >= '0' && str[0] <= '9')
        errx(EXIT_FAILURE, "check_reserved: Not a valid token\n");
    else
    {
        return IDENTIFIER;
    }
}

e_token_type check_number(char* str)
{
    char* p = str;
    while(*p != '\0')
    {
        if(*p < '0' || *p > '9')
            return IDENTIFIER;

        p += 1;
    }

    return NUMBER;
}

void search_token(s_token* token, char* str, e_token_type token_type)
{
    if(token_type == NUMBER)
        token_type = check_number(str);
    else
        token_type = check_reserved(str);

    token->str = str;
    token->token_type = token_type;
}

void create_token(s_token* token, char* str, e_token_type token_type)
{
    if(token_type == NEWLINE)
        token->str = "\0";
    else
    {
        token->str = malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(token->str, str);
    }
    token->token_type = token_type;
}

void create_token_list(s_token_list* tokens, size_t list_size)
{
    tokens->data = (s_token*) malloc(sizeof(s_token) * list_size);
    tokens->token_count = 0;
    tokens->list_size = list_size;
}

void add_token(s_token_list* tokens, s_token token)
{
    if(tokens->token_count >= tokens->list_size)
    {
        tokens->list_size *= 2;
        tokens->data = (s_token*) realloc(tokens->data,
                sizeof(s_token) * tokens->list_size);
    }

    s_token *new_token = &tokens->data[tokens->token_count];
    create_token(new_token, token.str, token.token_type);
    tokens->data[tokens->token_count] = *new_token;
    tokens->token_count += 1;
}

s_token* get_token(s_token_list* tokens, size_t index)
{
    return &tokens->data[index];
}

void free_tokens(s_token_list* tokens)
{
    for(size_t i = 0; i < tokens->token_count; i++)
    {
        if(i < tokens->token_count - 1)
            free(tokens->data[i].str);
    }

    free(tokens->data);
}

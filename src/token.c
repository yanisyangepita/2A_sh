/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/token.h"

/* ------------------------------------------------------------------------- */
/* STATIC VARIABLE                                                           */
/* Type         : s_token                                                    */
/* Name         : reserved_words                                             */
/* Description  : database of the reserved_words                             */
/* ------------------------------------------------------------------------- */
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


/* ------------------------------------------------------------------------- */
/* Function     : check_reserved                                             */
/*                                                                           */
/* Description  : if the string is in the database                           */
/*                   return the corresponding token_type                     */
/*                else                                                       */
/*                   return the IDENTIFIER token_type                        */
/* ------------------------------------------------------------------------- */
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


/* ------------------------------------------------------------------------- */
/* Function     : check_number                                               */
/*                                                                           */
/* Description  : if the string is a number                                  */
/*                   return the NUMBER token_type                            */
/*                else                                                       */
/*                   return the IDENTIFIER token_type                        */
/* ------------------------------------------------------------------------- */
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


/* ------------------------------------------------------------------------- */
/* Function     : search_token                                               */
/*                                                                           */
/* Description  : search the right token_type                                */
/*                assign the value of the attributes of the token            */
/* ------------------------------------------------------------------------- */
void search_token(s_token* token, char* str, e_token_type token_type)
{
    if(token_type == NUMBER)
        token_type = check_number(str);
    else
        token_type = check_reserved(str);

    token->str = str;
    token->token_type = token_type;
}


/* ------------------------------------------------------------------------- */
/* Function     : create_token                                               */
/*                                                                           */
/* Description  : assign the value of the attributes of the token            */
/* ------------------------------------------------------------------------- */
void create_token(s_token* token, char* str, e_token_type token_type)
{
    if(token_type == NEWLINE)
        token->str = "\0";
    else if(token_type == BACKSLASH)
        token->str = "\\";
    else
    {
        token->str = malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(token->str, str);
    }
    token->token_type = token_type;
}


/* ------------------------------------------------------------------------- */
/* Function     : create_token_list                                          */
/*                                                                           */
/* Description  : initialize and assign the value of the attributes of the   */
/*                token_list                                                 */
/* ------------------------------------------------------------------------- */
void create_token_list(s_token_list* tokens, size_t list_size)
{
    tokens->data = (s_token*) malloc(sizeof(s_token) * list_size);
    tokens->token_count = 0;
    tokens->list_size = list_size;
}


/* ------------------------------------------------------------------------- */
/* Function     : add_token                                                  */
/*                                                                           */
/* Description  : add the token to the token_list                            */
/* ------------------------------------------------------------------------- */
void add_token(s_token_list* tokens, s_token token)
{
    if(tokens->token_count >= tokens->list_size)
    {
        tokens->list_size *= 2;
        tokens->data = (s_token*) realloc(tokens->data,
                sizeof(s_token) * tokens->list_size);
    }

    if(token.token_type == OPTION || token.token_type == STRING)
        tokens->data[tokens->token_count] = token;
    else
    {
        s_token *new_token = &tokens->data[tokens->token_count];
        create_token(new_token, token.str, token.token_type);
        tokens->data[tokens->token_count] = *new_token;
    }
    tokens->token_count += 1;
}


/* ------------------------------------------------------------------------- */
/* Function     : get_token                                                  */
/*                                                                           */
/* Description  : get the token of the token_list at the index               */
/* ------------------------------------------------------------------------- */
s_token* get_token(s_token_list* tokens, size_t index)
{
    return &tokens->data[index];
}


/* ------------------------------------------------------------------------- */
/* Function     : free_tokens                                                */
/*                                                                           */
/* Description  : free the token_list                                        */
/* ------------------------------------------------------------------------- */
void free_tokens(s_token_list* tokens)
{
    for(size_t i = 0; i < tokens->token_count; i++)
    {
        if(i < tokens->token_count - 1
                && tokens->data[i].token_type != BACKSLASH)
            free(tokens->data[i].str);
    }

    free(tokens->data);
}

#include "../include/lexer.h"

void lex(s_token_list* tokens, char* source)
{
    char* lex = malloc(sizeof(char) * 128);
    size_t lex_index = 0 ;
    size_t i = 0;

    while(1)
    {
        // create the token str until a delimiter
        while(source[i] != '\0' && source[i] != '\n'
                && source[i] != ' ' && source[i] != '\t')
        {
            // BRACES
            // PAREN
            // STRINGS
            lex[lex_index] = source[i];
            lex_index += 1;
            i += 1;
        }

        lex[lex_index] = '\0';

        // Skip empty lines and tabs
        if(lex_index == 0 && (source[i] == '\n' || source[i] == '\t'))
        {
            i += 1;
            continue;
        }

        // Create a token
        s_token token;

        // - NUMBER
        if(lex[0] >= '0' && lex[0] <= '9')
            search_token(&token, lex, NUMBER);
        // - OTHER
        else
            search_token(&token, lex, (e_token_type)-1);

        // Add the token to the list
        add_token(tokens, token);

        // End of the source
        if(source[i] == '\0')
            break;

        // update the indexes
        lex_index = 0;
        i += 1;
    }

    // NEWLINE
}

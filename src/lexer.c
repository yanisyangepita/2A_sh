#include "../include/lexer.h"

void lex(s_token_list* tokens, char* source)
{
    char* lex = malloc(sizeof(char) * 128);
    size_t lex_index = 0 ;
    size_t i = 0;
    int b_is_squote = 0;
    int b_is_dquote = 0;
    int b_break = 0;

    // Create a token
    s_token token;

    while(1)
    {
        // create the token str until a delimiter
        while(source[i] != '\0' && source[i] != '\n'
                && (source[i] != ' ' || b_is_squote || b_is_dquote)
                && source[i] != '\t' && !b_break)
        {
            lex[lex_index] = source[i];
            lex_index += 1;

            // NUMBER) / LETTER)
            if(source[i + 1] == ')')
                b_break = 1;
            // STRINGS
            else if(source[i] == '\"' && !b_is_squote)
            {
                if(b_is_dquote)
                    b_is_dquote = 0;
                else
                    b_is_dquote = 1;
                b_break = 1;
            }
            else if (source[i] == '\'' && !b_is_dquote)
            {
                if(b_is_squote)
                    b_is_squote = 0;
                else
                    b_is_squote = 1;
                b_break = 1;
            }
            // BRACES / PAREN
            else if(lex[lex_index - 1] == '('
                    || lex[lex_index - 1] == ')'
                    || lex[lex_index - 1] == '{'
                    || lex[lex_index - 1] == '}')
                b_break = 1;
            i += 1;
            if((source[i] == '\"' && b_is_dquote)
                    || (source[i] == '\'' && b_is_squote))
                b_break = 1;
        }

        lex[lex_index] = '\0';

        // End of the source
        if(source[i] == '\0')
            break;

        // Skip empty lines and tabs
        if(lex_index == 0 && (source[i] == '\n' || source[i] == '\t'
                    || source[i] == ' '))
        {
            i += 1;
            continue;
        }


        // - STRING
        if((b_is_squote && lex[0] != '\'') || (b_is_dquote && lex[0] != '\"'))
            create_token(&token, lex, STRING);
        // - NUMBER
        else if(lex[0] >= '0' && lex[0] <= '9')
            search_token(&token, lex, NUMBER);
        // - OTHER
        else
            search_token(&token, lex, (e_token_type)-1);

        // Add the token to the list
        add_token(tokens, token);

        // update the indexes
        lex_index = 0;
        b_break = 0;
    }

    // NEWLINE
    create_token(&token, '\0', NEWLINE);
#ifdef DEBUG
    printf("\\0 -> NEWLINE");
#endif
    add_token(tokens, token);

    free(lex);
}

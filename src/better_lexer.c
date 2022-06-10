/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/lexer.h"
#include "../include/better_lexer.h"


/* ------------------------------------------------------------------------- */
/* Function     : is_separator                                               */
/*                                                                           */
/* Description  : if the character is the end of a token                     */
/*                    return 1 (true)                                        */
/*                else                                                       */
/*                    return 0 (false)                                       */
/* ------------------------------------------------------------------------- */
int is_separator(e_lexer_status status, char character)
{
    if(character == '\0' ||
            (status != LEXER_D_QUOTED && status != LEXER_S_QUOTED
             && (character == '\t' || character == '\n' || character == ' ')))
        return 1;

    return 0;
}


/* ------------------------------------------------------------------------- */
/* Function     : is_special                                                 */
/*                                                                           */
/* Description  : if the character is special                                */
/*                    return 1 (true)                                        */
/*                else                                                       */
/*                    return 0 (false)                                       */
/* ------------------------------------------------------------------------- */
int is_special(e_lexer_status status, char character)
{
    if(status != LEXER_D_QUOTED && status != LEXER_S_QUOTED
             && (character == '{' || character == '}'
                 || character == '(' || character == ')'
                 || character == '!' || character == '|'
                 || character == '\\'))
        return 1;

    return 0;
}



/* ------------------------------------------------------------------------- */
/* Function     : better_lex                                                 */
/*                                                                           */
/* Description  : lex the source and fill the token_list but opti            */
/* ------------------------------------------------------------------------- */
void better_lex(s_token_list* tokens, char* source, s_node* root_node)
{
    // Initialize the lexer
    s_lexer* lexer = malloc(sizeof(s_lexer));
    lexer->status = LEXER_NORMAL;

    while(*source != 0)
    {
        // Initialize the status, type and str of the current_token
        if(lexer->status != LEXER_D_QUOTED && lexer->status != LEXER_S_QUOTED)
            lexer->status = LEXER_NORMAL;

        lexer->current_token_type = NONE;
        lexer->current_str = malloc(sizeof(char));
        size_t current_len = 0;

        // get the str of the token
        while(!is_separator(lexer->status, *source)
                && lexer->status != LEXER_END_QUOTE
                && lexer->status != LEXER_NEXT
                && lexer->current_token_type == NONE)
        {
            // update the str of the current token
            lexer->current_str = realloc(lexer->current_str,
                    sizeof(char) * (current_len + 2));
            lexer->current_str[current_len] = *source;
            current_len++;

            // <d_quote> <s_quote>
            if(*(source - 1) != '\\')
            {
                if(*source == '"')
                {
                    if(lexer->status == LEXER_D_QUOTED)
                        lexer->status = LEXER_END_QUOTE;
                    else
                        lexer->status = LEXER_D_QUOTED;

                    lexer->current_token_type = DQUOTE;
                }
                else if (*source == '\'')
                {
                    if(lexer->status == LEXER_S_QUOTED)
                        lexer->status = LEXER_END_QUOTE;
                    else
                        lexer->status = LEXER_S_QUOTED;

                    lexer->current_token_type = SQUOTE;
                }
            }

            // go to the next character of the source
            source++;

            if(*(source - 1) != '\\' &&
                    ((*source == '\'' && lexer->status == LEXER_S_QUOTED)
                     || (*source == '"' && lexer->status == LEXER_D_QUOTED)))
            {
                lexer->current_token_type = STRING;
            }
            else if(is_special(lexer->status, *source)
                        || is_special(lexer->status, *(source - 1)))
            {
                lexer->status = LEXER_NEXT;
            }
        }

        lexer->current_str[current_len] = 0;

        if(lexer->current_str[0] == 0)
        {
            source++;
            free(lexer->current_str);
            continue;
        }

        // Set the token_type of the current token
        else if(lexer->current_token_type == NONE)
        {
            if(lexer->current_str[0] == '-')
                lexer->current_token_type = OPTION;
            else
            {
                // Check the tree with the str
                lexer->current_token_type =
                    check_tree(root_node, lexer->current_str);

                // if the tree did not recognize the token
                // check if the token is a number or an identifier
                if(lexer->current_token_type == NONE)
                    lexer->current_token_type =
                        check_number(lexer->current_str);
            }
        }

        // Add the token to the list of tokens
        add_better_token(tokens, lexer->current_str,
                lexer->current_token_type);
    }

    // add the newline token at the end of the token list
    lexer->current_token_type = NEWLINE;
    lexer->current_str = "";
    add_better_token(tokens, lexer->current_str,
            lexer->current_token_type);

    // Free the lexer
    free(lexer);

#ifdef DEBUG
    for(size_t i = 0; i < tokens->token_count; i++)
        printf("%s\n", tokens->data[i].str);
#endif
}

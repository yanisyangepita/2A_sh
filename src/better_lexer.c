/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/lexer.h"
#include "../include/better_lexer.h"


/* ------------------------------------------------------------------------- */
/* Function     : better_lex                                                 */
/*                                                                           */
/* Description  : lex the source and fill the token_list but opti            */
/* ------------------------------------------------------------------------- */
void better_lex()//s_token_list* tokens, char* source)
{
    // Initialize the lexer
    //s_lexer* lexer = malloc(sizeof(s_lexer));
    //lexer->status = LEXER_START;
    //lexer->current_token =

    // if the end of input is recognized
        // the current token shall be delimited

    // if the previous character was used as part of an operator
    // and the current character is not quoted
        // if it can be used with the previous charaters to form an operator
            // used as part of that token
        // else
            // extend the token

    // if the current character is <backslash>, <single-quote> or
    // <double -quote> and is not quoted
        // affect quoting for characters up to the end of the quoted text

    // if the current character is not quoted and can be used as first
    // character of a new operator
        // the current token shall start with the current character

    // if the current character is an unquoted <blank>
        // any token containing the previous character is delimited
        // the current character shall be discarded

    // if the previous character was part of a word
        // the current character is appended to that word

    // else the current character is used as the start of a new word
}

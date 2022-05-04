#include "../include/front.h"

static s_err reserved_err[] =
{
    {"Command not found", E_INVALID_FUNCTION},
    {"Expecting another \"", E_GRAMMAR_DQUOTE},
    {"Expecting another \'", E_GRAMMAR_SQUOTE},
    {"Parenthesis not matching", E_GRAMMAR_PAR},
    {"Braces not matching", E_GRAMMAR_BRA},
    {") without (", E_GRAMMAR_LPAR},
    {"} without {", E_GRAMMAR_LBRA},
    {"This function does not accept any options", E_NACCEPT_OPTION},
    {"This function need at least 2 parameters", E_NEED2_PARAMETERS},
    {"Invalid option", E_INVALID_OPTION},
    {"This function need a parameter", E_NEED_PARAMETERS}

};

void check_error()
{
    if (errno != 0)
    {
        printf("\033[1;31m");
        printf("2A-SH");
        printf("\033[5;31m");
        printf(" ! ERROR ! ");
        printf("\033[0m");
        printf("%s", reserved_err[errno - 1].err_msg);
        printf("\033[1;31m");
        printf("\033[5;31m");
        printf(" ! ERROR ! ");
        printf("\033[0m");
        printf("\n");
        errno = 0;
    }
}

int front(void)
{
    char *wd;
    wd = get_wd();


    printf("\e[H\e[2J\e[3J"); //clean the terminal

    puts(
"       ::::::::      :::                                ::::::::  :::    :::\n"
"     :+:    :+:   :+: :+:                             :+:    :+: :+:    :+:  \n"
"          +:+   +:+   +:+                            +:+        +:+    +:+   \n"
"       +#+    +#++:++#++:      +#++:++#++:++        +#++:++#++ +#++:++#++    \n"
"    +#+      +#+     +#+                                  +#+ +#+    +#+     \n"
"  #+#       #+#     #+#                           #+#    #+# #+#    #+#      \n"
"########## ###     ###                            ########  ###    ###       \n"
        );

    sleep(3);
    printf("\e[H\e[2J\e[3J");
    char *login = getlogin();

    if(login == NULL)
        errx(EXIT_FAILURE, "Login is null");

    int cond = 42;
    char* input = calloc(ARG_MAX, sizeof(char));
    char* buffer = calloc(ARG_MAX, sizeof(char));

    printf("2A-SH <%s: %s>$ ",login, wd);

    while(cond)
    {
        input = fgets(buffer, ARG_MAX, stdin);

        //Val shenanigans, IDK what it does
        s_token_list tokens;
        create_token_list(&tokens, 1);
        lex(&tokens, input);
        parse(&tokens);
        free_tokens(&tokens);

        check_error();

        printf("2A-SH <%s: %s>$ ",login, wd);
    }

    free(wd);
    free(input);
    free(buffer);
    return EXIT_SUCCESS;
}

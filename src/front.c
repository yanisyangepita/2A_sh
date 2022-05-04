#include "../include/front.h"

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

    while(cond)
    {
        char* input = calloc(ARG_MAX, sizeof(char));
        printf("2A-SH <%s: %s>$ ",login, wd);
        if (scanf("%[^\n]", input) == 0)
        {
            input[0] = ' ';
            input[1] = 0;
        }

        //Val shenanigans, IDK what it does
        if (input[0] == '\n')
            printf("bip boop");
        s_token_list tokens;
        create_token_list(&tokens, 1);
        lex(&tokens, input);
        parse(&tokens);
        free_tokens(&tokens);
        free(input);
        sleep(1);
    }

    free(wd);
    return EXIT_SUCCESS;
}

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
    char* input = calloc(ARG_MAX, sizeof(char));

    printf("2A-SH <%s: %s>$ ",login, wd);

    while(cond)
    {
        scanf("%[^\n]", input);

        //Val shenanigans, IDK what it does

        s_token_list tokens;
        create_token_list(&tokens, 1);
        lex(&tokens, input);
        parse(&tokens);
        free_tokens(&tokens);

        printf("2A-SH <%s: %s>$ ",login, wd);
    }

    free(wd);
    free(input);
    return EXIT_SUCCESS;
}

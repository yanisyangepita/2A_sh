#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>

#include "../include/front.h"
#include "../include/token.h"







int front(void)
{
    char wd[PATH_MAX];
    getcwd(wd, PATH_MAX);
    printf("\e[H\e[2J\e[3J"); //clean the terminal

    puts(
"       ::::::::      :::                                ::::::::  :::    :::\n"
"    :+:    :+:   :+: :+:                             :+:    :+: :+:    :+:  \n"
"          +:+   +:+   +:+                            +:+        +:+    +:+   \n"
"       +#+    +#++:++#++:      +#++:++#++:++        +#++:++#++ +#++:++#++    \n"
"    +#+      +#+     +#+                                  +#+ +#+    +#+     \n"
"  #+#       #+#     #+#                           #+#    #+# #+#    #+#      \n"
"########## ###     ###                            ########  ###    ###       \n"
        );

    sleep(5);
    printf("\e[H\e[2J\e[3J");
    char *login = getlogin();

    if(login == NULL)
        errx(EXIT_FAILURE, "Login is null");

    int cond = 42;
    char* input = calloc(ARG_MAX, sizeof(char));

    printf("[%s: %s]$ ",login, wd);
    cond = scanf("%s", input);

    while(cond)
    {
        //Val shenanigans, IDK what it does

        s_token_list tokens;
        create_token_list(&tokens, 1);
        lex(&tokens, input);
        parse(&tokens);
        free_tokens(&tokens);

        /* printf("var : %s\n", input); */
        printf("<%s: %s>$ ",login, wd);
        cond = scanf("%s", input);
    }

    free(input);
    return EXIT_SUCCESS;
}

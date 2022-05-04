#include "../include/test_command.h"

char* options_ls[2] = {"a", "l"};
char* options_cat[1] = {"e"};
char* options_echo[1] = {"<<"};
char* test[4] = {"a", "b", "c", "d"};

void test_command()
{
    char* options[] = {"e", "e", "e"};
    size_t len_final_options;
    char** final_options = get_options(3, options, 1, options_cat,
            &len_final_options);

    if(final_options == NULL)
        printf("The options given are not valid\n");
    else
    {
        printf("\nThe list of final options are\n");
        for(size_t i = 0; i < len_final_options; i++)
            printf("-%s ", final_options[i]);

        free(final_options);
    }
}

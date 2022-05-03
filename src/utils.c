/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/utils.h"


/* ------------------------------------------------------------------------- */
/* Function     : get_file_name                                              */
/*                                                                           */
/* Description  : if the option is in the valid_options list                 */
/*                   return 1                                                */
/*                else                                                       */
/*                   return 0                                                */
/* ------------------------------------------------------------------------- */
int check_option(char* option, size_t len_valid_options, char** valid_options)
{
    for(size_t i = 0; i < len_valid_options; i++)
    {
        if(!strcmp(valid_options[i], option))
        {
#ifdef DEBUG
            printf("-%s is a valid option\n", option);
#endif
            return 1;
        }
    }

#ifdef DEBUG
    printf("-%s is not a valid option\n", option);
#endif

    return 0;
}


/* ------------------------------------------------------------------------- */
/* Function     : is_in_options                                              */
/*                                                                           */
/* Description  : if the option is already in the final_options list         */
/*                   return 1                                                */
/*                else                                                       */
/*                   return 0                                                */
/* ------------------------------------------------------------------------- */
int is_in_options(char* option, size_t len_final_options,
        char** final_options)
{
    for(size_t i = 0; i < len_final_options; i++)
    {
        if(!strcmp(final_options[i], option))
        {
#ifdef DEBUG
            printf("-%s is already in the final_options list\n", option);
#endif
            return 1;
        }
    }

#ifdef DEBUG
    printf("-%s is not already in the final_options list\n", option);
#endif

    return 0;
}


/* ------------------------------------------------------------------------- */
/* Function     : get_options                                                */
/*                                                                           */
/* Description  : if all the options given are valid                         */
/*                   return a list of unique options                         */
/*                else                                                       */
/*                    return NULL                                            */
/* ------------------------------------------------------------------------- */
// Return the list of different valid options
char** get_options(size_t len_opt, char** options,
        size_t len_valid_options, char** valid_options, size_t* len_final)
{
    // Initialize the final_options list
    char** final_options = malloc(sizeof(char*));
    size_t len_final_options = 0;

    // foreach options given
    for(size_t i = 0; i < len_opt; i++)
    {
        // if the option is not valid
        if(!check_option(options[i], len_valid_options, valid_options))
        {
            // free the final_options list and return NULL
            for(size_t j = 0; j < len_final_options; j++)
                free(final_options[j]);
            free(final_options);
            return NULL;
        }

        // if the option is not already in the final_options list
        if(!is_in_options(options[i], len_final_options, final_options))
        {
            // add the option to the final_options list
            len_final_options++;
            final_options = realloc(final_options,
                    sizeof(char*) * len_final_options);
            final_options[len_final_options - 1] = options[i];
        }
    }

    // Set the value of the final_len
    *len_final = len_final_options;
    // return the final_options list
    return final_options;
}

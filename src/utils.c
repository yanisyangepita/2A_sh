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
            return 1;
    }

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
            return 1;
    }

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


/* ------------------------------------------------------------------------- */
/* Function     : lower                                                      */
/*                                                                           */
/* Description  : return str in lower case                                   */
/* ------------------------------------------------------------------------- */
char* lower(char* str)
{
    char* res = malloc(sizeof(char) * (strlen(str) + 1));
    size_t i = 0;
    while(*str != '\0')
    {
        if(*str >= 'A' && *str <= 'Z')
            res[i] = (*str) - 'A' + 'a';
        else
            res[i] = *str;
        str++;
        i++;
    }
    res[i] = '\0';

    return res;
}


/* ------------------------------------------------------------------------- */
/* Function     : ls_sort                                                    */
/*                                                                           */
/* Description  : sort the result of ls                                      */
/* ------------------------------------------------------------------------- */
void ls_sort(size_t len_to_sort, char** to_sort)
{
    if (len_to_sort == 0)
        return;
    for(size_t i = 0; i < len_to_sort - 1; i++)
    {
        for(size_t j = i + 1; j < len_to_sort; j++)
        {
            if(!strcmp(to_sort[i], "2Ash"))
            {
                if(strcmp("./2Ash", to_sort[j]) > 0)
                {
                    char* tmp = to_sort[i];
                    to_sort[i] = to_sort[j];
                    to_sort[j] = tmp;
                }
            }
            else if(!strcmp(to_sort[j], "2Ash"))
            {
                if(strcmp(to_sort[i], "./2Ash") > 0)
                {
                    char* tmp = to_sort[i];
                    to_sort[i] = to_sort[j];
                    to_sort[j] = tmp;
                }
            }
            else
            {
                char* stri = lower(to_sort[i]);
                char* strj = lower(to_sort[j]);

                if(strcmp(stri, strj) > 0)
                {
                    char* tmp = to_sort[i];
                    to_sort[i] = to_sort[j];
                    to_sort[j] = tmp;
                }

                free(stri);
                free(strj);
            }
        }
    }
}


/* ------------------------------------------------------------------------- */
/* Function     : nbrlen                                                     */
/*                                                                           */
/* Description  : return len of the number                                   */
/* ------------------------------------------------------------------------- */
size_t nbrlen(size_t nbr)
{
    size_t res = 1;
    while (nbr >= 10)
    {
        res++;
        nbr /= 10;
    }
    return res;
}

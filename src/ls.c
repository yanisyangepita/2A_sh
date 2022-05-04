/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/ls.h"


/* ------------------------------------------------------------------------- */
/* Function     : ls                                                         */
/*                                                                           */
/* Description  : options : a or l                                           */
/* ------------------------------------------------------------------------- */
void ls(char* directory, size_t len_options, char** options)
{
    // option
    int option_a = 0;

    // - Open the directory
    DIR* dir;
    if(directory == NULL)
    {
        directory = ".";
        /* char* wd = get_wd(); */

        /* directory = malloc(sizeof(char) * 2); */
        /* size_t i = 0; */
        /* size_t count = 6; */
        /* directory[0] = '~'; */

        /* // Skip the /home */
        /* while(wd[count] != '\0' && wd[count] != '/') */
        /*     count++; */

        /* while(wd[count] != '\0') */
        /* { */
        /*     directory = realloc(directory, sizeof(char) * (i + 3)); */
        /*     directory[i + 1] = wd[count]; */
        /*     i++; */
        /*     count++; */
        /* } */

        /* directory[i + 1] = '\0'; */
    }

    dir = opendir(directory);

    // - Check errors
    if(!dir)
    {
        if(errno == ENOENT)
            errx(EXIT_FAILURE, "Directory doesn't exist\n");
        else
            errx(EXIT_FAILURE, "Could not open the directory\n");
    }

    struct dirent* d;

    // -a
    if(options != NULL && is_in_options("a", len_options, options))
        option_a = 1;

    // -l
    if(options != NULL && is_in_options("l", len_options, options))
    {

    }
    else
    {
        size_t len_to_sort = 0;
        char** to_sort = malloc(sizeof(char*));

        // ls
        while((d = readdir(dir)) != NULL)
        {
            if(!option_a && d->d_name[0] == '.')
                continue;

            char* name = malloc(sizeof(char) * (strlen(d->d_name) + 1));
            strcpy(name, d->d_name);

            to_sort = realloc(to_sort, sizeof(char*) * (len_to_sort + 1));
            to_sort[len_to_sort] = name;
            len_to_sort += 1;
        }

        ls_sort(len_to_sort, to_sort);

        for(size_t i = 0; i < len_to_sort; i++)
        {
            printf("%s ", to_sort[i]);
            free(to_sort[i]);
        }

        free(to_sort);
    }

    printf("\n");
    closedir(dir);
}

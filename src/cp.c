/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/cp.h"


/* ------------------------------------------------------------------------- */
/* Function     : get_file_name                                              */
/*                                                                           */
/* Description  : return filename of the path without its directory name     */
/* ------------------------------------------------------------------------- */
char* get_file_name(char* path)
{
    char* file_name = malloc(sizeof(char));
    size_t index = 0;
    size_t i = 0;
    while(path[i] != '\0')
    {
        if(path[i] == '/')
        {
            index = i + 1;
            free(file_name);
            file_name = malloc(sizeof(char));
        }
        else
        {
            file_name = realloc(file_name, sizeof(char) * (i - index + 1));
            file_name[i - index] = path[i];
        }

        i++;
    }
    file_name = realloc(file_name, sizeof(char) * (i - index + 1));
    file_name[i - index] = '\0';

    return file_name;
}


/* ------------------------------------------------------------------------- */
/* Function     : cp                                                         */
/*                                                                           */
/* Description  : if the source and the dest are valid                       */
/*                   copy the source content to the dest file                */
/*                if the source is valid and the dest is a directory name    */
/*                   create a new file with the same name as source in dest  */
/*                if the source is not valid                                 */
/*                   throw an error                                          */
/* ------------------------------------------------------------------------- */
void cp(char* source, char* dest)
{
    FILE* file1 = NULL;
    FILE* file2 = NULL;

    file1 = fopen(source, "r");
    file2 = fopen(dest, "w");

    if(file1 == NULL)
    {
        errno = E_INVALID_FILE;
        return;
    }

    if(file2 == NULL)
    {
        errno = 0;
        // Check if dest is a directory
        DIR* dir = opendir(dest);
        if(dir)
        {
            // Directory exists
            closedir(dir);

            // touch newfile with the same name as source in the dest directory
            // - get the file name
            char* file_name = get_file_name(source);
            size_t len = strlen(dest);
            if (dest[len - 1] != '/')
            {
                dest = realloc(dest, sizeof(char) * (len + 2));
                dest[len] = '/';
                dest[len + 1] = '\0';
            }
            char* new_file_path = malloc(sizeof(char) *
                    (strlen(dest) + strlen(source) + 1));
            sprintf(new_file_path, "%s%s", dest, file_name);
            touch(new_file_path);
            file2 = fopen(new_file_path, "w");
        }
        else if(ENOENT == errno)
        {
            // Directory does not exist
            errno = E_INVALID_DIR;
        }
        else
        {
            // opendir() failed
            errno = E_INVALID_DIR;
        }
    }

    char c;
    while((c = fgetc(file1)) != EOF)
    {
        fputc(c, file2);
    }

    fclose(file1);
    fclose(file2);
}

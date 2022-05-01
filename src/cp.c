#include "../include/cp.h"

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
    file_name[i - index] = '\0';

    return file_name;
}

void cp(char* source, char* dest)
{
    FILE* file1 = NULL;
    FILE* file2 = NULL;

    file1 = fopen(source, "r");
    file2 = fopen(dest, "w");

    if(file1 == NULL)
        errx(EXIT_FAILURE, "not valid argument(s)\n");

    if(file2 == NULL)
    {
        // Check if dest is a directory
        DIR* dir = opendir(dest);
        if(dir)
        {
            // Directory exists
            closedir(dir);

            // touch newfile with the same name as source in the dest directory
            // - get the file name
            char* file_name = get_file_name(source);
            char* new_file_path = malloc(sizeof(char) *
                    (strlen(dest) + strlen(source) + 1));
            sprintf(new_file_path, "%s%s", dest, file_name);
            touch(new_file_path);
            file2 = fopen(new_file_path, "w");
        }
        else if(ENOENT == errno)
        {
            // Directory does not exist
            errx(EXIT_FAILURE, "The directory does not exist\n");
        }
        else
        {
            // opendir() failed
            errx(EXIT_FAILURE, "Could not open the directory\n");
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

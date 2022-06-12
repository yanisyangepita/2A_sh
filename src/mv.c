#include "../include/mv.h"

char* get_file_dir(char* file)
{
    size_t reverse_index = strlen(file) - 1;
    while (file[reverse_index] != '/')
    {
        reverse_index--;
    }

    char* file_dir = malloc(sizeof(char));
    size_t index = 0;

    while (index != reverse_index)
    {
        file_dir = realloc(file_dir, sizeof(char) * (index + 2));
        file_dir[index] = file[index];
        index++;
    }

    file_dir[index] = '\0';
    return file_dir;
}

void mv(char* source, char* dest)
{
    // check if dest = dir
    DIR* dir;
    dir = opendir(dest);
    if (dir)
    {
        errno = E_INVALID_DIR;
        closedir(dir);
        return;
    }

    // check if source = file
    FILE* file;
    file = fopen(source, "r");
    if (!file)
    {
        errno = E_INVALID_FILE;
        return;
    }

    fclose(file);

    // get dst dir
    char* old_dir = get_wd();
    cd(dest);
    char* dest_dir = get_wd();
    cd(old_dir);

    // get source dir
    char* file_dir = get_file_dir(source);
    cd(file_dir);
    char* source_dir = get_wd();
    cd(old_dir);

    // compare dest_dir and source_dir
    if (strcmp(dest_dir, source_dir))
    {
        cp(source, dest);
        rm(source, NULL);
    }

    // free char*
    free(old_dir);
    free(dest_dir);
    free(file_dir);
    free(source_dir);
}

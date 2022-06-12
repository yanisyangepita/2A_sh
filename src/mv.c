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
    // check if source = dir
    DIR* dir;
    dir = opendir(source);
    if (dir)
    {
        errno = E_INVALID_DIR;
        closedir(dir);
        return;
    }

    // get source dir
    char* source_dir = get_file_dir(source);

    // compare dest_dir and source_dir
    if (!strcmp(dest, source_dir))
    {
        return;
    }

    cp(source, dest);
    rm(source, NULL);
}

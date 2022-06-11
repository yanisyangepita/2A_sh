#include "../include/rm.h"

void rm_file(char* pathname)
{
    int err;
    err = remove(pathname);
    if (err != 0)
        errx(EXIT_FAILURE, "rm failure, %s", pathname);
}

void rm_dir(char* pathname)
{
    int err;
    err = rmdir(pathname);
    if (err != 0)
    {
        errno = E_INVALID_DIR;
        return;
    }
}

void recursive_rm_dir(char* pathname)
{
    DIR* dir;
    dir = opendir(pathname);
    if(!dir)
    {
        errno = E_INVALID_DIR;
        return;
    }

    // length of pathname
    size_t pathlen = strlen(pathname);

    struct dirent* d;

    while (((d=readdir(dir))) != NULL)
    {
        if (d->d_name[0] == '.')
            continue;
        char* tmp_path =
            malloc(sizeof(char) * (pathlen + strlen(d->d_name)) + 2);
        // copy pathname in tmp_path
        strcpy(tmp_path, pathname);

        strcat(tmp_path, d->d_name);
        DIR* dirtmp = opendir(tmp_path);
        if (dirtmp)
        {
            // if it's a dir recursive_rm_dir
            strcat(tmp_path, "/");
            recursive_rm_dir(tmp_path);
            rm_dir(tmp_path);
            closedir(dirtmp);
        }
        else
        {
            errno = 0;
            // if it's a file rm the file
            rm_file(tmp_path);
        }
        free(tmp_path);
    }
    rm_dir(pathname);
    closedir(dir);
}

void rm(char* pathname, char** option)
{
    DIR* dir = opendir(pathname);
    if(dir)
    {
        size_t len = strlen(pathname);
        if (pathname[len - 1] != '/')
        {
            pathname = realloc(pathname, len + 2);
            pathname[len] = '/';
            pathname[len + 1] = '\0';
        }
        // Directory exists
        if (option == NULL)
        {
            errno = E_INVALID_DIR;
        }
        else
        {
            recursive_rm_dir(pathname);
        }
        closedir(dir);
    }
    else
    {
        errno = 0;
        rm_file(pathname);
    }
}

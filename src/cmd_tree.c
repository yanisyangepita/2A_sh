/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/cmd_tree.h"

/* ------------------------------------------------------------------------- */
/* Function     : tree                                                       */
/*                                                                           */
/* Description  : tree.                                                      */
/* ------------------------------------------------------------------------- */
void tree_dir(char **res, char* dir_name, size_t level, size_t end)
{
    char *result = *res;
    DIR *dir;

    char *directory = ".";
    dir = opendir(directory);

    if (!dir)
    {
        errno = E_INVALID_DIR;
        return;
    }

    struct dirent *d;

    // Thx Val
    size_t len_to_sort = 0;
    char** to_sort = malloc(sizeof(char*));

    while((d = readdir(dir)) != NULL)
    {
        if(d->d_name[0] == '.')
            continue;

        // - Add name
        char* name = malloc(sizeof(char) * (strlen(d->d_name) + 1));
        strcpy(name, d->d_name);

        to_sort = realloc(to_sort,
                sizeof(char*) * (len_to_sort + 1));
        to_sort[len_to_sort] = name;

        // - Update len
        len_to_sort += 1;
    }

    // sort the name alphabetically
    ls_sort(len_to_sort, to_sort);

    size_t len = strlen(result);
    len += strlen(dir_name) + 2 + 7 + 6;
    result = realloc(result, sizeof(char) * len);
    char *tmp = result;
    sprintf(result, "%s\033[1;32m%s \033[0m\n", tmp, dir_name);
    for (size_t i = 0; i < len_to_sort; i++)
    {
        if (level != 0)
        {
            len += 2 + level * 2 + 2;
            char *spaces = malloc(sizeof(char) * level * 2 + 1);
            for (size_t i = 0; i < level * 2; i++)
                spaces[i] = ' ';
            spaces[level * 2] = '\0';
            result = realloc(result, sizeof(char) * len);
            tmp = result;
            if (!end)
                sprintf(result, "%s│ %s", tmp, spaces);
            else
                sprintf(result, "%s  %s", tmp, spaces);

        }
        len += 9;
        result = realloc(result, sizeof(char) * len);
        tmp = result;
        if (i != len_to_sort - 1)
            sprintf(result, "%s├── ", tmp);
        else
        {
            sprintf(result, "%s└── ", tmp);
            end = 1;
        }

        // - Get stats
        struct stat stats;
        if(strcmp(directory, "."))
        {
            char* file_path = malloc(sizeof(char) *
                    (strlen(directory) + strlen(to_sort[i]) + 2));
            strcpy(file_path, directory);
            if(directory[strlen(directory) - 1] != '/')
            {
                file_path[strlen(directory)] = '/';
                file_path[strlen(directory) + 1] = '\0';
            }
            file_path = strcat(file_path, to_sort[i]);
            if(stat(file_path, &stats))
            {
                errno = E_INVALID_STAT;
                return;

            }
            free(file_path);
        }
        else
        {
            if(stat(to_sort[i], &stats))
            {
                errno = E_INVALID_STAT;
                return;
            }
        }

        // - directory
        if(S_ISDIR(stats.st_mode))
        {
            tmp = result;
            cd(to_sort[i]);
            tree_dir(&tmp, to_sort[i], level + 1, i == len_to_sort - 1);
            cd("..");
            result = tmp;
            len = strlen(result);
        }
        // - executable
        else if(stats.st_mode & S_IXUSR)
        {
            len += 7 + 5 + strlen(to_sort[i]) + 2 + 1;
            result = realloc(result, (sizeof(char) * len));
            tmp = result;
            sprintf(result, "%s\033[1;36m%s \033[0m\n", tmp, to_sort[i]);
        }
        // - file
        else
        {
            len += strlen(to_sort[i]) + 2 + 1;
            result = realloc(result, (sizeof(char) * len));
            tmp = result;
            sprintf(result, "%s%s \n", tmp, to_sort[i]);
        }

        free(to_sort[i]);
    }

    // Free
    free(to_sort);
    closedir(dir);
    *res = result;
}
/* ------------------------------------------------------------------------- */
/* Function     : tree                                                       */
/*                                                                           */
/* Description  : tree.                                                      */
/* ------------------------------------------------------------------------- */
void tree(char **res)
{
    char *result = *res;
    size_t level = 0;
    char *directory = malloc(sizeof(char) * 2);
    directory[0] = '.';
    directory[1] = '\0';
    tree_dir(&result, directory, level, 0);
    *res = result;
}

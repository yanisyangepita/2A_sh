/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/ls.h"


/* ------------------------------------------------------------------------- */
/* Function     : ls                                                         */
/*                                                                           */
/* Description  : options : a or l                                           */
/* ------------------------------------------------------------------------- */
void ls(char* directory, size_t len_options, char** options, char **res)
{
    char *result = *res;
    char *tmp = result;
    size_t len = strlen(result);
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
        errno = E_INVALID_DIR;
        return;
    }

    struct dirent* d;

    // -a
    if(options != NULL && is_in_options("a", len_options, options))
        option_a = 1;

    // -l
    if(options != NULL && is_in_options("l", len_options, options))
    {
        size_t len_to_sort = 0;
        char** to_sort = malloc(sizeof(char*));

        while((d = readdir(dir)) != NULL)
        {
            if(!option_a && d->d_name[0] == '.')
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

        // Print and free
        // - total
        size_t total = 0;
        for(size_t i = 0; i < len_to_sort; i++)
        {
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


            total += stats.st_blocks;
        }

        len += 7 + nbrlen(total/2);
        result = realloc(result, (sizeof(char) * len ));
        tmp = result;
        sprintf(result, "%stotal %zu\n", tmp, total / 2);

        // - result
        for(size_t i = 0; i < len_to_sort; i++)
        {
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

            // - data
            len += 11 + nbrlen(stats.st_nlink);
            result = realloc(result, (sizeof(char) * len ));
            tmp = result;
            sprintf(result, (S_ISDIR(stats.st_mode)) ? "%sd" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IRUSR) ? "%sr" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IWUSR) ? "%sw" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IXUSR) ? "%sx" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IRGRP) ? "%sr" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IWGRP) ? "%sw" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IXGRP) ? "%sx" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IROTH) ? "%sr" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IWOTH) ? "%sw" : "%s-", tmp);
            tmp = result;
            sprintf(result, (stats.st_mode & S_IXOTH) ? "%sx " : "%s- ", tmp);
            tmp = result;
            sprintf(result, "%s%li ", tmp, stats.st_nlink);

            // - user data
            struct passwd* pw = getpwuid(stats.st_uid);
            if(pw == NULL)
            {
                errno = E_INVALID_UID;
                return;
            }
            else
            {
                len += strlen(pw->pw_name) + 1 + 1;
                result = realloc(result, (sizeof(char) * len));
                tmp = result;
                sprintf(result, "%s%s ", tmp , pw->pw_name);
            }

            struct group* gr = getgrgid(stats.st_gid);
            if(gr == NULL)
            {
                errno = E_INVALID_UID;
                return;
            }
            else
            {
                len += strlen(gr->gr_name) + 1 + 1;
                result = realloc(result, (sizeof(char) * len));
                tmp = result;
                sprintf(result, "%s%s ", tmp, gr->gr_name);
            }

            // - size
            len += nbrlen(stats.st_size) + 1 + 1;
            result = realloc(result, (sizeof(char) * len));
            tmp = result;
            sprintf(result, "%s%5ld ", tmp, stats.st_size);

            // - time
            struct tm* tmp_tm;
            char str[200];
            time_t time = stats.st_mtime;
            tmp_tm = localtime(&time);
            if(tmp_tm == NULL)
            {
                errno = E_INVALID_TIME;
                return;
            }
            strftime(str, sizeof(str), "%b %d %R", tmp_tm);
            len += strlen(str);
            result = realloc(result, (sizeof(char) * len));
            tmp = result;
            sprintf(result, "%s%s ", tmp, str);

            // - directory
            if(S_ISDIR(stats.st_mode))
            {
                len += 7 + 5 + strlen(to_sort[i]) + 2 + 1;
                result = realloc(result, (sizeof(char) * len));
                tmp = result;
                sprintf(result, "%s\033[1;32m%s \033[0m\n", tmp, to_sort[i]);
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
    }
    // ls
    else
    {
        size_t len_to_sort = 0;
        char** to_sort = malloc(sizeof(char*));

        // ls
        while((d = readdir(dir)) != NULL)
        {
            if(!option_a && d->d_name[0] == '.')
                continue;

            // - Add name
            char* name = malloc(sizeof(char) * (strlen(d->d_name) + 2));
            strcpy(name, d->d_name);

            to_sort = realloc(to_sort,
                    sizeof(char*) * (len_to_sort + 1));
            to_sort[len_to_sort] = name;

            // Update len
            len_to_sort += 1;
        }

        // sort the name alphabetically
        ls_sort(len_to_sort, to_sort);

        // Print and free
        for(size_t i = 0; i < len_to_sort; i++)
        {
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
                len += 7 + 5 + strlen(to_sort[i]) + 1 + 1;
                result = realloc(result, (sizeof(char) * len));
                tmp = result;
                sprintf(result, "%s\033[1;32m%s \033[0m", tmp, to_sort[i]);
            }
            // - executable
            else if(stats.st_mode & S_IXUSR)
            {
                len += 7 + 5 + strlen(to_sort[i]) + 2 + 1;
                result = realloc(result, (sizeof(char) * len));
                tmp = result;
                sprintf(result, "%s\033[1;36m%s \033[0m", tmp, to_sort[i]);
            }
            // - file
            else
            {
                len += strlen(to_sort[i]) + 1 + 1;
                result = realloc(result, (sizeof(char) * len));
                tmp = result;
                sprintf(result, "%s%s ", tmp, to_sort[i]);
            }

            free(to_sort[i]);
        }

        // Free
        free(to_sort);

        len++;
        result = realloc(result, (sizeof(char) * len));
        tmp = result;
        sprintf(result, "%s\n", tmp);
    }

    closedir(dir);
    *res = result;
}

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
                        (strlen(directory) + strlen(to_sort[i]) + 1));
                strcpy(file_path, directory);
                file_path = strcat(file_path, to_sort[i]);
                if(stat(file_path, &stats))
                    errx(EXIT_FAILURE, "Could not get stats\n");
                free(file_path);
            }
            else
            {
                if(stat(to_sort[i], &stats))
                    errx(EXIT_FAILURE, "Could not get stats\n");
            }

            total += stats.st_blocks;
        }

        printf("total %zu\n", total / 2);

        // - result
        for(size_t i = 0; i < len_to_sort; i++)
        {
            // - Get stats
            struct stat stats;
            if(strcmp(directory, "."))
            {
                char* file_path = malloc(sizeof(char) *
                        (strlen(directory) + strlen(to_sort[i]) + 1));
                strcpy(file_path, directory);
                file_path = strcat(file_path, to_sort[i]);
                if(stat(file_path, &stats))
                    errx(EXIT_FAILURE, "Could not get stats\n");
                free(file_path);
            }
            else
            {
                if(stat(to_sort[i], &stats))
                    errx(EXIT_FAILURE, "Could not get stats\n");
            }

            // - data
            printf((S_ISDIR(stats.st_mode)) ? "d" : "-");
            printf((stats.st_mode & S_IRUSR) ? "r" : "-");
            printf((stats.st_mode & S_IWUSR) ? "w" : "-");
            printf((stats.st_mode & S_IXUSR) ? "x" : "-");
            printf((stats.st_mode & S_IRGRP) ? "r" : "-");
            printf((stats.st_mode & S_IWGRP) ? "w" : "-");
            printf((stats.st_mode & S_IXGRP) ? "x" : "-");
            printf((stats.st_mode & S_IROTH) ? "r" : "-");
            printf((stats.st_mode & S_IWOTH) ? "w" : "-");
            printf((stats.st_mode & S_IXOTH) ? "x " : "- ");
            printf("%li ", stats.st_nlink);

            // - user data
            struct passwd* pw = getpwuid(stats.st_uid);
            if(pw == NULL)
                errx(EXIT_FAILURE, "Could not get pw uid\n");
            else
                printf("%s ", pw->pw_name);

            struct group* gr = getgrgid(stats.st_gid);
            if(gr == NULL)
                errx(EXIT_FAILURE, "Could not get gr id");
            else
                printf("%s ", gr->gr_name);

            // - size
            printf("%5ld ", stats.st_size);

            // - time
            struct tm* tmp;
            char str[200];
            time_t time = stats.st_mtime;
            tmp = localtime(&time);
            if(tmp == NULL)
                errx(EXIT_FAILURE, "Could not get the time\n");
            strftime(str, sizeof(str), "%b %d %R", tmp);
            printf("%s ", str);

            // - directory
            if(S_ISDIR(stats.st_mode))
            {
                printf("\033[1;32m");
                printf("%s ", to_sort[i]);
                printf("\033[0m");
            }
            // - executable
            else if(stats.st_mode & S_IXUSR)
            {
                printf("\033[1;36m");
                printf("%s ", to_sort[i]);
                printf("\033[0m");
            }
            // - file
            else
                printf("%s ", to_sort[i]);

            printf("\n");

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
            char* name = malloc(sizeof(char) * (strlen(d->d_name) + 1));
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
                        (strlen(directory) + strlen(to_sort[i]) + 1));
                strcpy(file_path, directory);
                file_path = strcat(file_path, to_sort[i]);
                if(stat(file_path, &stats))
                    errx(EXIT_FAILURE, "Could not get stats\n");
                free(file_path);
            }
            else
            {
                if(stat(to_sort[i], &stats))
                    errx(EXIT_FAILURE, "Could not get stats\n");
            }

            // - directory
            if(S_ISDIR(stats.st_mode))
            {
                printf("\033[1;32m");
                printf("%s  ", to_sort[i]);
                printf("\033[0m");
            }
            // - executable
            else if(stats.st_mode & S_IXUSR)
            {
                printf("\033[1;36m");
                printf("%s  ", to_sort[i]);
                printf("\033[0m");
            }
            // - file
            else
                printf("%s  ", to_sort[i]);

            free(to_sort[i]);
        }

        // Free
        free(to_sort);
    }

    printf("\n");
    closedir(dir);
}

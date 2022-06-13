/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/grep.h"

/* ------------------------------------------------------------------------- */
/* Function     : contains                                                   */
/*                                                                           */
/* Description  :                                                            */
/* ------------------------------------------------------------------------- */
void update_res(char *str, char *pattern,
        char **res, char *filename, int print)
{
    size_t old_found = 0;
    size_t end = strlen(pattern);
    size_t i = 0;
    size_t i_pattern = 0;
    size_t nbr_found = 0;
    while (str[i] != '\0')
    {
        if (str[i] == pattern[i_pattern])
        {
            i_pattern++;
        }
        else
        {
            i_pattern = 0;
        }
        i++;
        if (i_pattern == end)
        {
            size_t len = strlen(*res);
            // Print name of the file if needed
            if (nbr_found == 0 && print)
            {
                size_t len_file = strlen(filename);
                *res = realloc(*res, sizeof(char) * (len + len_file + 20));
                char *tmp = *res;
                sprintf(*res, "%s\033[1;35m%s\033[1;36m:\033[0m",
                        tmp, filename);
                len = strlen(*res);
            }
            if (old_found != 0)
                old_found++;
            *res = realloc(*res, sizeof(char) *
                    (len + 1 + i - end - old_found));
            // Put line from old_found to i - end (patern length)
            for (size_t index = old_found; index < i - end; index++)
            {
                (*res)[len + index - old_found] = str[index];
            }
            (*res)[len + i - old_found - end] = '\0';
            // Put the pattern with nice colors
            *res = realloc(*res, sizeof(char) *
                    (len + i - old_found + 1 + 13));
            char *tmp = *res;
            sprintf(*res, "%s\033[1;31m%s\033[0m", tmp, pattern);
            i_pattern = 0;
            old_found = i - 1;
            nbr_found++;
        }
    }

    if (old_found != 0)
    {
        size_t len = strlen(*res);
        *res = realloc(*res, sizeof(char) *
                (len + i - old_found));
        // Put line from old_found to i - end (patern length)
        for (size_t index = old_found + 1; index < i; index++)
        {
            (*res)[len + index - old_found - 1] = str[index];
        }
        (*res)[len + i - old_found - 1] = '\0';
    }

}


/* ------------------------------------------------------------------------- */
/* Function     : grep                                                       */
/*                                                                           */
/* Description  :                                                            */
/* ------------------------------------------------------------------------- */
void grep_file(char* pattern, char* filename, char **res, int print)
{
    char *result =*res;
    FILE* file = NULL;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        errno = E_INVALID_FILE;
        return;
    }
    char c;
    char *line = malloc(sizeof(char));
    size_t len_line = 0;
    while ((c = fgetc(file)) != EOF)
    {
        line = realloc(line, sizeof(char) * (len_line + 2));
        line[len_line] = c;
        len_line++;
        line[len_line] = '\0';
        if (c == '\n')
        {
            update_res(line, pattern, &result, filename, print);
            line = malloc(sizeof(char));
            len_line = 0;
        }
    }
    fclose(file);
    *res = result;
}


/* ------------------------------------------------------------------------- */
/* Function     : grep                                                       */
/*                                                                           */
/* Description  :                                                            */
/* ------------------------------------------------------------------------- */
void grep_buff(char* pattern, char **res)
{
    char *result = malloc(sizeof(char));
    result[0] = '\0';
    char *buff = *res;
    if (res == NULL)
    {
        *res = result;
        return;
    }
    size_t i = 0;
    char *line = malloc(sizeof(char));
    size_t len_line = 0;
    while (buff[i] != '\0')
    {
        line = realloc(line, sizeof(char) * (len_line + 2));
        line[len_line] = buff[i];
        len_line++;
        line[len_line] = '\0';
        if (buff[i] == '\n')
        {
            update_res(line, pattern, &result, NULL, 0);
            line = malloc(sizeof(char));
            len_line = 0;
        }
        i++;
    }
    *res = result;
}

#ifndef _2ASH_ERR_H
#define _2ASH_ERR_H

typedef struct s_err
{
    char *err_msg;
    size_t err_nbr;
}s_err;

#define E_INVALID_FUNCTION 1
#define E_GRAMMAR_DQUOTE 2
#define E_GRAMMAR_SQUOTE 3
#define E_GRAMMAR_PAR 4
#define E_GRAMMAR_BRA 5
#define E_GRAMMAR_LPAR 6
#define E_GRAMMAR_LBRA 7
#define E_NACCEPT_OPTION 8
#define E_NEED2_PARAMETERS 9
#define E_INVALID_OPTION 10
#define E_NEED_PARAMETERS 11

#endif

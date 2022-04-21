#include "../include/parser.h"

s_ast *parse(s_token_list* tkl)
{
   s_ast *ast = ast_create(tkl->data[0]);

#ifdef DEBUG
   ast_print(ast);
#endif

   return ast;
}

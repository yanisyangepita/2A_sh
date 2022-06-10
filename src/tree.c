/* ------------------------------------------------------------------------- */
/*                             Include File                                  */
/* ------------------------------------------------------------------------- */
#include "../include/tree.h"


/* ------------------------------------------------------------------------- */
/* STATIC VARIABLE                                                           */
/* Type         : s_token                                                    */
/* Name         : leaf_list                                                  */
/* Description  : database of the leaf_list                                  */
/* ------------------------------------------------------------------------- */
static s_token leaf_list[NB_LEAF] =
{
    {"cd",    CD},
    {"ls",    LS},
    {"mkdir", MKDIR},
    {"touch", TOUCH},
    {"pwd",   PWD},
    {"rm",    RM},
    {"mv",    MV},
    {"cp",    CP},
    {"cat",   CAT},
    {"echo",  ECHO},
    {"clear", CLEAR},
    {"{",     LBRACE},
    {"}",     RBRACE},
    {"|",     PIPE},
    {"(",     LPAREN},
    {")",     RPAREN},
    {"<<",    DLESS},
    {">>",    DGREAT},
    {"<&",    LESSAND},
    {">&",    GREATAND},
    {"<>",    LESSGREAT},
    {"<<-",   DLESSDASH},
    {">|",    CLOBBER}
};


/* ------------------------------------------------------------------------- */
/* Function     : fill_tree                                                  */
/*                                                                           */
/* Description  : if the char is already in the children of the current_node */
/*                   go to the next char of the leaf                         */
/*                else                                                       */
/*                   add a child to the current_node and go to this child    */
/* ------------------------------------------------------------------------- */
s_node* fill_tree(s_node* current_node, char character)
{
    s_node* child_check = get_children(current_node, character);
    // if the child does not already exist
    if(child_check == NULL)
    {
        // add a child to the count
        current_node->children_count++;

        // allocate memory for the new child
        current_node->children = realloc(current_node->children,
                current_node->children_count * sizeof(s_node*));

        // create the new child
        s_node* new_node = malloc(sizeof(s_node));
        new_node->character = character;
        new_node->children = malloc(sizeof(s_node*));
        new_node->children_count = 0;
        new_node->leaf_token = NULL;

        // add the new child to the list of children of the current node
        current_node->children[current_node->children_count - 1] = new_node;

        // return the new child
        return new_node;
    }
    // if the child already exists
    else
        // return the child
        return child_check;
}


/* ------------------------------------------------------------------------- */
/* Function     : load_leaf                                                  */
/*                                                                           */
/* Description  : load the s_token in the tree                               */
/* ------------------------------------------------------------------------- */
void load_leaf(s_token leaf, s_node* root_node)
{
    s_node* current_node = root_node;

    for(size_t i = 0; leaf.str[i] != 0; i++)
        current_node = fill_tree(current_node, leaf.str[i]);

    // allocate memory for the leaf_token
    s_token* new_leaf = malloc(sizeof(s_token));
    new_leaf->str = leaf.str;
    new_leaf->token_type = leaf.token_type;
    current_node->leaf_token = new_leaf;
}


#ifdef DEBUG
/* ------------------------------------------------------------------------- */
/* Function     : print_tree                                                 */
/*                                                                           */
/* Description  : print all the leaf from the root of a tree                 */
/* ------------------------------------------------------------------------- */
void print_tree(s_node* node)
{
    // foreach children of the node
    for(size_t i = 0; i < node->children_count; i++)
        // call free_tree with all its children
        print_tree(node->children[i]);

    if(is_leaf_node(node))
        printf("%s\n", node->leaf_token->str);
}
#endif


/* ------------------------------------------------------------------------- */
/* Function     : init_tree                                                  */
/*                                                                           */
/* Description  : initialize the tree from the leaf list                     */
/*                root_node is already malloc()                              */
/* ------------------------------------------------------------------------- */
void init_tree(s_node* root_node)
{
    root_node->character = 0;
    root_node->children_count = 0;
    root_node->leaf_token = NULL;

    root_node->children = malloc(sizeof(s_node*));

    // foreach leaf in the leaf list
    for(size_t i = 0; i < NB_LEAF; i++)
        load_leaf(leaf_list[i], root_node);
/*
#ifdef DEBUG
    print_tree(root_node);
#endif
*/
}


/* ------------------------------------------------------------------------- */
/* Function     : free_tree                                                  */
/*                                                                           */
/* Description  : initialize the tree from the leaf list                     */
/*                root_node is already malloc()                              */
/* ------------------------------------------------------------------------- */
void free_tree(s_node* node)
{
    // foreach children of the node
    for(size_t i = 0; i < node->children_count; i++)
        // call free_tree with all its children
        free_tree(node->children[i]);

    if(is_leaf_node(node))
    {
        /*
#ifdef DEBUG
        printf("%s\n", node->leaf_token->str);
#endif
*/
        free(node->leaf_token);
    }

    free(node->children);
    free(node);
}



/* ------------------------------------------------------------------------- */
/* Function     : get_children                                               */
/*                                                                           */
/* Description  : if the current char is a children of the current_node      */
/*                    return the its node                                    */
/*                else                                                       */
/*                    return NULL                                            */
/* ------------------------------------------------------------------------- */
s_node* get_children(s_node* current_node, char current_char)
{
    if(current_node == NULL)
        return NULL;

    for(size_t i = 0; i < current_node->children_count; i++)
    {
        if(current_node->children[i]->character == current_char)
            return current_node->children[i];
    }

    return NULL;
}


/* ------------------------------------------------------------------------- */
/* Function     : is_root_node                                               */
/*                                                                           */
/* Description  : if the current node is a root node                         */
/*                    return 1 (true)                                        */
/*                else                                                       */
/*                    return 0 (false)                                       */
/* ------------------------------------------------------------------------- */
int is_root_node(s_node* current_node)
{
    return current_node->character == 0;
}


/* ------------------------------------------------------------------------- */
/* Function     : is_leaf_node                                               */
/*                                                                           */
/* Description  : if the current node is a leaf node                         */
/*                    return 1 (true)                                        */
/*                else                                                       */
/*                    return 0 (false)                                       */
/* ------------------------------------------------------------------------- */
int is_leaf_node(s_node* current_node)
{
    return current_node != NULL && current_node->leaf_token != NULL;
}


/* ------------------------------------------------------------------------- */
/* Function     : get_leaf_token                                             */
/*                                                                           */
/* Description  : return the token of the leaf_node                          */
/* ------------------------------------------------------------------------- */
s_token* get_leaf_token(s_node* leaf_node)
{
    return leaf_node->leaf_token;
}


/* ------------------------------------------------------------------------- */
/* Function     : check_tree                                                 */
/*                                                                           */
/* Description  : if the str corresponds to a leaf                           */
/*                    e_token_type                                           */
/*                else                                                       */
/*                    NONE                                                   */
/* ------------------------------------------------------------------------- */
e_token_type check_tree(s_node* root_node, char* str)
{
    s_node* current_node = root_node;

    while(current_node != NULL && *str != 0)
    {
        current_node = get_children(current_node, *str);
        str++;
    }

    if(is_leaf_node(current_node))
        return get_leaf_token(current_node)->token_type;

    return NONE;
}


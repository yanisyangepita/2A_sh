#ifndef _2ASH_TREE_H
#define _2ASH_TREE_H

#include "token.h"

#define NB_LEAF     25

struct s_node
{
    char character;
    struct s_node** children;
    size_t children_count;
    s_token* leaf_token;
};

typedef struct s_node s_node;

void init_tree(s_node* root_node);
void free_tree(s_node* root_node);

s_node* get_children(s_node* current_node, char current_char);

int is_root_node(s_node* current_node);
int is_leaf_node(s_node* current_node);
s_token* get_leaf_token(s_node* leaf_node);
e_token_type check_tree(s_node* root_node, char* str);

#endif

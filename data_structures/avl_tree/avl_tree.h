#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef type_h
#define type_h
typedef void * Type;

#endif

#ifndef avl_tree_h
#define avl_tree_h

typedef struct strTree * Tree;

Tree avl_tree_init(void(*destructor)(Type), int(*comparator)(Type, Type));
void avl_tree_insert(Tree tree, Type data);
void avl_tree_delete(Tree tree, Type data);
Type avl_tree_search(Tree tree, Type data);
void avl_tree_destroy(Tree tree);
unsigned int avl_tree_size(Tree tree);
bool avl_tree_is_empty(Tree tree);

#endif
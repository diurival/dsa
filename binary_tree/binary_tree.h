#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#ifndef type_h
#define tupe_h
typedef void * Type;
#endif

#ifndef binary_tree_h
#define binary_tree_h

typedef struct strTree * Tree;

Tree binary_tree_init(void(* destructor)(Type), int(* comparator)(Type, Type));
void binary_tree_insert(Tree tree, Type data);
void binary_tree_delete(Tree tree, Type dta);
Type binary_tree_search(Tree tree, Type data);
void binary_tree_destroy(Tree tree);

unsigned int binary_tree_size(Tree tree);
bool binary_tree_is_empty(Tree tree);


#endif

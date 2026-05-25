#include "avl_tree.h"
#include <stdlib.h>
#include <stdio.h>

void int_destructor(Type data) {
    free(data);
}

int int_comparator(Type a, Type b) {
    return *(int *)a - *(int *)b;
}

int main(void) {
    Tree t = avl_tree_init(int_destructor, int_comparator);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 20;
    int *c = malloc(sizeof(int)); *c = 5;
    int *d = malloc(sizeof(int)); *d = 15;

    avl_tree_insert(t, a);
    avl_tree_insert(t, b);
    avl_tree_insert(t, c);
    avl_tree_insert(t, d);

    printf("SIZE: %u\n", avl_tree_size(t)); 

    int key = 15;
    Type found = avl_tree_search(t, &key);
    if(found) printf("FOUND: %d\n", *(int *)found); 

    avl_tree_delete(t, &key);
    printf("SIZE: %u\n", avl_tree_size(t));

    avl_tree_destroy(t);
    return 0;
}
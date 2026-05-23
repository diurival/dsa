#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int comparator(Type a, Type b)
{
    int x = *(int *)a;
    int y = *(int *)b;

    if (x > y)
        return 1;
    else if (x < y)
        return -1;

    return 0;
}

void destructor(Type data)
{
    free(data);
}

int *create_int(int value)
{
    int *n = (int *)malloc(sizeof(int));
    *n = value;
    return n;
}

void print_search(Tree tree, int value)
{
    int temp = value;

    int *result = (int *)binary_tree_search(tree, &temp);

    if (result != NULL)
        printf("FOUND: %d\n", *result);
    else
        printf("NOT FOUND: %d\n", value);
}

int main(void)
{
    Tree tree = binary_tree_init(destructor, comparator);

    printf("INSERT\n");

    binary_tree_insert(tree, create_int(50));
    binary_tree_insert(tree, create_int(30));
    binary_tree_insert(tree, create_int(70));
    binary_tree_insert(tree, create_int(20));
    binary_tree_insert(tree, create_int(40));
    binary_tree_insert(tree, create_int(60));
    binary_tree_insert(tree, create_int(80));

    printf("SIZE: %u\n", binary_tree_size(tree));

    printf("SEARCH\n");

    print_search(tree, 40);
    print_search(tree, 100);

    printf("DELETE\n");

    int x = 20;
    binary_tree_delete(tree, &x);

    x = 30;
    binary_tree_delete(tree, &x);

    x = 50;
    binary_tree_delete(tree, &x);

    printf("SIZE: %u\n", binary_tree_size(tree));

    printf("EMPTY\n");

    if (binary_tree_is_empty(tree))
        printf("TREE IS EMPTY\n");
    else
        printf("TREE IS NOT EMPTY\n");

    printf("DESTROY\n");

    binary_tree_destroy(tree);

    return 0;
}
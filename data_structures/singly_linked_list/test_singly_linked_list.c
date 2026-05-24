#include <stdio.h>
#include <stdlib.h>
#include "singly_linked_list.h"

int main()
{
    Link list = linked_list_init(free);

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));

    *a = 2;
    *b = 10;
    *c = 15;
    *d = 72;

    printf("=== APPEND ===\n");

    linked_list_append(list, a);
    linked_list_append(list, b);
    linked_list_append(list, c);
    linked_list_append(list, d);

    linked_list_print(list);

    printf("Size: %d\n\n", linked_list_size(list));

    printf("=== PREPEND ===\n");

    int *e = malloc(sizeof(int));
    *e = 99;

    linked_list_prepend(list, e);

    linked_list_print(list);

    printf("Size: %d\n\n", linked_list_size(list));

    printf("=== INSERT AT INDEX 2 ===\n");

    int *f = malloc(sizeof(int));
    *f = 500;

    linked_list_insert(list, f, 2);

    linked_list_print(list);

    printf("Size: %d\n\n", linked_list_size(list));

    printf("=== DELETE HEAD ===\n");

    linked_list_delete(list, 0);

    linked_list_print(list);

    printf("Size: %d\n\n", linked_list_size(list));

    printf("=== DELETE TAIL ===\n");

    linked_list_delete(list, linked_list_size(list) - 1);

    linked_list_print(list);

    printf("Size: %d\n\n", linked_list_size(list));

    printf("=== DELETE MIDDLE ===\n");

    linked_list_delete(list, 1);

    linked_list_print(list);

    printf("Size: %d\n\n", linked_list_size(list));

    printf("=== FIND ===\n");

    Type found = linked_list_find(list, c);

    if (found != NULL)
        printf("Found: %d\n\n", *(int *)found);
    else
        printf("Not found\n\n");

    printf("=== IS EMPTY ===\n");

    printf("%s\n\n", linked_list_is_empty(list) ? "true" : "false");

    printf("=== FINAL STATE ===\n");

    linked_list_print(list);

    printf("Size: %d\n", linked_list_size(list));

    return 0;
}
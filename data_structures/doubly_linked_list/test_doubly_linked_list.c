#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "doubly_linked_list.h"

int main()
{
    DLink LIST = doubly_linked_list_init(NULL);

    int *A = malloc(sizeof(int));
    int *B = malloc(sizeof(int));
    int *C = malloc(sizeof(int));
    int *D = malloc(sizeof(int));

    *A = 10;
    *B = 20;
    *C = 30;
    *D = 40;

    doubly_linked_list_append(LIST, A);
    doubly_linked_list_append(LIST, B);
    doubly_linked_list_prepend(LIST, C);
    doubly_linked_list_insert(LIST, D, 1);

    doubly_linked_list_print(LIST);

    printf("SIZE: %u\n", doubly_linked_list_size(LIST));

    if (doubly_linked_list_is_empty(LIST))
    {
        printf("LIST IS EMPTY\n");
    }
    else
    {
        printf("LIST IS NOT EMPTY\n");
    }

    doubly_linked_list_delete(LIST, 2);

    doubly_linked_list_print(LIST);

    doubly_linked_list_destroy(LIST);

    return 0;
}
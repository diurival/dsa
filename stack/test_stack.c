#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    Stack st = stack_init(NULL);

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));

    *a = 10;
    *b = 20;
    *c = 30;

    printf("=== PUSH ===\n");

    stack_push(st, a);
    stack_push(st, b);
    stack_push(st, c);

    printf("Top: %d\n\n", *(int *)stack_top(st));

    printf("=== POP ===\n");

    int *value = (int *)stack_pop(st);

    if (value != NULL)
    {
        printf("Popped: %d\n", *value);
        free(value);
    }

    printf("New Top: %d\n\n", *(int *)stack_top(st));

    printf("=== POP AGAIN ===\n");

    value = (int *)stack_pop(st);

    if (value != NULL)
    {
        printf("Popped: %d\n", *value);
        free(value);
    }

    printf("New Top: %d\n\n", *(int *)stack_top(st));

    printf("=== IS EMPTY ===\n");

    printf("%s\n\n", stack_is_empty(st) ? "true" : "false");

    printf("=== FINAL POP ===\n");

    value = (int *)stack_pop(st);

    if (value != NULL)
    {
        printf("Popped: %d\n", *value);
        free(value);
    }

    printf("=== IS EMPTY NOW ===\n");

    printf("%s\n\n", stack_is_empty(st) ? "true" : "false");

    stack_destroy(st);

    return 0;
}
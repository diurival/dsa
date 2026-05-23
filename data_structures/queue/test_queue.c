#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    Queue q = queue_init(free);

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));

    *a = 10;
    *b = 20;
    *c = 30;
    *d = 40;

    printf("=== OFFER ===\n");

    queue_offer(q, a);
    queue_offer(q, b);
    queue_offer(q, c);
    queue_offer(q, d);

    printf("Queue size: %d\n", queue_size(q));
    printf("Front element: %d\n\n", *(int *)queue_peek(q));

    printf("=== POLL ===\n");

    int *value = (int *)queue_poll(q);

    if (value != NULL)
    {
        printf("Polled: %d\n", *value);
        free(value);
    }

    printf("New front: %d\n", *(int *)queue_peek(q));
    printf("Queue size: %d\n\n", queue_size(q));

    printf("=== POLL AGAIN ===\n");

    value = (int *)queue_poll(q);

    if (value != NULL)
    {
        printf("Polled: %d\n", *value);
        free(value);
    }

    printf("New front: %d\n", *(int *)queue_peek(q));
    printf("Queue size: %d\n\n", queue_size(q));

    printf("=== IS EMPTY ===\n");

    printf("%s\n\n", queue_is_empty(q) ? "true" : "false");

    printf("=== REMOVE REMAINING ===\n");

    while (!queue_is_empty(q))
    {
        value = (int *)queue_poll(q);

        if (value != NULL)
        {
            printf("Removed: %d\n", *value);
            free(value);
        }
    }

    printf("\n");

    printf("=== FINAL STATE ===\n");

    printf("Queue size: %d\n", queue_size(q));
    printf("Is empty: %s\n\n", queue_is_empty(q) ? "true" : "false");

    queue_destroy(q);

    return 0;
}
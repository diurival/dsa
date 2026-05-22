#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef type_h
#define type_h
typedef void * Type;
#endif

#ifndef queue_h
#define queue_h
typedef struct strQueue * Queue;

Queue queue_init(void(*destructor)(Type));
Type queue_poll(Queue q);
Type queue_peek(Queue q);
void queue_offer(Queue q, Type data);
void queue_destroy(Queue q);
bool queue_is_empty(Queue q);
int queue_size(Queue q);

#endif
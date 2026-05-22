#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

struct strNode
{
    Type data;
    struct strNode * next;
};

typedef struct strNode * Node;

struct strQueue
{
    Node first;
    Node last;
    unsigned int size;
    void(*destructor)(Type);
};

Queue queue_init(void(*destructor)(Type))
{
    Queue queue = (Queue)malloc(sizeof(struct strQueue));
    if(queue == NULL)
        return NULL;
    
    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;
    queue->destructor = destructor;

    return queue;
}

void queue_offer(Queue q, Type data)
{
    if(q == NULL)
        return;
    
    Node node = (Node)malloc(sizeof(struct strNode));

    if(node == NULL)
        return;

    node->data = data;
    node->next = NULL;

    if(q->first == NULL)
        q->first = node;
    else
        q->last->next = node;

    q->last = node;
    q->size++;
}

Type queue_poll(Queue q)
{
    if(q == NULL || q->first == NULL)
        return NULL;
    
    Node curr = q->first;
    Type data = curr->data;

    if(q->size > 1)
        q->first = curr->next;
    else
    {
        q->first = NULL;
        q->last = NULL;
    }
    
    free(curr);
    q->size--;
    return data;
}

Type queue_peek(Queue q)
{
    return (q == NULL || q->first == NULL) ? NULL : q->first->data;
}

int queue_size(Queue q)
{
    return q == NULL ? 0 : q->size;
}

bool queue_is_empty(Queue q)
{
    if(q == NULL)
        return true;
    return q->size > 0 ? false : true;
}

void queue_destroy(Queue q)
{
    if(q == NULL)
        return;
        
    Node curr = q->first;
    while(curr != NULL)
    {
        Node temp = curr->next;
        if(q->destructor != NULL)
            q->destructor(curr->data);
        free(curr);

        curr = temp;
    }
    free(q);
}

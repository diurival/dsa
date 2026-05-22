#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

struct strNode
{
    Type data;
    struct strNode * next;
};

typedef struct strNode * Node;

struct strStack
{
    Node top;
    unsigned int size;
    void (*destructor)(Type);
};

Stack stack_init(void (*destructor)(Type))
{
    Stack newStack = (Stack)malloc(sizeof(struct strStack));

    if(newStack == NULL)
        return NULL;

    newStack->top = NULL;
    newStack->size = 0;
    newStack->destructor = destructor;

    return newStack;
}

void stack_push(Stack st, Type element)
{
    if(st == NULL)
        return;
    
    Node node = (Node)malloc(sizeof(struct strNode));
    if(node == NULL)
        return;
    
    node->data = element;
    node->next = st->top;

    st->top = node;
    st->size++;
}

Type stack_pop(Stack st)
{
    if(st == NULL || st->top == NULL)
        return NULL;

    Node top = st->top;
    Type data = top->data;
    st->top = top->next;

    free(top);

    st->size--;

    return data;
}

void stack_destroy(Stack st)
{
    if(st == NULL)
        return;

    Node curr = st->top;

    while(curr != NULL)
    {
        Node temp = curr->next;
        if(st->destructor != NULL)
            st->destructor(curr->data);
        free(curr);

        curr = temp;
    }

    free(st);
}

Type stack_top(Stack st)
{   
    return (st == NULL || st->top == NULL) ? NULL : st->top->data;
}

bool stack_is_empty(Stack st)
{
    if(st == NULL)
        return true;
    return st->size == 0 ? true : false;
}
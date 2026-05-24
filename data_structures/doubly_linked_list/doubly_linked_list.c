#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "doubly_linked_list.h"

struct strNode
{
    Type data;
    struct strNode * prev;
    struct strNode * next;
};

typedef struct strNode * Node;

struct strDLink
{
    Node head;
    Node tail;
    unsigned int size;
    void(*destructor)(Type);
};

static void doubly_linked_list_delete_head(DLink dlist);
static void doubly_linked_list_delete_tail(DLink dlist);

DLink doubly_linked_list_init(void(*destructor)(Type))
{
    DLink newList = (DLink)malloc(sizeof(struct strDLink));
    if(newList == NULL)
        return NULL;
    
    newList->head = NULL;
    newList->tail = NULL;
    newList->destructor = destructor;
    newList->size = 0;

    return newList;
}

void doubly_linked_list_append(DLink dlist, Type data)
{
    if(dlist == NULL)
        return;
    
    Node node = (Node)malloc(sizeof(struct strNode));
    if(node == NULL)
        return;    

    node->data = data;
    
    if(dlist->head == NULL)
    {
        dlist->head = node;
        node->prev = NULL;
    }
    else
    {
        dlist->tail->next = node;
        node->prev = dlist->tail;
    }
    
    dlist->tail = node;
    node->next = NULL;

    dlist->size++;
}

void doubly_linked_list_prepend(DLink dlist, Type data)
{
    if(dlist == NULL)
        return;

    Node node = (Node)malloc(sizeof(struct strNode));
    if(node == NULL)
        return;

    node->data = data;

    if(dlist->tail == NULL)
    {
        dlist->tail = node;
        node->next = NULL;
    }
    else
    {
        dlist->head->prev = node;
        node->next = dlist->head;
    }

    dlist->head = node;
    node->prev = NULL;

    dlist->size++;
}

void doubly_linked_list_insert(DLink dlist, Type data, int index)
{
    if(dlist == NULL)
        return;
    
    if(index < 0 || index > dlist->size)
        return;
        
    if(index == 0)
        doubly_linked_list_prepend(dlist, data);
    else if(index == dlist->size)
        doubly_linked_list_append(dlist, data);
    else
    {
        Node node = (Node)malloc(sizeof(struct strNode));
        if(node == NULL)
            return;
    
        node->data = data;
        Node curr = dlist->head;

        for(int i = 0; i < index - 1; ++i)
            curr = curr->next;
        
        node->next = curr->next;
        node->prev = curr;
        node->next->prev = node;
        curr->next = node;

        dlist->size++;
    }
}

void doubly_linked_list_delete(DLink dlist, int index)
{
    if(dlist == NULL)
        return;

    if(index < 0 || index >= dlist->size)
        return;

    if(index == 0)
        doubly_linked_list_delete_head(dlist);
    else if(index == dlist->size - 1)
        doubly_linked_list_delete_tail(dlist);
    else
    {
        Node curr = dlist->head;
        for(int i = 0; i < index - 1; ++i)
            curr = curr->next;
        
        Node temp = curr->next;
        curr->next = curr->next->next;
        curr->next->prev = curr;

        if(dlist->destructor != NULL)
            dlist->destructor(temp->data);
        free(temp);

        dlist->size--;
    }
}

Type doubly_linked_list_find(DLink dlist, Type data)
{
    if(dlist == NULL)
        return NULL;

    Node first = dlist->head;
    Node last = dlist->tail;

    while(first != last && last->next != first)
    {
        if(first->data == data)
            return first->data;
        if(last->data == data)
            return last->data;
        first = first->next;
        last = last->prev;
    }

    return (last != NULL && last->data == data) ? data : NULL;
}

unsigned int doubly_linked_list_size(DLink dlist)
{
    return dlist == NULL ? 0 : dlist->size;
}

bool doubly_linked_list_is_empty(DLink dlist)
{
    if(dlist == NULL)
        return true;
    return dlist->size != 0 ? false : true;
}

void doubly_linked_list_destroy(DLink dlist)
{
    if(dlist == NULL)
        return;

    Node curr = dlist->head;

    while(curr != NULL)
    {
        Node temp = curr->next;
        dlist->head = dlist->head->next;

        if(dlist->destructor != NULL)
            dlist->destructor(curr->data);
        free(curr);

        curr = temp;
    }

    free(dlist);
}

void doubly_linked_list_print(DLink dlist)
{
    if(dlist == NULL)
        return;
    
    Node curr = dlist->head;
    printf("NULL");
    while(curr != NULL)
    {
        printf("<-> %d <-> ", *(int *)curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

static void doubly_linked_list_delete_head(DLink dlist)
{
    if(dlist == NULL)
        return;

    Node curr = dlist->head;

    if(dlist->size > 1)
    {
        dlist->head = dlist->head->next;
        dlist->head->prev = NULL;
    }
    else
    {
        dlist->head = NULL;
        dlist->tail = NULL;
    }
    if(dlist->destructor != NULL)
        dlist->destructor(curr->data);
    free(curr);

    dlist->size--;
}

static void doubly_linked_list_delete_tail(DLink dlist)
{
    if(dlist == NULL)
        return;

    Node curr = dlist->tail;
    if(dlist->size > 1)
    {
        dlist->tail = dlist->tail->prev;
        dlist->tail->next = NULL;
    }
    else
    {
        dlist->head = NULL;
        dlist->tail = NULL;
    }
    if(dlist->destructor != NULL)
        dlist->destructor(curr->data);
    free(curr);

    dlist->size--;
}

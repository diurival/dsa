#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

struct strNode
{
    Type data;
    struct strNode * next;
};

typedef struct strNode * Node;

struct strLink
{
    Node head;
    Node tail;
    unsigned int size;
    void (* destructor)(Type);
};

void linked_list_delete_head(Link list);
void linked_list_delete_tail(Link list);

Link linked_list_init(void (* destructor)(Type))
{
    Link initLink = (Link)malloc(sizeof(struct strLink));

    if(initLink == NULL)
        return NULL;

    initLink->head = NULL;
    initLink->tail = NULL;
    initLink->destructor = destructor;
    initLink->size = 0;

    return initLink;
}


void linked_list_append(Link list, Type data)
{
    if(list == NULL)
        return;
    
    Node node = (Node)malloc(sizeof(struct strNode));
    if(node == NULL)
        return;

    node->data = data;
    node->next = NULL;

    if(list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void linked_list_prepend(Link list, Type data)
{
    if(list == NULL)
        return;
    
    Node node = (Node)malloc(sizeof(struct strNode));
    if(node == NULL)
        return;

    node->data = data;
    node->next = NULL;

    if(list->tail == NULL)
    {
        list->tail = node;
        list->head = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }

    list->size++;
}

void linked_list_insert(Link list, Type data, int index)
{
    if(list == NULL)
        return;
    
    if(index > list->size)
        return;
    
    if(index == list->size)
        linked_list_append(list, data);
    else if(index == 0)
        linked_list_prepend(list, data);
    else
    {
        Node curr = list->head;
        for(int i = 0; i < index - 1; ++i){
            curr = curr->next;
        }

        Node node = (Node)malloc(sizeof(struct strNode));
        if(node == NULL)
            return;

        node->data = data;

        node->next = curr->next;
        curr->next = node;

        list->size++;
    }
}

void linked_list_delete(Link list, int index)
{
    if(list == NULL)
        return;

    if(index < 0 || index >= list->size)
        return;
    
    if(index == 0)
        linked_list_delete_head(list);
    else if(index == list->size - 1)
        linked_list_delete_tail(list);
    else
    {
        Node curr = list->head;
        for(int i = 0; i < index - 1; ++i)
            curr = curr->next;

        Node temp = curr->next;
        curr->next = curr->next->next;

        if(list->destructor != NULL)
            list->destructor(temp->data);
        free(temp);

        list->size--;
    }
}

Type linked_list_find(Link list, Type data)
{
    if(list == NULL)
        return NULL;
    
    Node curr = list->head;
    
    while(curr != NULL)
    {
        if(curr->data == data)
            return curr->data;
        curr = curr->next;
    }

    return NULL;
}


unsigned int linked_list_size(Link list)
{
    return list == NULL ? 0 : list->size;
}

bool linked_list_is_empty(Link list)
{   
    if(list == NULL)
        return true;
    return list->size == 0 ? true : false;
}

void linked_list_destroy(Link list)
{
    if(list == NULL)
        return;
    
    Node curr = list->head;

    while(curr != NULL)
    {
        Node temp = curr->next;
        list->head = list->head->next;

        if(list->destructor != NULL)
            list->destructor(curr->data);
        free(curr);

        curr = temp;
    }

    free(list);
}

void linked_list_delete_head(Link list)
{
    if(list == NULL || list->head == NULL)
        return;

    Node curr = list->head;        
    if(list->size > 1)
        list->head = curr->next;
    else
    {
        list->head = NULL;
        list->tail = NULL;
    }

    if(list->destructor != NULL)
        list->destructor(curr->data);
    free(curr);
    list->size--;
}
void linked_list_delete_tail(Link list)
{
    if(list == NULL || list->tail == NULL)
        return;

    Node temp = list->tail;
    if(list->size > 1)
    {
        Node curr = list->head;
        while(curr->next != list->tail)
            curr = curr->next;
        list->tail = curr;
        list->tail->next = NULL;
    }
    else
    {
        list->tail = NULL;
        list->head = NULL;
    }

    if(list->destructor != NULL)
        list->destructor(temp->data);
    free(temp);

    list->size--;
}

void linked_list_print(Link list)
{
    if(list == NULL)
        return;
    
    Node curr = list->head;
    while(curr != NULL)
    {
        printf("%d -> ", *(int *)curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

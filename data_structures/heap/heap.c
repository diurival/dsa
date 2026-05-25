#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

struct strHeap
{
    Type * data;
    unsigned int size;
    unsigned int capacity;
    void(*destructor)(Type);
    int(*comparator)(Type, Type);
};

static void swap(Type a, Type b);
static int parent_index(int index);
static int right_child(int index);
static int left_child(int index);

Heap heap_init(void(*destructor)(Type), int(*comparator)(Type, Type), int capacity)
{
    Heap heap = (Heap)malloc(sizeof(struct strHeap));
    if(heap == NULL)
        return NULL;
    
    Type data = (Type *)malloc(capacity * sizeof(Type));
    if(data == NULL)
    {
        free(heap);
        return NULL;
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->comparator = comparator;
    heap->destructor = destructor;
    heap->data = data;

    return heap;
}

void heap_insert(Heap heap, Type data)
{
    if(heap == NULL)
        return;

    if(heap->size == heap->capacity)
    {
        Type * temp = (Type *)realloc(heap->data, 2 * heap->capacity * sizeof(Type));
        if(temp == NULL)
            return;
        heap->data = temp;
        heap->capacity *= 2;
    }

    heap->data[heap->size] = data;
    heap->size++;

    int i = heap->size - 1;
    int pIdx = parent_index(i);
    while(i > 0 && heap->comparator(heap->data[i], heap->data[pIdx]) < 0)
    {
        swap(heap->data[pIdx], heap->data[i]);
        i = pIdx;
        pIdx = parent_index(i);
    }
}

Type heap_extract(Heap heap)
{
    if(heap == NULL)
        return NULL;

    if(heap->size == 0)
        return NULL;
    
    Type extractedValue = heap->data[0];

    swap(heap->data[0], heap->data[(heap->size - 1)]);
    heap->size--;

    if(heap->size == 0)
        return extractedValue;

    int i = 0;

    while(true)
    {
        int rIdx = right_child(i), lIdx = left_child(i);
        if(lIdx >= heap->size)
            break;
        else if(lIdx < heap->size && rIdx >= heap->size)
        {
            int cmp = heap->comparator(heap->data[i], heap->data[lIdx]);
            if(cmp < 0)
            {
                swap(heap->data[i], heap->data[lIdx]);
                i = lIdx;
            }
            else 
                break;
        }
        else
        {
            int cmp = heap->comparator(heap->data[lIdx], heap->data[rIdx]);
            if(cmp > 0)
            {
                cmp = heap->comparator(heap->data[i], heap->data[lIdx]);
                if(cmp < 0)
                {
                    swap(heap->data[i], heap->data[lIdx]);
                    i = lIdx;
                }
                else 
                    break;
            }
            else
            {
                cmp = heap->comparator(heap->data[i], heap->data[rIdx]);
                if(cmp < 0)
                {
                    swap(heap->data[i], heap->data[rIdx]);
                    i = rIdx;
                }
                else 
                    break;
            }
        }
    }

    return extractedValue;
}

Type heap_peek(Heap heap)
{
    if(heap == NULL)
        return NULL;

    return heap->size > 0 ? heap->data[0] : NULL;
}

unsigned int heap_size(Heap heap)
{
    if(heap == NULL)
        return 0;
    return heap->size;
}

bool heap_is_empty(Heap heap)
{
    if(heap == NULL)
        return true;
    return heap->size > 0 ? false : true; 
}

void heap_destroy(Heap heap)
{
    if(heap == NULL)
        return;

    for(int i = 0; i < heap->size; ++i){
        if(heap->destructor != NULL)
            heap->destructor(heap->data[i]);
    }
    free(heap->data);
    free(heap);
}

static void swap(Type * a, Type * b)
{
    Type temp = *a;
    *a = *b;
    *b = temp;
}

static int parent_index(int index)
{
    return (index - 1) / 2;
}

static int left_child(int index)
{
    return 2 * index + 1;
}

static int right_child(int index)
{
    return 2 * index + 2;
}


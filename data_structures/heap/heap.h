#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef type_h
#define type_h
typedef void * Type;

#endif

#ifndef heap_h
#define heap_h
typedef struct strHeap * Heap;

Heap heap_init(void(*destructor)(Type), int(*comparator)(Type, Type), int capacity);
void heap_insert(Heap heap, Type data);
Type heap_extract(Heap heap);
Type heap_peek(Heap heap);
unsigned int heap_size(Heap heap);
bool heap_is_empty(Heap heap);
void heap_destroy(Heap heap);

#endif
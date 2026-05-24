#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef type_h
#define type_h
typedef void * Type;
#endif

#ifndef doubly_linked_list_h
#define doubly_linked_list_h

typedef struct strDLink * DLink;

DLink doubly_linked_list_init(void(*destructor)(Type));
void doubly_linked_list_append(DLink dlist, Type data);
void doubly_linked_list_prepend(DLink dlist, Type data);
void doubly_linked_list_insert(DLink dlist, Type data, int index);
void doubly_linked_list_delete(DLink dlist, int index);
Type doubly_linked_list_find(DLink dlist, Type data);
unsigned int doubly_linked_list_size(DLink dlist);
bool doubly_linked_list_is_empty(DLink dlist);
void doubly_linked_list_destroy(DLink dlist);
void doubly_linked_list_print(DLink dlist);

#endif

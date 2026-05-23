#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef type_h
#define type_h
typedef void * Type;
#endif

#ifndef linked_list_h
#define linked_list_h

typedef struct strLink * Link;

Link linked_list_init(void (* destructor)(Type));
void linked_list_append(Link list, Type data);
void linked_list_prepend(Link list, Type data);
void linked_list_insert(Link list, Type data, int index);
void linked_list_delete(Link list, int index);
Type linked_list_find(Link list, Type data);

unsigned int linked_list_size(Link list);
bool linked_list_is_empty(Link list);
void linked_list_destroy(Link list);
void linked_list_print(Link list);

#endif
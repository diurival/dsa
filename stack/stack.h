#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
  
#ifndef type_h
#define type_h
typedef void * Type;
#endif

#ifndef stack_h
#define stack_h

typedef struct strStack * Stack;

Stack stack_init(void (*destructor)(Type));
void stack_push(Stack st, Type element);
void stack_destroy(Stack st);
Type stack_pop(Stack st);
Type stack_top(Stack st);
bool stack_is_empty(Stack st);

#endif
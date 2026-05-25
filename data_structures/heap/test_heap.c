#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void int_destructor(Type data) {
    free(data);
}

// min-heap: returns negative if a < b
int int_comparator(Type a, Type b) {
    return *(int *)a - *(int *)b;
}

/* max-heap
int int_comparator(Type a, Type b) {
    return *(int *)b - *(int *)a;
}
*/

int main(void) {
    Heap h = heap_init(int_destructor, int_comparator, 16);

    int *a = malloc(sizeof(int)); *a = 30;
    int *b = malloc(sizeof(int)); *b = 10;
    int *c = malloc(sizeof(int)); *c = 20;

    heap_insert(h, a);
    heap_insert(h, b);
    heap_insert(h, c); 

    printf("TOP: %d\n", *(int *)heap_peek(h));   

    int *extracted = (int *)heap_extract(h);
    printf("EXTRACT: %d\n", *extracted);        
    free(extracted);

    printf("SIZE: %u\n", heap_size(h));         

    heap_destroy(h);
    return 0;
}

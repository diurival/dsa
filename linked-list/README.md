# Linked List — Documentación en C

Implementación de una **lista enlazada simple** en C con soporte para destructor de datos genérico (`void *`).

---

## Estructuras internas

```c
struct strNode {
    Type data;
    struct strNode *next;
};

struct strLink {
    Node head;
    Node tail;
    unsigned int size;
    void (*destructor)(Type);
};
```

- `strNode`: nodo individual que almacena un dato genérico (`Type`) y un puntero al siguiente nodo.
- `strLink`: contenedor principal con referencias a la cabeza, cola, tamaño de la lista y un destructor opcional para liberar los datos.

---

## API pública

### `linked_list_init`
```c
Link linked_list_init(void (*destructor)(Type));
```
Inicializa una nueva lista vacía. Acepta un puntero a función destructor para liberar la memoria de los datos; puede ser `NULL` si no es necesario.

**Retorna:** puntero a la lista, o `NULL` en caso de fallo de memoria.

---

### `linked_list_append`
```c
void linked_list_append(Link list, Type data);
```
Inserta un nuevo nodo al **final** de la lista en tiempo O(1) gracias al puntero `tail`.

---

### `linked_list_prepend`
```c
void linked_list_prepend(Link list, Type data);
```
Inserta un nuevo nodo al **inicio** de la lista en tiempo O(1).

---

### `linked_list_insert`
```c
void linked_list_insert(Link list, Type data, int index);
```
Inserta un nodo en la posición indicada por `index`.

- `index == 0` → equivale a `prepend`.
- `index == size` → equivale a `append`.
- `index > size` → operación ignorada.
- Cualquier otro valor → inserta en la posición intermedia en O(n).

---

### `linked_list_delete`
```c
void linked_list_delete(Link list, int index);
```
Elimina el nodo en la posición `index` e invoca el destructor sobre el dato si fue definido.

- `index == 0` → elimina la cabeza.
- `index == size - 1` → elimina la cola.
- `index < 0 || index >= size` → operación ignorada.

---

### `linked_list_find`
```c
Type linked_list_find(Link list, Type data);
```
Recorre la lista buscando un nodo cuyo puntero sea igual a `data` (comparación por dirección, no por valor). Retorna el dato encontrado o `NULL`.

---

### `linked_list_size`
```c
unsigned int linked_list_size(Link list);
```
Retorna el número de nodos en la lista. Si `list == NULL` retorna `0`.

---

### `linked_list_is_empty`
```c
bool linked_list_is_empty(Link list);
```
Retorna `true` si la lista no tiene elementos, `false` en caso contrario. Si `list == NULL` retorna `true`.

---

### `linked_list_destroy`
```c
void linked_list_destroy(Link list);
```
Libera todos los nodos de la lista y la estructura principal. Invoca el destructor en cada dato si fue definido.

---

### `linked_list_print`
```c
void linked_list_print(Link list);
```
Imprime los elementos de la lista asumiendo que cada `Type` es un puntero a `int`. Formato de salida:

```
42 -> 7 -> 15 -> NULL
```

---

## Funciones internas

| Función | Descripción |
|---|---|
| `linked_list_delete_head` | Elimina el nodo cabeza y actualiza el puntero `head`. O(1). |
| `linked_list_delete_tail` | Recorre la lista hasta el penúltimo nodo y elimina la cola. O(n). |

---

## Bugs identificados

No se identificaron bugs en esta versión. ✅

---

## Historial de correcciones

| Versión | Función | Corrección aplicada |
|---|---|---|
| v2 | `linked_list_delete` | `index > index` → `index >= list->size` |
| v2 | `linked_list_is_empty` | Lógica booleana invertida corregida (`size > 0` → `size == 0`) |
| v2 | `linked_list_insert` | Condición de append inalcanzable (`>= size` → `> size`) |
| v3 | `linked_list_is_empty` | Añadida guarda `NULL` |
| v3 | `linked_list_print` | Añadida guarda `NULL` |

---

## Ejemplo de uso

```c
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

void int_destructor(Type data) {
    free(data);
}

int main(void) {
    Link list = linked_list_init(int_destructor);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 20;
    int *c = malloc(sizeof(int)); *c = 30;

    linked_list_append(list, a);   // [10]
    linked_list_append(list, b);   // [10, 20]
    linked_list_prepend(list, c);  // [30, 10, 20]

    linked_list_print(list);
    // 30 -> 10 -> 20 -> NULL

    printf("Tamaño: %u\n", linked_list_size(list));   // 3
    printf("Vacía: %s\n", linked_list_is_empty(list) ? "sí" : "no"); // no

    linked_list_delete(list, 1);   // elimina el 10 → [30, 20]
    linked_list_print(list);
    // 30 -> 20 -> NULL

    linked_list_destroy(list);
    return 0;
}
```

---

## Notas de diseño

- `Type` es un alias de `void *`, lo que permite almacenar cualquier tipo de dato.
- La lista mantiene punteros tanto a `head` como a `tail` para que `append` sea O(1).
- La búsqueda (`find`) es O(n) y compara punteros, no contenido apuntado.
- La eliminación de la cola (`delete_tail`) es O(n) por ser lista simplemente enlazada sin puntero al penúltimo nodo.
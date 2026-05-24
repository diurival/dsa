# Doubly Linked List — Documentación en C

Implementación de una **lista doblemente enlazada** en C con soporte para destructor de datos genérico (`void *`).

---

## Estructuras internas

```c
struct strNode {
    Type data;
    struct strNode *prev;
    struct strNode *next;
};

struct strDLink {
    Node head;
    Node tail;
    unsigned int size;
    void (*destructor)(Type);
};
```

- `strNode`: nodo individual con un dato genérico (`Type`) y punteros al nodo anterior y siguiente.
- `strDLink`: contenedor principal con referencias a la cabeza, cola, tamaño y un destructor opcional.

---

## API pública

### `doubly_linked_list_init`
```c
DLink doubly_linked_list_init(void (*destructor)(Type));
```
Inicializa una nueva lista vacía. El destructor puede ser `NULL` si no es necesario.

**Retorna:** puntero a la lista, o `NULL` en caso de fallo de memoria.

---

### `doubly_linked_list_append`
```c
void doubly_linked_list_append(DLink dlist, Type data);
```
Inserta un nuevo nodo al **final** de la lista en tiempo O(1) gracias al puntero `tail`.

---

### `doubly_linked_list_prepend`
```c
void doubly_linked_list_prepend(DLink dlist, Type data);
```
Inserta un nuevo nodo al **inicio** de la lista en tiempo O(1).

---

### `doubly_linked_list_insert`
```c
void doubly_linked_list_insert(DLink dlist, Type data, int index);
```
Inserta un nodo en la posición indicada por `index`.

- `index == 0` → equivale a `prepend`.
- `index == size` → equivale a `append`.
- `index < 0 || index > size` → operación ignorada.
- Cualquier otro valor → inserta en posición intermedia en O(n).

---

### `doubly_linked_list_delete`
```c
void doubly_linked_list_delete(DLink dlist, int index);
```
Elimina el nodo en la posición `index` e invoca el destructor sobre el dato si fue definido.

- `index == 0` → elimina la cabeza.
- `index == size - 1` → elimina la cola.
- `index < 0 || index >= size` → operación ignorada.

---

### `doubly_linked_list_find`
```c
Type doubly_linked_list_find(DLink dlist, Type data);
```
Búsqueda **bidireccional** — avanza desde la cabeza y desde la cola simultáneamente, reduciendo el recorrido a la mitad en promedio. Compara por dirección de puntero.

**Retorna:** el dato encontrado, o `NULL` si no existe.

---

### `doubly_linked_list_size`
```c
unsigned int doubly_linked_list_size(DLink dlist);
```
Retorna el número de nodos en la lista. Si `dlist == NULL` retorna `0`.

---

### `doubly_linked_list_is_empty`
```c
bool doubly_linked_list_is_empty(DLink dlist);
```
Retorna `true` si la lista no tiene elementos o si `dlist == NULL`, `false` en caso contrario.

---

### `doubly_linked_list_destroy`
```c
void doubly_linked_list_destroy(DLink dlist);
```
Libera todos los nodos de la lista y la estructura principal. Invoca el destructor sobre cada dato si fue definido.

---

### `doubly_linked_list_print`
```c
void doubly_linked_list_print(DLink dlist);
```
Imprime los elementos de la lista asumiendo que cada `Type` es un puntero a `int`. Formato de salida:

```
NULL <-> 10 <-> 20 <-> 30 <-> NULL
```

---

## Funciones internas

| Función | Descripción |
|---|---|
| `doubly_linked_list_delete_head` | Elimina el nodo cabeza, actualiza `head` y su nuevo `prev = NULL`. O(1). |
| `doubly_linked_list_delete_tail` | Elimina el nodo cola, actualiza `tail` y su nuevo `next = NULL`. O(1). |

---

## Diferencias clave vs Singly Linked List

| Operación | Singly | Doubly |
|---|---|---|
| `delete_tail` | O(n) — recorre hasta el penúltimo | O(1) — usa `tail->prev` |
| `print_reverse` | Imposible sin stack auxiliar | O(n) — recorre con `prev` |
| `find` | O(n) unidireccional | O(n/2) bidireccional |
| Memoria por nodo | 1 puntero extra | 2 punteros extra |
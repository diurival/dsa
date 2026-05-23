# Queue — Documentación en C

Implementación de una **cola (FIFO)** en C usando una lista enlazada interna, con soporte para destructor de datos genérico (`void *`).

---

## Estructuras internas

```c
struct strNode {
    Type data;
    struct strNode *next;
};

struct strQueue {
    Node first;
    Node last;
    unsigned int size;
    void (*destructor)(Type);
};
```

- `strNode`: nodo individual que almacena un dato genérico (`Type`) y un puntero al siguiente nodo.
- `strQueue`: contenedor principal con referencias al frente (`first`) y al final (`last`) de la cola, tamaño y un destructor opcional.

---

## API pública

### `queue_init`
```c
Queue queue_init(void (*destructor)(Type));
```
Inicializa una nueva cola vacía. El parámetro `destructor` es un puntero a función para liberar los datos al hacer poll o destruir la cola; puede ser `NULL` si no es necesario.

**Retorna:** puntero a la cola, o `NULL` en caso de fallo de memoria.

---

### `queue_offer`
```c
void queue_offer(Queue q, Type data);
```
Inserta un nuevo elemento al **final** de la cola en tiempo O(1) gracias al puntero `last`.

---

### `queue_poll`
```c
Type queue_poll(Queue q);
```
Extrae y retorna el elemento al **frente** de la cola en tiempo O(1). Libera el nodo pero **no llama al destructor** — la responsabilidad del dato retornado pasa al llamador.

**Retorna:** el dato del frente, o `NULL` si la cola es `NULL` o está vacía.

---

### `queue_peek`
```c
Type queue_peek(Queue q);
```
Retorna el dato al frente de la cola **sin extraerlo**. O(1).

**Retorna:** el dato del frente, o `NULL` si la cola es `NULL` o está vacía.

---

### `queue_size`
```c
int queue_size(Queue q);
```
Retorna el número de elementos en la cola. Si `q == NULL` retorna `0`.

---

### `queue_is_empty`
```c
bool queue_is_empty(Queue q);
```
Retorna `true` si la cola no tiene elementos o si `q == NULL`, `false` en caso contrario.

---

### `queue_destroy`
```c
void queue_destroy(Queue q);
```
Libera todos los nodos de la cola y la estructura principal. Invoca el destructor sobre cada dato si fue definido.

---

## Bugs identificados

| Función | Descripción del bug | Severidad |
|---|---|---|
| `queue_destroy` | No valida `q == NULL` antes de acceder a `q->first` — crash si se pasa `NULL`. | Crash / UB |

---

## Notas de diseño

- `Type` es un alias de `void *`, lo que permite almacenar cualquier tipo de dato.
- `queue_poll` no llama al destructor intencionalmente — retorna el dato al llamador, quien es responsable de liberarlo.
- La cola mantiene punteros a `first` y `last` para que tanto `offer` como `poll` sean O(1).
- `queue_size` retorna `int` en lugar de `unsigned int` (a diferencia del stack y la linked list) — considerar unificar el tipo si se usan juntas.
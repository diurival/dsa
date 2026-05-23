# Stack — Documentación en C

Implementación de una **pila (LIFO)** en C usando una lista enlazada interna, con soporte para destructor de datos genérico (`void *`).

---

## Estructuras internas

```c
struct strNode {
    Type data;
    struct strNode *next;
};

struct strStack {
    Node top;
    unsigned int size;
    void (*destructor)(Type);
};
```

- `strNode`: nodo individual que almacena un dato genérico (`Type`) y un puntero al siguiente nodo.
- `strStack`: contenedor principal con referencia al tope de la pila, tamaño y un destructor opcional para liberar los datos.

---

## API pública

### `stack_init`
```c
Stack stack_init(void (*destructor)(Type));
```
Inicializa una nueva pila vacía. El parámetro `destructor` es un puntero a función para liberar los datos al hacer pop o destruir la pila; puede ser `NULL` si no es necesario.

**Retorna:** puntero a la pila, o `NULL` en caso de fallo de memoria.

---

### `stack_push`
```c
void stack_push(Stack st, Type element);
```
Inserta un nuevo elemento en el **tope** de la pila en tiempo O(1). El nuevo nodo apunta al anterior tope.

---

### `stack_pop`
```c
Type stack_pop(Stack st);
```
Extrae y retorna el elemento en el tope de la pila en tiempo O(1). Libera el nodo pero **no llama al destructor** — la responsabilidad del dato retornado pasa al llamador.

**Retorna:** el dato del tope, o `NULL` si la pila es `NULL` o está vacía.

---

### `stack_top`
```c
Type stack_top(Stack st);
```
Retorna el dato en el tope **sin extraerlo**. O(1).

**Retorna:** el dato del tope, o `NULL` si la pila es `NULL` o está vacía.

---

### `stack_is_empty`
```c
bool stack_is_empty(Stack st);
```
Retorna `true` si la pila no tiene elementos o si `st == NULL`, `false` en caso contrario.

---

### `stack_destroy`
```c
void stack_destroy(Stack st);
```
Libera todos los nodos de la pila y la estructura principal. Invoca el destructor sobre cada dato si fue definido.

---

## Funciones internas

Ninguna. Todas las operaciones se implementan directamente en las funciones públicas.

---

## Notas de diseño

- `Type` es un alias de `void *`, lo que permite almacenar cualquier tipo de dato.
- `stack_pop` no llama al destructor intencionalmente — retorna el dato al llamador, quien es responsable de liberarlo.
- La pila crece hacia el frente de la lista enlazada, por lo que `push` y `pop` son ambos O(1).
- `size` se mantiene actualizado en `push` y `pop`, pero **no en `stack_destroy`** — no es un bug ya que la pila se invalida de todas formas.
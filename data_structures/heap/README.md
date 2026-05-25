# Heap — Documentación en C

Implementación de un **heap binario genérico** en C usando un arreglo dinámico. El comportamiento (min-heap o max-heap) lo determina el comparator proporcionado por el usuario.

---

## Estructuras internas

```c
struct strHeap {
    Type *data;
    unsigned int size;
    unsigned int capacity;
    void (*destructor)(Type);
    int (*comparator)(Type, Type);
};
```

- `data`: arreglo dinámico que almacena los elementos.
- `size`: número de elementos actuales en el heap.
- `capacity`: tamaño actual del arreglo — se duplica automáticamente cuando se llena.
- `destructor`: función opcional para liberar los datos.
- `comparator`: determina el orden del heap. Sigue la convención de `qsort`.

---

## Representación como árbol

El heap se almacena en un arreglo pero representa un árbol binario completo. Las relaciones entre nodos se calculan aritméticamente:

| Relación | Fórmula |
|---|---|
| Hijo izquierdo de `i` | `2i + 1` |
| Hijo derecho de `i` | `2i + 2` |
| Padre de `i` | `(i - 1) / 2` |

---

## API pública

### `heap_init`
```c
Heap heap_init(void (*destructor)(Type), int (*comparator)(Type, Type), int capacity);
```
Inicializa un nuevo heap con la capacidad inicial indicada. Si algún `malloc` falla libera lo ya alocado antes de retornar `NULL`.

**Retorna:** puntero al heap, o `NULL` en caso de fallo de memoria.

---

### `heap_insert`
```c
void heap_insert(Heap heap, Type data);
```
Inserta un elemento en el heap y restaura la propiedad del heap con **heapify up**. Si el arreglo está lleno, duplica la capacidad con `realloc`. O(log n).

**Heapify up:** compara el elemento insertado con su padre repetidamente, intercambiándolos mientras el hijo tenga mayor prioridad, hasta llegar a la raíz o encontrar un padre con mayor prioridad.

---

### `heap_extract`
```c
Type heap_extract(Heap heap);
```
Extrae y retorna la raíz del heap (el elemento con mayor prioridad). Mueve el último elemento a la raíz y restaura la propiedad con **heapify down**. O(log n).

**Heapify down:** compara la nueva raíz con sus hijos, intercambiándola con el hijo de mayor prioridad mientras sea necesario, hasta llegar a una hoja o hasta que el padre tenga mayor prioridad. Maneja tres casos:

- Sin hijos → termina.
- Solo hijo izquierdo → compara únicamente con él.
- Ambos hijos → encuentra el de mayor prioridad y compara con el padre.

**Retorna:** el dato de la raíz, o `NULL` si el heap es `NULL` o está vacío.

---

### `heap_peek`
```c
Type heap_peek(Heap heap);
```
Retorna la raíz del heap **sin extraerla**. O(1).

**Retorna:** el dato de la raíz, o `NULL` si el heap es `NULL` o está vacío.

---

### `heap_size`
```c
unsigned int heap_size(Heap heap);
```
Retorna el número de elementos en el heap. Si `heap == NULL` retorna `0`.

---

### `heap_is_empty`
```c
bool heap_is_empty(Heap heap);
```
Retorna `true` si el heap no tiene elementos o si `heap == NULL`, `false` en caso contrario.

---

### `heap_destroy`
```c
void heap_destroy(Heap heap);
```
Libera todos los datos con el destructor si fue definido, luego libera el arreglo y la estructura principal.

---

## Funciones internas

| Función | Descripción |
|---|---|
| `swap(Type *a, Type *b)` | Intercambia dos elementos del arreglo. |
| `parent_index(int i)` | Retorna `(i - 1) / 2`. |
| `left_child(int i)` | Retorna `2i + 1`. |
| `right_child(int i)` | Retorna `2i + 2`. |

---

## Notas de diseño

- El comparator determina si el heap es min o max — el heap no lo sabe, solo sigue la comparación.
- La capacidad se duplica automáticamente en cada resize, manteniendo el costo amortizado de `insert` en O(1).
- `heap_extract` no llama al destructor — retorna el dato al llamador, quien es responsable de liberarlo.
- A diferencia del stack y la queue, el heap usa un arreglo en lugar de nodos enlazados, lo que mejora la localidad de caché.
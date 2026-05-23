# Binary Search Tree — Documentación en C

Implementación de un **árbol binario de búsqueda (BST)** en C con soporte para comparator y destructor de datos genérico (`void *`).

---

## Estructuras internas

```c
struct strNode {
    Type data;
    struct strNode *left;
    struct strNode *right;
};

struct strTree {
    Node root;
    unsigned int size;
    int (*comparator)(Type, Type);
    void (*destructor)(Type);
};
```

- `strNode`: nodo individual con un dato genérico (`Type`) y punteros a sus hijos izquierdo y derecho.
- `strTree`: contenedor principal con la raíz, el tamaño, y los callbacks de comparación y destrucción.

---

## API pública

### `binary_tree_init`
```c
Tree binary_tree_init(void (*destructor)(Type), int (*comparator)(Type, Type));
```
Inicializa un nuevo árbol vacío.

**Retorna:** puntero al árbol, o `NULL` en caso de fallo de memoria.

---

### `binary_tree_insert`
```c
void binary_tree_insert(Tree tree, Type data);
```
Inserta un nuevo dato en su posición correcta según el comparator. Si el dato ya existe (comparator retorna `0`), lo rechaza y libera el nodo creado. O(log n) promedio, O(n) peor caso.

---

### `binary_tree_delete`
```c
void binary_tree_delete(Tree tree, Type data);
```
Elimina el nodo que contiene `data`. Maneja los tres casos estándar de eliminación en un BST:

| Caso | Estrategia |
|---|---|
| Nodo hoja | Se elimina directamente |
| Un solo hijo | Se reemplaza por ese hijo |
| Dos hijos | Se reemplaza por el sucesor inorder (el menor del subárbol derecho) |

En el caso de dos hijos, el dato del sucesor se copia al nodo actual y el sucesor es liberado, sin llamar al destructor sobre él (correcto, ya que el dato migra al nodo actual).

---

### `binary_tree_search`
```c
Type binary_tree_search(Tree tree, Type data);
```
Busca un dato en el árbol recorriendo según el comparator.

**Retorna:** el dato encontrado, o `NULL` si no existe.

---

### `binary_tree_destroy`
```c
void binary_tree_destroy(Tree tree);
```
Libera todos los nodos del árbol en postorder (izquierda → derecha → raíz) y la estructura principal. Invoca el destructor sobre cada dato si fue definido. Utiliza la función estática auxiliar `destroy`.

---

### `binary_tree_size`
```c
unsigned int binary_tree_size(Tree tree);
```
Retorna el número de nodos en el árbol. Si `tree == NULL` retorna `0`.

---

### `binary_tree_is_empty`
```c
bool binary_tree_is_empty(Tree tree);
```
Retorna `true` si el árbol no tiene elementos o si `tree == NULL`, `false` en caso contrario.

---

## Función interna

### `destroy` (estática)
```c
static void destroy(Node node, DestroyFunc destructor);
```
Recorre el árbol en postorder de forma recursiva liberando cada nodo. Al ser `static`, solo es visible dentro del archivo.

---

## Notas de diseño

- `Type` es un alias de `void *`, lo que permite almacenar cualquier tipo de dato.
- El comparator sigue la convención de `qsort`: negativo si `a < b`, `0` si `a == b`, positivo si `a > b`.
- En el caso de eliminación con dos hijos, el dato del sucesor se **copia** al nodo actual — el destructor no se llama sobre él para evitar liberar un dato que sigue en uso.
- `binary_tree_destroy` usa recursión postorder para garantizar que los hijos se liberan antes que el padre.
- La búsqueda y la inserción son O(log n) en un árbol balanceado y O(n) en el peor caso (árbol degenerado/lineal).
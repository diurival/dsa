# AVL Tree — Documentación en C

Implementación de un **árbol AVL** en C — un árbol binario de búsqueda (BST) autobalanceado que garantiza altura O(log n) en todo momento.

---

## Diferencia con BST

Un BST normal puede degenerarse en una lista enlazada (O(n)) si los datos se insertan en orden. El AVL mantiene la siguiente propiedad en **cada nodo**:

> `|altura(izquierdo) - altura(derecho)| <= 1`

Cuando una inserción o eliminación viola esta propiedad, el árbol se corrige automáticamente mediante **rotaciones**.

---

## Estructuras internas

```c
struct strNode {
    Type data;
    struct strNode *left;
    struct strNode *right;
    int height;
};

struct strTree {
    Node root;
    unsigned int size;
    void (*destructor)(Type);
    int (*comparator)(Type, Type);
};
```

- `strNode`: igual al BST pero con campo `height` adicional para calcular el balance.
- `strTree`: contenedor principal con la raíz, tamaño y los callbacks.

---

## API pública

### `avl_tree_init`
```c
Tree avl_tree_init(void (*destructor)(Type), int (*comparator)(Type, Type));
```
Inicializa un nuevo árbol AVL vacío.

**Retorna:** puntero al árbol, o `NULL` en caso de fallo de memoria.

---

### `avl_tree_insert`
```c
void avl_tree_insert(Tree tree, Type data);
```
Inserta un dato en su posición correcta y rebalancea el árbol si es necesario. Si el dato ya existe (comparator retorna `0`), la operación se ignora. O(log n).

---

### `avl_tree_delete`
```c
void avl_tree_delete(Tree tree, Type data);
```
Elimina el nodo que contiene `data` y rebalancea el árbol. Si el dato no existe, la operación se ignora. O(log n).

Maneja los tres casos estándar:

| Caso | Estrategia |
|---|---|
| Nodo hoja | Se elimina directamente |
| Un solo hijo | Se reemplaza por ese hijo |
| Dos hijos | Se reemplaza por el sucesor inorder; el destructor no se llama sobre el sucesor para evitar destruir el dato que migró |

---

### `avl_tree_search`
```c
Type avl_tree_search(Tree tree, Type data);
```
Busca un dato en el árbol usando el comparator.

**Retorna:** el dato encontrado, o `NULL` si no existe.

---

### `avl_tree_destroy`
```c
void avl_tree_destroy(Tree tree);
```
Libera todos los nodos en postorder (izquierda → derecha → raíz) y la estructura principal. Invoca el destructor sobre cada dato si fue definido.

---

### `avl_tree_size`
```c
unsigned int avl_tree_size(Tree tree);
```
Retorna el número de nodos en el árbol. Si `tree == NULL` retorna `0`.

---

### `avl_tree_is_empty`
```c
bool avl_tree_is_empty(Tree tree);
```
Retorna `true` si el árbol no tiene elementos o si `tree == NULL`, `false` en caso contrario.

---

## Funciones internas

### Auxiliares de altura y balance

| Función | Descripción |
|---|---|
| `height(Node)` | Retorna la altura del nodo; `0` si es `NULL`. |
| `avl_update_height(Node)` | Recalcula `node->height = 1 + max(height(left), height(right))`. |
| `avl_balance(Node)` | Retorna `height(left) - height(right)`; `0` si el nodo es `NULL`. |

### Rotaciones

| Función | Cuándo aplicar |
|---|---|
| `rotate_right` | Balance `> 1` y hijo izquierdo con balance `>= 0` |
| `rotate_left` | Balance `< -1` y hijo derecho con balance `<= 0` |
| `rotate_left_right` | Balance `> 1` y hijo izquierdo con balance `< 0` |
| `rotate_right_left` | Balance `< -1` y hijo derecho con balance `> 0` |

Las rotaciones simples actualizan la altura del nodo que bajó primero y luego del que subió. Las dobles encadenan dos rotaciones simples.

### Recursivas

| Función | Descripción |
|---|---|
| `avl_insert` | Insert recursivo con flag para controlar `size++`. |
| `avl_delete` | Delete recursivo con flag para controlar `size--`. |
| `avl_search` | Search recursivo por el árbol. |
| `postorder` | Recorre el árbol en postorder liberando cada nodo. |

---

## Diferencias clave vs BST

| Aspecto | BST | AVL |
|---|---|---|
| Altura peor caso | O(n) — árbol degenerado | O(log n) — garantizado |
| Insert | O(log n) promedio | O(log n) garantizado |
| Delete | O(log n) promedio | O(log n) garantizado |
| Search | O(log n) promedio | O(log n) garantizado |
| Complejidad de implementación | Simple | Mayor — requiere rotaciones |
| Campo extra por nodo | Ninguno | `height` |

---

## Notas de diseño

- `Type` es un alias de `void *`, lo que permite almacenar cualquier tipo de dato.
- El comparator sigue la convención de `qsort`: negativo si `a < b`, `0` si `a == b`, positivo si `a > b`.
- Los flags `isInserted` e `isDeleted` se pasan por referencia para controlar `size` solo cuando la operación realmente modifica el árbol.
- En el caso de dos hijos, el destructor se pasa como `NULL` en la llamada recursiva al sucesor para evitar destruir el dato que ya migró al nodo actual.
- `max` se asume disponible — puede requerir una macro o función auxiliar dependiendo del compilador.
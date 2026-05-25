# Data Structures & Algorithms in C

Implementaciones de estructuras de datos fundamentales en C, con soporte para datos genéricos mediante `void *` y destructor opcional en cada estructura.

---

## Estructuras implementadas

| Estructura | Archivo | Estado |
|---|---|---|
| Singly Linked List | `linked_list/` | ✅ |
| Doubly Linked List | `doubly_linked_list/` | ✅ |
| Stack | `stack/` | ✅ |
| Queue | `queue/` | ✅ |
| Binary Search Tree | `binary_tree/` | ✅ |

---

## Estructura del repositorio

```
dsa/
├── singly_linked_list/
│   ├── singly_linked_list.h
│   ├── singly_linked_list.c
│   └── README.md
├── doubly_linked_list/
│   ├── doubly_linked_list.h
│   ├── doubly_linked_list.c
│   └── README.md
├── stack/
│   ├── stack.h
│   ├── stack.c
│   └── README.md
├── queue/
│   ├── queue.h
│   ├── queue.c
│   └── README.md
├── binary_tree/
│   ├── binary_tree.h
│   ├── binary_tree.c
│   └── README.md
└── README.md
```

---

## Diseño general

Todas las estructuras siguen las mismas convenciones:

- `Type` es un alias de `void *` — permite almacenar cualquier tipo de dato.
- Todas aceptan un `destructor` opcional en el `init` para liberar la memoria de los datos.
- Las funciones verifican `NULL` antes de operar.
- El BST acepta además un `comparator` con la convención de `qsort`: negativo, 0, o positivo.

---

## Resumen de operaciones

### Singly Linked List
| Función | Complejidad |
|---|---|
| `linked_list_append` | O(1) |
| `linked_list_prepend` | O(1) |
| `linked_list_insert` | O(n) |
| `linked_list_delete` | O(n) |
| `linked_list_find` | O(n) |

### Doubly Linked List
| Función | Complejidad |
|---|---|
| `doubly_linked_list_append` | O(1) |
| `doubly_linked_list_prepend` | O(1) |
| `doubly_linked_list_insert` | O(n) |
| `doubly_linked_list_delete` | O(n) |
| `doubly_linked_list_find` | O(n/2) |

### Stack
| Función | Complejidad |
|---|---|
| `stack_push` | O(1) |
| `stack_pop` | O(1) |
| `stack_top` | O(1) |

### Queue
| Función | Complejidad |
|---|---|
| `queue_offer` | O(1) |
| `queue_poll` | O(1) |
| `queue_peek` | O(1) |

### Binary Search Tree
| Función | Complejidad |
|---|---|
| `binary_tree_insert` | O(log n) promedio |
| `binary_tree_delete` | O(log n) promedio |
| `binary_tree_search` | O(log n) promedio |

---

## Autor
Diego Uribe Alvarez

Hecho a mano en C como parte de mi aprendizaje de estructuras de datos y algoritmos.

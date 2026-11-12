# Estructuras de Datos en C

Implementación desde cero de las estructuras de datos fundamentales en C11, con manejo manual de memoria, pruebas unitarias y una demo con casos de uso reales.

![C](https://img.shields.io/badge/C-11-00599C?logo=c&logoColor=white)
![Make](https://img.shields.io/badge/build-Makefile-informational)
![Tests](https://img.shields.io/badge/tests-33%20passing-brightgreen)

## Estructuras incluidas

| Estructura | Archivo | Detalles de implementación | Complejidad clave |
|---|---|---|---|
| Lista enlazada | `src/lista.c` | Inserción al inicio/final, eliminación con doble puntero, inversión in-place | Insertar inicio O(1), buscar O(n) |
| Pila (LIFO) | `src/pila.c` | Arreglo dinámico que duplica su capacidad con `realloc` | Apilar O(1) amortizado |
| Cola (FIFO) | `src/cola.c` | Buffer circular de capacidad fija | Encolar / desencolar O(1) |
| Árbol binario de búsqueda | `src/arbol.c` | Inserción sin duplicados, eliminación con sucesor inorden, recorrido con callback | Buscar O(log n) promedio |

## Demo

La demo muestra cada estructura resolviendo un problema concreto:

- **Pila** → verificar si una expresión tiene paréntesis balanceados.
- **Cola** → simular turnos de atención en orden de llegada.
- **Árbol** → ordenar valores con un recorrido inorden.

```
== Pila: parentesis balanceados ==
(a+b)*[c-d]    -> balanceado
(a+b))         -> NO balanceado

== Arbol binario de busqueda ==
Inorden (ordenado): 3 12 25 45 60 78 99
Altura: 3
```

## Cómo ejecutarlo

Requiere `gcc` y `make`.

```bash
make demo && ./demo     # compila y ejecuta la demo
make test               # compila y corre las pruebas unitarias
make memcheck           # pruebas bajo valgrind (detecta fugas de memoria)
make clean
```

## Estructura del proyecto

```
estructuras-datos-c/
├── include/      # Interfaces públicas (.h)
├── src/          # Implementaciones y demo
├── tests/        # Pruebas unitarias sin dependencias externas
└── Makefile
```

## Lo que practiqué

- Gestión de memoria dinámica (`malloc`, `realloc`, `free`) sin fugas.
- Uso de punteros a punteros para simplificar inserciones y eliminaciones.
- Separación entre interfaz (`.h`) e implementación (`.c`).
- Punteros a función para recorridos genéricos del árbol.
- Pruebas unitarias con macros propias y compilación con `-Wall -Wextra -Wpedantic`.

## Autor

**Rendy Silva** — Estudiante de Ingeniería en Software, Universidad de las Américas (UDLA), Quito.

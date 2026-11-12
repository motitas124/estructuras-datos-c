#ifndef ARBOL_H
#define ARBOL_H

#include <stdbool.h>
#include <stddef.h>

/* Arbol binario de busqueda (BST) de enteros, sin duplicados. */
typedef struct NodoArbol {
    int valor;
    struct NodoArbol *izq;
    struct NodoArbol *der;
} NodoArbol;

typedef struct {
    NodoArbol *raiz;
    size_t tamano;
} Arbol;

typedef void (*Visitante)(int valor, void *contexto);

Arbol *arbol_crear(void);
void   arbol_destruir(Arbol *a);
bool   arbol_insertar(Arbol *a, int valor);
bool   arbol_buscar(const Arbol *a, int valor);
bool   arbol_eliminar(Arbol *a, int valor);
int    arbol_altura(const Arbol *a);
void   arbol_inorden(const Arbol *a, Visitante f, void *contexto);

#endif

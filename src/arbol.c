#include "arbol.h"

#include <stdlib.h>

Arbol *arbol_crear(void) {
    Arbol *a = malloc(sizeof *a);
    if (a == NULL) return NULL;
    a->raiz = NULL;
    a->tamano = 0;
    return a;
}

static void destruir_nodo(NodoArbol *n) {
    if (n == NULL) return;
    destruir_nodo(n->izq);
    destruir_nodo(n->der);
    free(n);
}

void arbol_destruir(Arbol *a) {
    if (a == NULL) return;
    destruir_nodo(a->raiz);
    free(a);
}

bool arbol_insertar(Arbol *a, int valor) {
    NodoArbol **enlace = &a->raiz;
    while (*enlace != NULL) {
        if (valor == (*enlace)->valor) return false; /* sin duplicados */
        enlace = valor < (*enlace)->valor ? &(*enlace)->izq : &(*enlace)->der;
    }
    NodoArbol *n = malloc(sizeof *n);
    if (n == NULL) return false;
    n->valor = valor;
    n->izq = n->der = NULL;
    *enlace = n;
    a->tamano++;
    return true;
}

bool arbol_buscar(const Arbol *a, int valor) {
    const NodoArbol *n = a->raiz;
    while (n != NULL) {
        if (valor == n->valor) return true;
        n = valor < n->valor ? n->izq : n->der;
    }
    return false;
}

bool arbol_eliminar(Arbol *a, int valor) {
    NodoArbol **enlace = &a->raiz;
    while (*enlace != NULL && (*enlace)->valor != valor)
        enlace = valor < (*enlace)->valor ? &(*enlace)->izq : &(*enlace)->der;
    if (*enlace == NULL) return false;

    NodoArbol *borrar = *enlace;
    if (borrar->izq == NULL) {
        *enlace = borrar->der;
    } else if (borrar->der == NULL) {
        *enlace = borrar->izq;
    } else {
        /* Dos hijos: se reemplaza por el sucesor inorden (minimo del subarbol derecho). */
        NodoArbol **suc = &borrar->der;
        while ((*suc)->izq != NULL) suc = &(*suc)->izq;
        NodoArbol *sucesor = *suc;
        *suc = sucesor->der;
        sucesor->izq = borrar->izq;
        sucesor->der = borrar->der;
        *enlace = sucesor;
    }
    free(borrar);
    a->tamano--;
    return true;
}

static int altura_nodo(const NodoArbol *n) {
    if (n == NULL) return 0;
    int hi = altura_nodo(n->izq), hd = altura_nodo(n->der);
    return 1 + (hi > hd ? hi : hd);
}

int arbol_altura(const Arbol *a) { return altura_nodo(a->raiz); }

static void inorden_nodo(const NodoArbol *n, Visitante f, void *ctx) {
    if (n == NULL) return;
    inorden_nodo(n->izq, f, ctx);
    f(n->valor, ctx);
    inorden_nodo(n->der, f, ctx);
}

void arbol_inorden(const Arbol *a, Visitante f, void *contexto) {
    inorden_nodo(a->raiz, f, contexto);
}

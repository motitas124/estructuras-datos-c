#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

Lista *lista_crear(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL) return NULL;
    l->cabeza = NULL;
    l->tamano = 0;
    return l;
}

void lista_destruir(Lista *l) {
    if (l == NULL) return;
    NodoLista *actual = l->cabeza;
    while (actual != NULL) {
        NodoLista *sig = actual->siguiente;
        free(actual);
        actual = sig;
    }
    free(l);
}

static NodoLista *nodo_nuevo(int valor) {
    NodoLista *n = malloc(sizeof *n);
    if (n == NULL) return NULL;
    n->valor = valor;
    n->siguiente = NULL;
    return n;
}

bool lista_insertar_inicio(Lista *l, int valor) {
    NodoLista *n = nodo_nuevo(valor);
    if (n == NULL) return false;
    n->siguiente = l->cabeza;
    l->cabeza = n;
    l->tamano++;
    return true;
}

bool lista_insertar_final(Lista *l, int valor) {
    NodoLista *n = nodo_nuevo(valor);
    if (n == NULL) return false;
    if (l->cabeza == NULL) {
        l->cabeza = n;
    } else {
        NodoLista *actual = l->cabeza;
        while (actual->siguiente != NULL) actual = actual->siguiente;
        actual->siguiente = n;
    }
    l->tamano++;
    return true;
}

bool lista_eliminar(Lista *l, int valor) {
    NodoLista **enlace = &l->cabeza;
    while (*enlace != NULL) {
        if ((*enlace)->valor == valor) {
            NodoLista *borrar = *enlace;
            *enlace = borrar->siguiente;
            free(borrar);
            l->tamano--;
            return true;
        }
        enlace = &(*enlace)->siguiente;
    }
    return false;
}

bool lista_contiene(const Lista *l, int valor) {
    for (NodoLista *n = l->cabeza; n != NULL; n = n->siguiente)
        if (n->valor == valor) return true;
    return false;
}

void lista_invertir(Lista *l) {
    NodoLista *anterior = NULL, *actual = l->cabeza;
    while (actual != NULL) {
        NodoLista *sig = actual->siguiente;
        actual->siguiente = anterior;
        anterior = actual;
        actual = sig;
    }
    l->cabeza = anterior;
}

void lista_imprimir(const Lista *l) {
    printf("[");
    for (NodoLista *n = l->cabeza; n != NULL; n = n->siguiente)
        printf("%d%s", n->valor, n->siguiente ? " -> " : "");
    printf("]\n");
}

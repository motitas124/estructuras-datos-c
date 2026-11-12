#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/* Lista enlazada simple de enteros. */
typedef struct NodoLista {
    int valor;
    struct NodoLista *siguiente;
} NodoLista;

typedef struct {
    NodoLista *cabeza;
    size_t tamano;
} Lista;

Lista *lista_crear(void);
void   lista_destruir(Lista *l);
bool   lista_insertar_inicio(Lista *l, int valor);
bool   lista_insertar_final(Lista *l, int valor);
bool   lista_eliminar(Lista *l, int valor);
bool   lista_contiene(const Lista *l, int valor);
void   lista_invertir(Lista *l);
void   lista_imprimir(const Lista *l);

#endif

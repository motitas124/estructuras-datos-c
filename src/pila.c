#include "pila.h"

#include <stdlib.h>

Pila *pila_crear(size_t capacidad_inicial) {
    if (capacidad_inicial == 0) capacidad_inicial = 4;
    Pila *p = malloc(sizeof *p);
    if (p == NULL) return NULL;
    p->datos = malloc(capacidad_inicial * sizeof *p->datos);
    if (p->datos == NULL) {
        free(p);
        return NULL;
    }
    p->tamano = 0;
    p->capacidad = capacidad_inicial;
    return p;
}

void pila_destruir(Pila *p) {
    if (p == NULL) return;
    free(p->datos);
    free(p);
}

bool pila_apilar(Pila *p, int valor) {
    if (p->tamano == p->capacidad) {
        size_t nueva = p->capacidad * 2;
        int *tmp = realloc(p->datos, nueva * sizeof *tmp);
        if (tmp == NULL) return false;
        p->datos = tmp;
        p->capacidad = nueva;
    }
    p->datos[p->tamano++] = valor;
    return true;
}

bool pila_desapilar(Pila *p, int *salida) {
    if (p->tamano == 0) return false;
    *salida = p->datos[--p->tamano];
    return true;
}

bool pila_cima(const Pila *p, int *salida) {
    if (p->tamano == 0) return false;
    *salida = p->datos[p->tamano - 1];
    return true;
}

bool pila_vacia(const Pila *p) { return p->tamano == 0; }

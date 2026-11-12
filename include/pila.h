#ifndef PILA_H
#define PILA_H

#include <stdbool.h>
#include <stddef.h>

/* Pila (LIFO) sobre un arreglo dinamico que crece al doble. */
typedef struct {
    int *datos;
    size_t tamano;
    size_t capacidad;
} Pila;

Pila *pila_crear(size_t capacidad_inicial);
void  pila_destruir(Pila *p);
bool  pila_apilar(Pila *p, int valor);
bool  pila_desapilar(Pila *p, int *salida);
bool  pila_cima(const Pila *p, int *salida);
bool  pila_vacia(const Pila *p);

#endif

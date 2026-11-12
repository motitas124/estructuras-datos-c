#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stddef.h>

/* Cola (FIFO) implementada como buffer circular de capacidad fija. */
typedef struct {
    int *datos;
    size_t frente;
    size_t tamano;
    size_t capacidad;
} Cola;

Cola *cola_crear(size_t capacidad);
void  cola_destruir(Cola *c);
bool  cola_encolar(Cola *c, int valor);
bool  cola_desencolar(Cola *c, int *salida);
bool  cola_vacia(const Cola *c);
bool  cola_llena(const Cola *c);

#endif

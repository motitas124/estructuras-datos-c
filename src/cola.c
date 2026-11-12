#include "cola.h"

#include <stdlib.h>

Cola *cola_crear(size_t capacidad) {
    if (capacidad == 0) return NULL;
    Cola *c = malloc(sizeof *c);
    if (c == NULL) return NULL;
    c->datos = malloc(capacidad * sizeof *c->datos);
    if (c->datos == NULL) {
        free(c);
        return NULL;
    }
    c->frente = 0;
    c->tamano = 0;
    c->capacidad = capacidad;
    return c;
}

void cola_destruir(Cola *c) {
    if (c == NULL) return;
    free(c->datos);
    free(c);
}

bool cola_encolar(Cola *c, int valor) {
    if (cola_llena(c)) return false;
    size_t fin = (c->frente + c->tamano) % c->capacidad;
    c->datos[fin] = valor;
    c->tamano++;
    return true;
}

bool cola_desencolar(Cola *c, int *salida) {
    if (cola_vacia(c)) return false;
    *salida = c->datos[c->frente];
    c->frente = (c->frente + 1) % c->capacidad;
    c->tamano--;
    return true;
}

bool cola_vacia(const Cola *c) { return c->tamano == 0; }
bool cola_llena(const Cola *c) { return c->tamano == c->capacidad; }

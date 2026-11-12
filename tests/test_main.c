/* Pruebas unitarias minimas sin dependencias externas. */
#include <stdio.h>

#include "arbol.h"
#include "cola.h"
#include "lista.h"
#include "pila.h"

static int fallos = 0, total = 0;

#define CHECK(cond)                                                     \
    do {                                                                \
        total++;                                                        \
        if (!(cond)) {                                                  \
            fallos++;                                                   \
            printf("  FALLO %s:%d -> %s\n", __FILE__, __LINE__, #cond); \
        }                                                               \
    } while (0)

static void test_lista(void) {
    Lista *l = lista_crear();
    lista_insertar_final(l, 1);
    lista_insertar_final(l, 2);
    lista_insertar_inicio(l, 0);
    CHECK(l->tamano == 3);
    CHECK(lista_contiene(l, 2));
    lista_invertir(l);
    CHECK(l->cabeza->valor == 2);
    CHECK(lista_eliminar(l, 1));
    CHECK(!lista_eliminar(l, 99));
    CHECK(l->tamano == 2);
    lista_destruir(l);
}

static void test_pila(void) {
    Pila *p = pila_crear(1);
    for (int i = 0; i < 100; i++) pila_apilar(p, i);
    int v;
    CHECK(pila_cima(p, &v) && v == 99);
    CHECK(pila_desapilar(p, &v) && v == 99);
    CHECK(p->tamano == 99);
    while (pila_desapilar(p, &v)) {}
    CHECK(pila_vacia(p));
    CHECK(!pila_desapilar(p, &v));
    pila_destruir(p);
}

static void test_cola(void) {
    Cola *c = cola_crear(3);
    CHECK(cola_encolar(c, 1) && cola_encolar(c, 2) && cola_encolar(c, 3));
    CHECK(cola_llena(c));
    CHECK(!cola_encolar(c, 4));
    int v;
    CHECK(cola_desencolar(c, &v) && v == 1);
    CHECK(cola_encolar(c, 4)); /* da la vuelta al buffer circular */
    CHECK(cola_desencolar(c, &v) && v == 2);
    CHECK(cola_desencolar(c, &v) && v == 3);
    CHECK(cola_desencolar(c, &v) && v == 4);
    CHECK(cola_vacia(c));
    cola_destruir(c);
}

typedef struct { int vals[16]; int n; } Recolector;
static void recolectar(int v, void *ctx) {
    Recolector *r = ctx;
    r->vals[r->n++] = v;
}

static void test_arbol(void) {
    Arbol *a = arbol_crear();
    int datos[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) arbol_insertar(a, datos[i]);
    CHECK(!arbol_insertar(a, 50)); /* duplicado */
    CHECK(a->tamano == 7);
    CHECK(arbol_altura(a) == 3);
    CHECK(arbol_buscar(a, 60));
    CHECK(arbol_eliminar(a, 50)); /* nodo con dos hijos */
    CHECK(!arbol_buscar(a, 50));
    Recolector r = {.n = 0};
    arbol_inorden(a, recolectar, &r);
    int esperado[] = {20, 30, 40, 60, 70, 80};
    CHECK(r.n == 6);
    for (int i = 0; i < 6; i++) CHECK(r.vals[i] == esperado[i]);
    arbol_destruir(a);
}

int main(void) {
    printf("Lista...\n");  test_lista();
    printf("Pila...\n");   test_pila();
    printf("Cola...\n");   test_cola();
    printf("Arbol...\n");  test_arbol();
    printf("\n%d/%d pruebas pasaron\n", total - fallos, total);
    return fallos == 0 ? 0 : 1;
}

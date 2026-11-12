/* Pequena demostracion de las estructuras en consola. */
#include <stdio.h>

#include "arbol.h"
#include "cola.h"
#include "lista.h"
#include "pila.h"

static void imprimir(int v, void *ctx) {
    (void)ctx;
    printf("%d ", v);
}

/* Verifica si los parentesis de una expresion estan balanceados usando una pila. */
static int balanceado(const char *expr) {
    Pila *p = pila_crear(8);
    int ok = 1, tope;
    for (const char *c = expr; *c && ok; c++) {
        if (*c == '(' || *c == '[' || *c == '{') {
            pila_apilar(p, *c);
        } else if (*c == ')' || *c == ']' || *c == '}') {
            char abre = *c == ')' ? '(' : *c == ']' ? '[' : '{';
            ok = pila_desapilar(p, &tope) && tope == abre;
        }
    }
    ok = ok && pila_vacia(p);
    pila_destruir(p);
    return ok;
}

int main(void) {
    printf("== Lista enlazada ==\n");
    Lista *l = lista_crear();
    for (int i = 1; i <= 5; i++) lista_insertar_final(l, i * 10);
    lista_imprimir(l);
    lista_invertir(l);
    printf("Invertida: ");
    lista_imprimir(l);
    lista_destruir(l);

    printf("\n== Pila: parentesis balanceados ==\n");
    const char *exprs[] = {"(a+b)*[c-d]", "{[()]}", "(a+b))", "([)]"};
    for (int i = 0; i < 4; i++)
        printf("%-14s -> %s\n", exprs[i], balanceado(exprs[i]) ? "balanceado" : "NO balanceado");

    printf("\n== Cola: turnos de atencion ==\n");
    Cola *c = cola_crear(4);
    for (int t = 101; t <= 104; t++) cola_encolar(c, t);
    int turno;
    while (cola_desencolar(c, &turno)) printf("Atendiendo turno %d\n", turno);
    cola_destruir(c);

    printf("\n== Arbol binario de busqueda ==\n");
    Arbol *a = arbol_crear();
    int datos[] = {45, 12, 78, 3, 25, 60, 99};
    for (int i = 0; i < 7; i++) arbol_insertar(a, datos[i]);
    printf("Inorden (ordenado): ");
    arbol_inorden(a, imprimir, NULL);
    printf("\nAltura: %d\n", arbol_altura(a));
    arbol_destruir(a);
    return 0;
}

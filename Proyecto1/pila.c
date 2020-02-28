#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "pila.h"

tPila* crearPila() {
    tPila* pila = (tPila*)asignar(sizeof(tPila));
    if (pila != NULL) { // Pudo asignar la pila en la memoria
        pila->elem = 0;
        pila->next = NULL;
        return pila;
    } else {
        return NULL;
    }
}

int tope(tPila* P) {
    if (!pilaVacia(P)) {
        return P->next->elem; // La primera posicion de la pila funciona como centinela
    } else {
        printf("Se solicito el tope de una pila vacia.\n");
        exit(1);
    }
}

int desapilar(tPila** P) {
    if (!pilaVacia(*P)) {
        tPila* aux = (*P)->next;
        (*P)->next = aux->next;
        int elem = aux->elem;
        liberar(aux);
        return elem;
    } else {
        printf("Se solicito desapilar una pila vacia.\n");
        exit(2);
    }
}

int apilar(int a, tPila** P) {
    tPila* nuevo = (tPila*)asignar(sizeof(tPila));
    if (nuevo != NULL) { // Pudo asignar la pila en la memoria
        nuevo->elem = a;
        nuevo->next = (*P)->next;
        (*P)->next = nuevo;
        return 0; // Operacion exitosa
    } else {
        return 1; // Operacion fallida
    }
}

int pilaVacia(tPila* P) {
    return P->next == NULL;
}

tPila* subPila(int (*f)(int, int), int a, tPila* P) {
    tPila* sub = crearPila();
    tPila* index = P->next; // Tope de la pila P
    while (index != NULL) {
        int elem = index->elem;
        if ((*f)(elem, a) > 0) {
            apilar(elem, &sub);
        }
        index = index->next;
    }
    return sub;
}

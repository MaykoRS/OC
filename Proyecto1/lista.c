#include <stdlib.h>
#include "lista.h"

tLista crearLista() {
    tLista lista = {NULL, NULL, 0};
    return lista;
}

void insertarAtras(tLista* L, tNodo* pos, tElemento x) {
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    nuevo->elem = x;
    // Si el nodo es la cola hay que reasignar la direccion de tail
    if (pos != L->tail) {
        nuevo->next = pos->next;
    } else {
        L->tail = nuevo;
    }
    pos->next = nuevo;
    L->size = L->size + 1; // Actualizar tamaño
}

void insertarPpio(tLista* L, tElemento x) {
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    nuevo->elem = x;
    nuevo->next = L->header;
    L->header = nuevo;
    // Si la lista esta vacia header y tail apuntan al mismo nodo
    if (L->size == 0) {
        L->tail = nuevo;
    }
    L->size = L->size + 1; // Actualizar tamaño
}

tNodo* siguiente(tNodo* pos) {
    return pos->next;
}

tNodo* primera(tLista L) {
    return L.header;
}

tNodo* ultima(tLista L) {
    return L.tail;
}

void eliminar(tLista* L, tNodo* pos) { // Asumimos que pos pertenece a L
    if (L->header == pos) {
        // Si la posicion a eliminar es el header
        L->header = pos->next;
        // Si es el ultimo elemento en la lista
        if (pos == L->tail) {
            L->tail = NULL;
        }
    } else {
        tNodo* anterior = L->header;
        while (anterior->next != pos) {
            anterior = anterior->next;
        }
        // El siguiente de anterior es pos
        anterior->next = pos->next;
        if (pos == L->tail) {
            // Si la posicion a eliminar es el tail
            L->tail = anterior;
        }
    }
    L->size = L->size - 1; // Actualizar tamaño
    free(pos);
}

tElemento* elemento(tNodo* pos) {
    return &pos->elem;
}

int listaVacia(tLista L) {
    return !L.size;
}

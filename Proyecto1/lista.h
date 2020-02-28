#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct Elemento {
    int a;
    int b;
} tElemento;

typedef struct Nodo {
    tElemento elem;
    struct Nodo* next;
} tNodo;

typedef struct Lista {
    tNodo* header; // Puntero al primer nodo de la lista
    tNodo* tail; // Puntero al �ltimo nodo de la lista
    int size;
} tLista;

tLista crearLista(); // Crea una lista vac�a y la devuelve

void insertarAtras(tLista* L, tNodo* pos, tElemento x); // Inserta el elemento x en la posici�n inmediata siguiente a pos en la lista

void insertarPpio(tLista* L, tElemento x); // Inserta el elemento x en la primera posici�n de la lista

tNodo* siguiente(tNodo* pos); // Devuelve la posici�n siguiente a la posici�n pos. Devuelve NULL si p es NULL o si no existe posici�n siguiente

tNodo* primera(tLista L); // Devuelve la primera posici�n de la lista L

tNodo* ultima(tLista L); // Devuelve la �ltima posici�n de la lista L

void eliminar(tLista* L, tNodo* pos); // Elimina el elemento de la posici�n pos de la lista

tElemento* elemento(tNodo* pos); // Devuelve un puntero al elemento que ocupa la posici�n pos de la lista

int listaVacia(tLista L); // Devuelve verdadero si la lista est� vac�a y falso si la lista contiene al menos un elemento

#endif // LISTA_H_INCLUDED

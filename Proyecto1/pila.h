#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct Pila {
    int elem;
    struct Pila* next;
} tPila;

tPila* crearPila(); // Retorna una pila vacía nueva. Retorna NULL en caso de no poder crear la pila

int tope(tPila* P);
/* Retorna el entero que se encuentra en el tope de la pila.
Su comportamiento no está definido en caso de que la pila se encuentre vacía */

int desapilar(tPila** P); // Elimina el entero que se encuentra en el tope de la pila y lo retorna

int apilar(int a, tPila** P); // Inserta el entero a en el tope de la pila. Retorna 0 si la inserción fue exitosa, =/=0 en caso contrario

int pilaVacia(tPila* P); // Devuelve verdadero si la pila está vacía, falso en caso contrario

tPila* subPila(int (*f)(int, int), int a, tPila* P); // Crea una nueva pila con todos los elementos e de la pila tales que f(e,a) es verdadero

#endif // PILA_H_INCLUDED

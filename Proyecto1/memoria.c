#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "memoria.h"

char * mem = NULL;
tLista libres;
tLista ocupados;

int inicializarMemoria(int max) {
    int aux = max;
    while (aux % 8 != 0) {
        aux++;
    }

    if (mem != NULL) { // La memoria ya fue inicializada
        return 2;
    }

    mem = (char*)malloc(aux);
    libres = crearLista();
    ocupados = crearLista();
    tElemento elem = {0, aux - 1};
    insertarPpio(&libres, elem);
    if ((libres.header == NULL) || (libres.tail == NULL)) { // Cualquier otro error
        return 3;
    }

    if (mem == NULL) { // No hay suficiente memoria
        return 1;
    } else { // Ningun error
        return 0;
    }
}

void* asignar(int cant) {
    int index = -1;
    tNodo* nodo = libres.header;
    while ((index == -1) && (nodo != NULL)) {
        // Busca el primer bloque libre en la lista con un tamaño mayor o igual al buscado
        if ((elemento(nodo)->b - elemento(nodo)->a + 1) >= cant) {
            index = elemento(nodo)->a;
        } else {
            nodo = siguiente(nodo);
        }
    }
    // Si no encontro espacio retorna NULL
    if (nodo == NULL) {
        return NULL;
    }
    elemento(nodo)->a = index + cant; // Actualizacion del nodo libre

    tElemento elem = {index, index + cant - 1}; // Nuevo nodo con el bloque ocupado
    if (listaVacia(ocupados)) {
        insertarPpio(&ocupados, elem);
    } else {
        if (elem.b < elemento(ocupados.header)->a) { // Si elem es menor que el header
            insertarPpio(&ocupados, elem);
        } else {
            tNodo* aux = ocupados.header;
            while ((aux != ocupados.tail) && (elem.b > elemento(siguiente(aux))->a)) { // Mientras b de elem sea mayor que a del siguiente de aux
                aux = siguiente(aux);
            }
            insertarAtras(&ocupados, aux, elem);
        }
    }

    return mem + index; // Puntero de mem + index en el arreglo = puntero de index
}

void liberar(void* bloque) { // Asumimos que el bloque es un bloque ocupado
    int index = ((char*)bloque) - mem; // Puntero de bloque - puntero de mem = posicion en el arreglo
    int fin;
    tNodo* aux = ocupados.header;
    while ((aux != ocupados.tail) && (elemento(aux)->a != index)) {
        aux = siguiente(aux);
    }
    // Ahora aux es el bloque a liberar
    if (elemento(aux)->a == index) {
        fin = elemento(aux)->b; // Posicion del fin del bloque
    } else {
        // Llego al final de la lista sin haber encontrado el bloque solicitado
        printf("Se solicito liberar un bloque de memoria que no fue asignado.\n");
        exit(3);
    }
    eliminar(&ocupados, aux); // Se elimina el bloque de la lista ocupados

    // Devolver el bloque a la lista de libres
    tElemento liberado = {index, fin};
    if (listaVacia(libres)) {
        insertarPpio(&libres, liberado);
    } else {
        if (liberado.b < elemento(libres.header)->a) { // Verifica si liberado es el mas chico de la lista
            if (liberado.b + 1 == elemento(libres.header)->a) {
                elemento(libres.header)->a = liberado.a; // Si los bloques son consecutivos se fusionan
            } else {
                insertarPpio(&libres, liberado); // Sino se agrega al principio
            }
        } else {
            tNodo* anterior = libres.header;
            while ((aux != ocupados.tail) && (liberado.b > elemento(siguiente(anterior))->a)) {
                anterior = siguiente(anterior);
            }
            // Ahora liberado deberia ir entre anterior y el siguiente a anterior
            if (anterior == libres.tail) { // Si anterior es el tail
                if (elemento(anterior)->b + 1 == liberado.a) {
                    elemento(anterior)->b = liberado.b; // Si los bloques son consecutivos se fusionan
                } else {
                    insertarAtras(&libres, anterior, liberado); // Sino se agrega despues de anterior
                }
            } else {
                if ((elemento(anterior)->b + 1 == liberado.a) && (liberado.b + 1 == elemento(siguiente(anterior))->a)) {
                    elemento(anterior)->b = elemento(siguiente(anterior))->b; // Si los 3 bloques son consecutivos se fusionan
                    eliminar(&libres, siguiente(anterior));
                } else if (elemento(anterior)->b + 1 == liberado.a) {
                    elemento(anterior)->b = liberado.b; // Si el bloque anterior y el liberado son consecutivos se fusionan
                } else if (liberado.b + 1 == elemento(siguiente(anterior))->a) {
                    elemento(siguiente(anterior))->a = liberado.a; // Si el bloque liberado y el siguiente son consecutivos se fusionan
                } else {
                    insertarAtras(&libres, anterior, liberado); // Sino se agrega despues de anterior
                }
            }
        }
    }
}

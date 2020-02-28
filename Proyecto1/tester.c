#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "memoria.h"
#include "pila.h"


// Tester de la lista
int main() {
    int opcion = -1; // Numero fuera de rango
    tLista lista = crearLista();
    printf("1: Lista vacia?\n");
    printf("2: Insertar al principio\n");
    printf("3: Mostrar primer elemento\n");
    printf("4: Mostrar ultimo elemento\n");
    printf("5: Eliminar primer elemento\n");
    printf("6: Eliminar ultimo elemento\n");
    printf("7: Insertar despues del ultimo\n");
    printf("8: Mostrar lista\n");
    printf("9: Cantidad de elementos\n");
    printf("0: Cerrar\n");
    while (opcion != 0) {
        printf("Ingrese una opcion:\n");
        scanf("%i", &opcion);
        switch(opcion) {
            case 0: // Cerrar
                break;
            case 1: // Lista vacia?
                if (listaVacia(lista) == 1) {
                    printf("La lista esta vacia.\n");
                } else {
                    printf("La lista no esta vacia.\n");
                };
                break;
            case 2: { // Insertar al principio
                int aux = 0;
                printf("Ingrese un entero:\n");
                scanf("%i", &aux);
                tElemento elem = {aux, aux};
                insertarPpio(&lista, elem);
                printf("Valor ingresado exitosamente.\n");
                }
                break;
            case 3: { // Mostrar primer elemento
                if (listaVacia(lista) == 0) {
                    int elem = elemento(primera(lista))->a;
                    printf("El primer elemento es: %i\n", elem);
                } else {
                    printf("La lista esta vacia.\n");
                }
                }
                break;
            case 4: { // Mostrar ultimo elemento
                if (listaVacia(lista) == 0) {
                    int elem = elemento(ultima(lista))->a;
                    printf("El ultimo elemento es: %i\n", elem);
                } else {
                    printf("La lista esta vacia.\n");
                }
                }
                break;
            case 5: { // Eliminar primer elemento
                if (listaVacia(lista) == 0) {
                    tNodo* nodo = primera(lista);
                    eliminar(&lista, nodo);
                    printf("Eliminacion exitosa.\n");
                } else {
                    printf("La lista esta vacia.\n");
                }
                }
                break;
            case 6: { // Eliminar ultimo elemento
                if (listaVacia(lista) == 0) {
                    tNodo* nodo = ultima(lista);
                    eliminar(&lista, nodo);
                    printf("Eliminacion exitosa.\n");
                } else {
                    printf("La lista esta vacia.\n");
                }
                }
                break;
            case 7: { // Insertar despues del ultimo
                if (listaVacia(lista) == 0) {
                    int aux = 0;
                    printf("Ingrese un entero:\n");
                    scanf("%i", &aux);
                    tElemento elem = {aux, aux};
                    tNodo* nodo = ultima(lista);
                    insertarAtras(&lista, nodo, elem);
                    printf("Valor ingresado exitosamente.\n");
                } else {
                    printf("La lista esta vacia.\n");
                }
                }
                break;
            case 8: { // Mostrar lista
                if (listaVacia(lista) == 0) {
                    tNodo* index = primera(lista);
                    tNodo* ult = ultima(lista);
                    printf("Los elementos son: ");
                    while (index != NULL) {
                        printf("%i", elemento(index)->a);
                        if (index != ult) {
                            printf(", ");
                        } else {
                            printf("\n");
                        }
                        index = siguiente(index);
                    }
                } else {
                    printf("La lista esta vacia.\n");
                }
                }
                break;
            case 9: { // Cantidad de elementos
                printf("La lista tiene %i elementos\n", lista.size);
                }
                break;
        }
    }
    return 0;
}


/*
// Tester de la pila
int mayor(int elem, int num) {
    return elem > num;
}

int menor(int elem, int num) {
    return elem < num;
}

int multiplo(int elem, int num) {
    return elem % num == 0;
}

int obtenerNumeroCriterio(char* c) {
    int index = 1;
    int num = 0;
    while (c[index] != '\0') {
        int aux = c[index] - '0';
        num = (num * 10) + aux;
        index++;
    }
    return num;
}

int main() {
    int opcion = -1; // Numero fuera de rango
    inicializarMemoria(1024);
    tPila* pila = crearPila();
    printf("1: Pila vacia?\n");
    printf("2: Apilar\n");
    printf("3: Desapilar\n");
    printf("4: Mostrar tope de la pila\n");
    printf("5: Mostrar pila\n");
    printf("6: Generar subpila\n");
    printf("0: Cerrar\n");
    while (opcion != 0) {
        printf("Ingrese una opcion:\n");
        scanf("%i", &opcion);
        switch(opcion) {
            case 0: // Cerrar
                break;
            case 1: // Pila vacia?
                if (pilaVacia(pila)) {
                    printf("La pila esta vacia.\n");
                } else {
                    printf("La pila no esta vacia.\n");
                };
                break;
            case 2: { // Apilar
                int aux = 0;
                printf("Ingrese un entero:\n");
                scanf("%i", &aux);
                apilar(aux, &pila);
                printf("Valor ingresado exitosamente.\n");
                }
                break;
            case 3: { // Desapilar
                if (pilaVacia(pila)) {
                    desapilar(&pila);
                    printf("Elemento desapilado exitosamente.\n");
                } else {
                    printf("La pila esta vacia.\n");
                }
                }
                break;
            case 4: { // Mostrar tope de la pila
                if (pilaVacia(pila)) {
                    int elem = tope(pila);
                    printf("El tope de la pila es: %i\n", elem);
                } else {
                    printf("La pila esta vacia.\n");
                }
                }
                break;
            case 5: { // Mostrar pila
                if (pilaVacia(pila)) {
                    tPila* index = pila->next;
                    printf("Los elementos son: \n");
                    while (index != NULL) {
                        int elem = index->elem;
                        printf("%i\n", elem);
                        index = index->next;
                    }
                } else {
                    printf("La pila esta vacia.\n");
                }
                }
                break;
            case 6: { // Generar subpila
                if (pilaVacia(pila)) {
                    char entrada[5];
                    tPila* aux;
                    printf("Ingrese un criterio:\n");
                    scanf("%s", &entrada);
                    int num = obtenerNumeroCriterio(entrada);
                    if (entrada[0] == '%') { // Criterio multiplo
                        printf("Subpila con los elementos multiplos de %i\n", num);
                        aux = subPila(&multiplo, num, pila);
                    } else if (entrada[0] == '>') { // Criterio mayor
                        printf("Subpila con los elementos mayores que %i\n", num);
                        aux = subPila(&mayor, num, pila);
                    } else { // Criterio menor
                        printf("Subpila con los elementos menores que %i\n", num);
                        aux = subPila(&menor, num, pila);
                    }
                    while (!pilaVacia(aux)) {
                        printf("%i\n", desapilar(&aux));
                    }
                } else {
                    printf("La pila esta vacia.\n");
                }
                }
                break;
        }
    }
    return 0;
}
*/

// Tester de la memoria
/*
int main() {
    int max = 32;
    int valor = inicializarMemoria(max);
    int aux;

    printf("Resultado de inicializar la memoria: %i\n", valor);
    printf("El tamano de la memoria es: %i bytes.\n", max);

    int * num1 = (int*)asignar(sizeof(int));
    printf("1 int: %i (%i bytes)\n", num1, sizeof(int));
    if (num1 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    char * arreglo = (char*)asignar(4*sizeof(char));
    printf("4 cha: %i (4 * %i bytes)\n", arreglo, sizeof(char));
    if (arreglo == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Ingresar un numero para seguir:\n");
    scanf("%i", &aux);

    int * num2 = (int*)asignar(sizeof(int));
    printf("1 int: %i (%i bytes)\n", num2, sizeof(int));
    if (num2 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    int * num3 = (int*)asignar(sizeof(int));
    printf("1 int: %i (%i bytes)\n", num3, sizeof(int));
    if (num3 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Ingresar un numero para seguir:\n");
    scanf("%i", &aux);

    printf("Se libera la memoria del primer int.\n");
    liberar(num1);

    char * a = (char*)asignar(sizeof(char));
    printf("1 cha: %i (%i bytes)\n", a, sizeof(char));
    if (a == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    char * b = (char*)asignar(sizeof(char));
    printf("1 cha: %i (%i bytes)\n", b, sizeof(char));
    if (b == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    char * c = (char*)asignar(sizeof(char));
    printf("1 cha: %i (%i bytes)\n", c, sizeof(char));
    if (c == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    char * d = (char*)asignar(sizeof(char));
    printf("1 cha: %i (%i bytes)\n", d, sizeof(char));
    if (d == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Ingresar un numero para seguir:\n");
    scanf("%i", &aux);

    printf("Se libera la memoria del arreglo de char.\n");
    liberar(arreglo);

    int * num4 = (int*)asignar(sizeof(int));
    printf("1 int: %i (%i bytes)\n", num4, sizeof(int));
    if (num4 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Se libera la memoria del tercer int.\n");
    liberar(num3);

    int * num5 = (int*)asignar(sizeof(int));
    printf("1 int: %i (%i bytes)\n", num5, sizeof(int));
    if (num5 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Ingresar un numero para seguir:\n");
    scanf("%i", &aux);

    // Liberar un espacio de memoria menor al necesario
    printf("Se libera la memoria de un char.\n");
    liberar(a);

    int * num6 = (int*)asignar(sizeof(int));
    printf("1 int: %i (%i bytes)\n", num6, sizeof(int));
    if (num6 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Ingresar un numero para seguir:\n");
    scanf("%i", &aux);

    printf("Se libera toda la memoria.\n");
    liberar(b);
    liberar(c);
    liberar(d);
    liberar(num2);
    liberar(num4);
    liberar(num5);
    liberar(num6);

    tPila * pila1 = (tPila*)asignar(sizeof(tPila));
    printf("1 pila: %i (%i bytes)\n", pila1, sizeof(tPila));
    if (pila1 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    tPila * pila2 = (tPila*)asignar(sizeof(tPila));
    printf("1 pila: %i (%i bytes)\n", pila2, sizeof(tPila));
    if (pila2 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    printf("Se libera la segunda pila.\n");
    liberar(pila2);

    tPila * pila3 = (tPila*)asignar(sizeof(tPila));
    printf("1 pila: %i (%i bytes)\n", pila3, sizeof(tPila));
    if (pila3 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    tPila * pila4 = (tPila*)asignar(sizeof(tPila));
    printf("1 pila: %i (%i bytes)\n", pila4, sizeof(tPila));
    if (pila4 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    tPila * pila5 = (tPila*)asignar(sizeof(tPila));
    printf("1 pila: %i (%i bytes)\n", pila5, sizeof(tPila));
    if (pila5 == NULL) {
        printf("No hay espacio suficiente en la memoria.\n");
    }

    return 0;
}
*/

/*
// Tester convertir char a int
int obtenerNum(char* c) {
    int index = 1;
    int num = 0;
    while (c[index] != '\0') {
        int aux = c[index] - '0';
        num = (num * 10) + aux;
        index++;
    }
    return num;
}

int main() {
    char buffer[5];
    printf("Ingresar un numero con un simbolo al principio:\n");
    scanf("%s", &buffer);
    printf("%i\n", obtenerNum(&buffer));
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "memoria.h"

int mayor(int elem, int num) {
    return elem > num;
}

int menor(int elem, int num) {
    return elem < num;
}

int multiplo(int elem, int num) {
    return elem % num == 0;
}

void mostrarAyuda() {
    printf("-h: Pagina de ayuda del programa.\n");
    printf("El programa recibe como argumentos un archivo de enteros y un criterio\n");
    printf("y muestra por pantalla los enteros que cumplan con esa condicion.\n");
    printf("Tambien puede recibir un archivo de salida, y escribir el resultado en el mismo.\n");
    printf("[<criterio><archivo entrada>] [<archivo salida>]\n");
}

void mostrarError() {
    printf("***Parametros invalidos***\n");
}

// Verifica que el criterio pasado por parametro sea valido
int verificarCriterio(char* c) {
    int i = 1;
    if ((c[0] == '>') || (c[0] == '<') || (c[0] == '%')) { // Verifica que el simbolo del criterio sea correcto
        while ((c[i] != '\0') && (i != 0)) {
            int number = (int)c[i];
            if ((number >= 48) && (number <= 57)) { // Verifica que el resto de los caracteres sean numeros
                i++;
            } else {
                i = 0;
            }
        }
    } else {
        i = 0;
    }
    return i;
}

// Verifica que el archivo pasado por parametro exista
int verificarEntrada(char* c) {
    FILE* f = fopen(c, "r");
    if (f == NULL) {
        printf("El archivo solicitado por parametro no existe.\n");
        exit(4);
    }
    fclose(f);
    return 1;
}

// Retorna el numero correspondiente al criterio ingresado por parametro
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

int main(int argc, char** argv) {
    // Se inicializa la memoria
    int max = 1024;
    inicializarMemoria(max);
    tPila* pila; // Se usa para la subpila

    // Se elige una opcion segun la cantidad de parametros ingresados por el usuario
    switch (argc) {
    case 1: { // Ningun parametro
        mostrarAyuda();
        }
        break;
    case 2: { // Un parametro
        if (((argv[1])[0] != '-') || ((argv[1])[1] != 'h') || ((argv[1])[2] || '\0')) {
            mostrarError();
        }
        mostrarAyuda();
        }
        break;
    case 3: { // Dos parametros
        if ((verificarCriterio(argv[1])) && (verificarEntrada(argv[2]))) {
            // Parametros correctos
            FILE* f = fopen(argv[2], "r");
            tPila* aux = crearPila();
            // Se lee el archivo y se pasa a una pila auxiliar
            int num;
            int res;
            while (!feof(f)) {
                fscanf(f, "%d\n", &num);
                res = apilar(num, &aux);
                if (res == 1) {
                    printf("Se solicito memoria para apilar, pero la memoria esta llena.\n");
                    exit(5);
                }
            }
            // Determinar criterio
            int val = obtenerNumeroCriterio(argv[1]);
            if ((argv[1])[0] == '%') { // Criterio multiplo
                printf("Subpila con los elementos multiplos de %i:\n", val);
                pila = subPila(&multiplo, val, aux);
            } else if ((argv[1])[0] == '>') { // Criterio mayor
                printf("Subpila con los elementos mayores que %i:\n", val);
                pila = subPila(&mayor, val, aux);
            } else { // Criterio menor
                printf("Subpila con los elementos menores que %i:\n", val);
                pila = subPila(&menor, val, aux);
            }
            // Mostar subpila por consola
            int ap;
            while (!pilaVacia(pila)) {
                ap = desapilar(&pila);
                printf("%i\n", ap);
            }
            fclose(f);
        } else {
            mostrarError();
            mostrarAyuda();
        }
        }
        break;
    case 4: { // Tres parametros
        if ((verificarCriterio(argv[1])) && (verificarEntrada(argv[2]))) {
            // Parametros correctos
            FILE* f = fopen(argv[2], "r");
            FILE* out = fopen(argv[3], "w");
            tPila* aux = crearPila();
            // Se lee el archivo y se pasa a una pila auxiliar
            int num;
            int res;
            while (!feof(f)) {
                fscanf(f, "%d\n", &num);
                res = apilar(num, &aux);
                if (res == 1) {
                    printf("Se solicito memoria para apilar, pero la memoria esta llena.\n");
                    exit(5);
                }
            }
            // Determinar criterio
            int val = obtenerNumeroCriterio(argv[1]);
            if ((argv[1])[0] == '%') { // Criterio multiplo
                printf("Subpila con los elementos multiplos de %i:\n", val);
                pila = subPila(&multiplo, val, aux);
            } else if ((argv[1])[0] == '>') { // Criterio mayor
                printf("Subpila con los elementos mayores que %i:\n", val);
                pila = subPila(&mayor, val, aux);
            } else { // Criterio menor
                printf("Subpila con los elementos menores que %i:\n", val);
                pila = subPila(&menor, val, aux);
            }
            // Mostar subpila por consola
            int ap;
            while (!pilaVacia(pila)) {
                ap = desapilar(&pila);
                printf("%i\n", ap);
                fprintf(out, "%i\n", ap);
            }
            fclose(f);
            fclose(out);
        } else {
            mostrarError();
            mostrarAyuda();
        }
        }
        break;
    default: { // Mas de tres parametros
        mostrarError();
        mostrarAyuda();
        }
        break;
    }
    return 0;
}

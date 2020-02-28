#ifndef MEMORIA_H_INCLUDED
#define MEMORIA_H_INCLUDED

int inicializarMemoria(int max);
/* Crea e incializa un espacio de memoria de m bytes, siendo m el menor múltiplo
de 8 mayor o igual que max. Este función debe inicializar las lista de bloques
libres de forma tal que toda la memoria esté disponible. Retorna 0 si la creación
fue exitosa, 1 si no hay suficiente memoria, 2 si la memoria ya fue inicializada
y 3 en cualquier otro error */

void* asignar(int cant);
/* Reserva cant bytes de memoria contigua y devuelve el
puntero al primer byte. Retorna NULL en caso de no poder encontrar cant bytes contiguos */

void liberar(void* bloque); // Libera el bloque de memoria apuntado por bloque y actualiza las estructuras auxiliares

#endif // MEMORIA_H_INCLUDED

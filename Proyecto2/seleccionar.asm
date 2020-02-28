%include "atoi.asm"
%include "itoa.asm"

%define stdout 1
%define stdin 0

%define sys_exit 1
%define sys_write 4
%define sys_open 5
%define sys_creat 8

%define O_RDONLY 0
%define O_WRONLY 1
%define O_RDWR 2

%define sys_call 0x80 ; Valor de la llamada al sistema

section .data

	txt_error db "Hubo un error", 10
	long_error equ $ - txt_error

	txt_error_entrada db "El archivo de entrada no existe o no se encuentra en este directorio", 10
	long_error_entrada equ $ - txt_error_entrada

	txt_ayuda db "-h: Texto de ayuda...", 10
	long_ayuda equ $ - txt_ayuda
	
	txt_multiplo db "Multiplos de "
	long_multiplo equ $ - txt_multiplo
	
	txt_mayor db "Mayores que "
	long_mayor equ $ - txt_mayor
	
	txt_menor db "Menores que "
	long_menor equ $ - txt_menor
	
	salto db 0xA ; Valor del salto de linea

section .bss

	buffer resb 100 ; Buffer para guardar un string

section .text

	global _start

imprimir_salto:

	; Imprime un salto de linea
	; Requiere el valor de la salida en EBX
	mov EAX, sys_write					; Selecciono la llamada al sistema write
	mov ECX, salto						; Puntero al primer char de salto
	mov EDX, 1							; Longitud del string 1
	int sys_call						; Llamo al sistema operativo
	
	ret									; Retorno

_start:

	; El nombre del archivo se cuenta como argumento
	pop EAX								; Recupero la cantidad de argumentos
	
	; 1 argumento representa el nombre del programa
	cmp EAX, 1							; Comparo la cantidad de argumentos con 1
	je error_3 							; Salto al error 3 (argumentos invalidos)
	
	; 2 argumentos representan el nombre del programa y el comando de ayuda
	cmp EAX, 2							; Comparo la cantidad de argumentos con 2
	je param_2							; Salto a la seccion de 2 parametros
	
	; 3 argumentos representan el nombre del programa, el criterio y el archivo de entrada
	cmp EAX, 3							; Comparo la cantidad de argumentos con 3
	je param_3							; Salto a la seccion de 3 parametros
	
	; 4 argumentos representan el nombre del programa, el criterio, el archivo de entrada y archivo de salida
	cmp EAX, 4							; Comparo la cantidad de argumentos con 4
	je param_4							; Salto a la seccion de 4 parametros
	
	; Si llego hasta aca es porque habia mas de 4 argumentos
	jmp error_3							; Salto al error 3

param_2:

	; Ver si el argumento es -h
	pop EBX								; Descarto el primer parámetro (nombre del programa)
	pop EBX								; Recupero el segundo parámetro
	mov CL, BYTE [EBX] 					; Recupero el primer caracter
	cmp CL, 0x2D						; Comparo con '-' (guion)
	jne error_3							; Salto a error_3 si es distinto
	inc EBX								; Avanzo la posición del string
	mov CL, BYTE [EBX] 					; Recupero el segundo caracter
	cmp CL, 0x68						; Comparo con 'h'
	jne error_3							; Salto a error_3 si es distinto
	inc EBX								; Avanzo la posición del string
	mov CL, BYTE [EBX] 					; Recupero el tercer caracter
	cmp CL, 0x0							; Comparo con 0 (terminador)
	jne error_3							; Salto a error_3 si es distinto	
	je ayuda							; Salto a ayuda si es igual

param_3:

	; Ver si los argumentos son el criterio y archivo de entrada
	; Verifico el criterio
	pop EBX								; Descarto el primer parámetro (nombre del programa)
	pop EBX								; Recupero el segundo parámetro (criterio)
	mov CL, BYTE [EBX]					; Recupero el primer caracter
	
	inc EBX								; Avanzo al primer caracter del número
	mov EAX, EBX						; Guardo el puntero al primer caracter del número en EAX para llamar a atoi
	call atoi							; Llamo a atoi que me devuelve el entero en EAX (atoi debe preservar los valores de EBX y ECX)

	pop EBX								; Recupero el tercer parámetro (nombre del archivo de entrada)
	push EAX							; Guardo en la pila el número del criterio
	push ECX							; Guardo en la pila el criterio
	
	; Abro el archivo de entrada en modo solo lectura (requiere el nombre del archivo en EBX)
	mov EAX, sys_open					; Selecciono la llamada al sistema para abrir
	mov ECX, O_RDONLY					; Modo solo lectura
	int sys_call						; Llamo al sistema operativo
	
	cmp EAX, 0							; Examino el descriptor de archivo
	jl	error_1							; Si es menor que 0 salgo con error 1
	
	mov EDX, EAX						; Guardo en EDX el descriptor de archivo
	pop ECX								; Recupero de la pila el criterio
	pop EAX								; Recupero de la pila el número del criterio

	; Ahora tengo el número del criterio en EAX
	cmp CL, 0x25						; Comparo con '%' (porcentaje)
	je func_multiplo					; Salto a func_multiplo
	
	cmp CL, 0x3E						; Comparo con '>' (mayor)
	je func_mayor						; Salto a func_mayor
	
	cmp CL, 0x3C						; Comparo con '<' (menor)
	je func_menor						; Salto a func_menor
	
	; Si llego hasta aca es porque el criterio no coincide
	jmp error_3							; Salgo con error 3

param_4:

	; Ver si los argumentos son el criterio, archivo de entrada y archivo de salida
	mov EBX, 0							; Salgo sin errores 
	call salir 							; Llamo a salir (lo dejamos para testear)

ayuda:

	mov EAX, sys_write 					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en salida estándar
	mov ECX, txt_ayuda					; Puntero al primer char
	mov EDX, long_ayuda					; Longitud del string
	int sys_call						; Llamo al sistema operativo

	mov EBX, 0							; Salgo con error 0
	call salir							; Llamo a salir

error_1:

	; Cambiar texto segun tipo de error
	mov EAX, sys_write 					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en salida estándar
	mov ECX, txt_error_entrada 			; Puntero al primer char
	mov EDX, long_error_entrada			; Longitud del string
	int sys_call						; Llamo al sistema operativo

	mov EAX, sys_write 					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en salida estándar
	mov ECX, txt_ayuda					; Puntero al primer char
	mov EDX, long_ayuda					; Longitud del string
	int sys_call						; Llamo al sistema operativo

	mov EBX, 1							; Salgo con error 1
	call salir							; Llamo a salir

error_3:

	mov EAX, sys_write 					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en salida estándar
	mov ECX, txt_error 					; Puntero al primer char
	mov EDX, long_error					; Longitud del string
	int sys_call						; Llamo al sistema operativo

	mov EAX, sys_write 					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en salida estándar
	mov ECX, txt_ayuda					; Puntero al primer char
	mov EDX, long_ayuda					; Longitud del string
	int sys_call						; Llamo al sistema operativo

	mov EBX, 3							; Salgo con error 3
	call salir							; Llamo a salir

func_multiplo:

	; Función que determina los numeros que son multiplos de X
	; Requiere el número del criterio en EAX
	push EAX							; Guardo en la pila el número del criterio
	
	mov EAX, sys_write					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en la salida estándar
	mov ECX, txt_multiplo				; Puntero al primer char
	mov EDX, long_multiplo				; Longitud del string
	int sys_call						; Llamo al sistema operativo
	
	; Tengo que mantener el número como entero para poder usarlo después

	pop EAX								; Cargo el número del criterio en EAX
	mov EBX, buffer						; Puntero al buffer de caracteres
	call itoa							; Convierto el valor en EAX a string en buffer (itoa debe preservar los registros ECX y EDX)
	
	; Ahora buffer tiene el número convertido a string y EAX tiene la longitud del string
	push EAX							; Guardo la longitud en la pila
	
	mov EAX, sys_write					; Selecciono la llamada al sistema write
	mov EBX, stdout						; Escribo en la salida estándar
	mov ECX, buffer						; Puntero al primer char de buffer
	pop EDX								; Desapilo la longitud del string
	int sys_call						; Llamo al sistema operativo
	
	mov EBX, stdout						; Escribo en la salida estándar
	call imprimir_salto					; Imprimo un salto de linea

	; Leo los enteros del archivo y verifico si cumplen con el criterio, de ser asi los muestro por pantalla
	
	mov EBX, 0							; Salgo sin errores
	call salir							; Llamo a salir

func_mayor:

	; Función que determina los numeros que son mayores que X
	; Requiere el número del criterio en EAX
	push EAX							; Guardo en la pila el número del criterio
	
	mov EAX, sys_write			; Selecciono la llamada al sistema write
	mov EBX, stdout				; Escribo en la salida estándar
	mov ECX, txt_mayor			; Puntero al primer char
	mov EDX, long_mayor		; Longitud del string
	int sys_call				; Llamo al sistema operativo
	
	; Tengo que mantener el número como entero para poder usarlo después

	pop EAX						; Cargo el número del criterio en EAX
	mov EBX, buffer				; Puntero al buffer de caracteres
	call itoa					; Convierto el valor en EAX a string en buffer (itoa debe preservar los registros ECX y EDX)
	
	; Ahora buffer tiene el número convertido a string y EAX tiene la longitud del string
	push EAX					; Guardo la longitud en la pila
	
	mov EAX, sys_write			; Selecciono la llamada al sistema write
	mov EBX, stdout				; Escribo en la salida estándar
	mov ECX, buffer				; Puntero al primer char de buffer
	pop EDX						; Desapilo la longitud del string
	int sys_call				; Llamo al sistema operativo
	
	mov EBX, stdout				; Escribo en la salida estándar
	call imprimir_salto			; Imprimo un salto de linea

	; Leo los enteros del archivo y verifico si cumplen con el criterio, de ser asi los muestro por pantalla
	
	mov EBX, 0					; Salgo sin errores
	call salir					; Llamo a salir

func_menor:

	; Función que determina los numeros que son menores que X
	; Requiere el número del criterio en EAX
	push EAX					; Guardo en la pila el número del criterio
	
	mov EAX, sys_write			; Selecciono la llamada al sistema write
	mov EBX, stdout				; Escribo en la salida estándar
	mov ECX, txt_menor			; Puntero al primer char
	mov EDX, long_menor			; Longitud del string
	int sys_call				; Llamo al sistema operativo
	
	; Tengo que mantener el número como entero para poder usarlo después

	pop EAX						; Cargo el número del criterio en EAX
	mov EBX, buffer				; Puntero al buffer de caracteres
	call itoa					; Convierto el valor en EAX a string en buffer (itoa debe preservar los registros ECX y EDX)
	
	; Ahora buffer tiene el número convertido a string y EAX tiene la longitud del string
	push EAX					; Guardo la longitud en la pila
	
	mov EAX, sys_write			; Selecciono la llamada al sistema write
	mov EBX, stdout				; Escribo en la salida estándar
	mov ECX, buffer				; Puntero al primer char de buffer
	pop EDX						; Desapilo la longitud del string
	int sys_call				; Llamo al sistema operativo
	
	mov EBX, stdout				; Escribo en la salida estándar
	call imprimir_salto			; Imprimo un salto de linea

	; Leo los enteros del archivo y verifico si cumplen con el criterio, de ser asi los muestro por pantalla
	
	mov EBX, 0					; Salgo sin errores
	call salir					; Llamo a salir

salir:

	; Requiere el valor del error en el registro EBX
	mov EAX, sys_exit			; Llamo al sys_exit
	int sys_call				; Llamo al sistema operativo
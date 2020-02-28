; Función atoi que convierte string a entero

; Toma como parámetro un puntero a string en EAX
; y lo convierte a entero en EAX

section .text

atoi:

	; Guardo en la pila los valores de los registros EBX y ECX
	push EBX					; Apilo EBX
	push ECX					; Apilo ECX

    ; En ECX guardo el resultado parcial
    mov ECX, 0					; Inicializo el número en 0

atoi_siguiente:

    mov EBX, 0					; Pongo en blanco a EBX
    mov BL, BYTE [EAX]			; Recupero el siguiente caracter
    cmp BL, 0					; Comparo con 0 (terminador)
    je atoi_fin					; Fin del string

    ; Convertir el char a decimal (restarle 48)
    sub BL, 48					; Resto 48 a BL

    ; Actualizar el entero parcial
    imul ECX, 10				; Multiplico el resultado parcial por 10
    add ECX, EBX				; Sumo el dígito actual

    inc EAX						; Avanzo la posición del string

    jmp atoi_siguiente			; Siguiente iteración

atoi_fin:

    mov EAX, ECX				; Guardo el resultado en EAX
	
	; Recupero los valores de los registros EBX y ECX
	pop ECX						; Desapilo ECX
	pop EBX						; Desapilo EBX
	
    ret							; Retorno
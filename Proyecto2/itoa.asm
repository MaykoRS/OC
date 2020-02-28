; Función itoa que convierte un entero en EAX a string en un buffer apuntado por EBX

; EAX - entero (sin signo)
; EBX - puntero a char

; Retorna la longitud del string en EAX

section .data
	
	diez dd 10

section .text

itoa:

	; Guardo en la pila los valores de los registros ECX y EDX
	push ECX					; Apilo ECX
	push EDX					; Apilo EDX

	push EBX					; Guardo en tope de pila el puntero al buffer
	mov ECX, 0					; Cantida de digitos del número

itoa_dividir:
	
	mov EDX, 0					; Inicializo en 0 la parte mas significativa del dividendo
	
	; En EAX tengo el dividendo
	; Dividir EAX por 10
	idiv DWORD [diez]	 		; Ahora EAX tiene el cociente y EDX el resto
	add EDX, 0x30				; Convierto a ASCII el dígito menos significativo
	push EDX					; Guardo en la pila el caracter
	inc ECX						; Incremento el contador
	cmp EAX, 0					; Es el cociente igual a 0?
	jnz	itoa_dividir			; Si no es cero, vuelvo a dividir

	; En este punto tengo todos los caracteres en la pila
	; y ECX tiene la cantidad de caracteres
	mov EAX, ECX				; Guardo una copia del contador

itoa_guardar:

	pop EDX						; Recupero el últmo caracter (más significativo)
	mov [EBX], DL				; Guardo el caracter más significativo
	inc EBX						; Avanzo el puntero al siguiente char
	dec ECX						; Decremento el contador
	jnz itoa_guardar			; Paso al siguiente char
	
	; Limpieza y retorno
	pop EBX 					; Recupero el puntero a la posición inicial
	
	; Recupero los valores de los registros ECX y EDX
	pop EDX						; Desapilo EDX
	pop ECX						; Desapilo ECX
	
	ret							; Retorno
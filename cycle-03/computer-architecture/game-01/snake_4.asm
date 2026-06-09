#make_com#
ORG 100h

MOV AX, 0B800h
MOV ES, AX  ;Utilizamos el Extra Segment para la VRAM. El DS leerá el arreglo (cuerpo) del SNAKE


MOV CX, 8
MOV SI, 14

DIBUJAR_CUERPO:
        MOV BX, CUERPO_SNAKE[SI]  
        MOV WORD PTR ES:[BX], 0A7Fh    ; 0Ah: verde fosforecente y fondo negro, 3Eh: caracter '>' 
        ADD SI, -2
        LOOP DIBUJAR_CUERPO

DESPLAZAMIENTO_SNAKE:
    
    MOV AH, 01h ; INT para escuchar si se ha presionado una tecla. ZF devolverá 0 si es así.
    INT 16h
    JZ FISICA

    MOV AH, 00h
    INT 16h
    
    CMP AH, 48h ; flecha arriba
    JE DIR_ARRIBA
    CMP AH, 50h ; flecha abajo
    JE DIR_ABAJO
    CMP AH, 4Bh ; flecha izquierda
    JE DIR_IZQUIERDA
    CMP AH, 4Dh ; flecha derecha
    JE DIR_DERECHA
    
    DIR_ARRIBA:
        MOV VECTOR_DIRECCION, -160
        JMP FISICA
    DIR_ABAJO:
        MOV VECTOR_DIRECCION, 160
        JMP FISICA
    DIR_IZQUIERDA:
        MOV VECTOR_DIRECCION, -2
        JMP FISICA
    DIR_DERECHA:
        MOV VECTOR_DIRECCION, 2
        JMP FISICA
     
    FISICA:
   
        MOV AH, 86h
        MOV CX, 0001h
        MOV DX, 86A0h
        INT 15h         ; invocamos la INT 15h/86h para darle 100k microsegundos de espera
        
        MOV SI, 14      ; borramos la cola
        MOV BX, CUERPO_SNAKE[SI]
        MOV WORD PTR ES:[BX], 0020h
        
        MOV SI, 12
        MOV CX, 7
    
    REASIGNAR_CUERPO_SNAKE:
        MOV AX, CUERPO_SNAKE[SI]
        MOV CUERPO_SNAKE[SI+2], AX
        ADD SI, -2
        LOOP REASIGNAR_CUERPO_SNAKE
    
    MOV SI, 0         ; desplazamos la cabeza
    MOV AX, VECTOR_DIRECCION
    ADD CUERPO_SNAKE[SI], AX
    MOV BX, CUERPO_SNAKE[SI]
    MOV WORD PTR ES:[BX], 0A7Fh
    
    JMP DESPLAZAMIENTO_SNAKE



RET

;Datos:
CUERPO_SNAKE DW 07D0h, 07CEh, 07CCh, 07CAh, 07C8h, 07C6h, 07C4h, 07C2h  ; Cuerpo de la serpiente
VECTOR_DIRECCION DW 2
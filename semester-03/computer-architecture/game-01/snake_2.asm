#make_com#
ORG 100h

MOV AX, 0B800h    
MOV DS, AX        

MOV BX, 07D0h     ; Empezamos en el centro de la pantalla

; --- FASE 3: EL MOTOR DEL JUEGO (GAME LOOP) ---
MOTOR_PRINCIPAL:     

    ; 1. DIBUJAR LA CABEZA
    MOV WORD PTR [BX], 0A3Eh  ; AH=0Ah (Verde), AL=3Eh ('>')
    
    ; 2. FRENAR EL TIEMPO (Delay de 0.1 segundos)
    MOV AH, 86h       ; Función 86h: Pausar CPU
    MOV CX, 0001h     ; Mitad alta de 100,000
    MOV DX, 86A0h     ; Mitad baja de 100,000
    INT 15h           ; Llamada al BIOS para ejecutar la pausa

    ; 3. BORRAR EL RASTRO (Destrucción)
    ; Si no borramos, dejaremos una línea sólida de >>>>>>>
    MOV WORD PTR [BX], 0020h  ; AH=00h (Negro), AL=20h (' ' Espacio)

    ; 4. ACTUALIZAR FÍSICA (Cinemática)
    ADD BX, 2         ; Movemos el puntero 2 bytes a la derecha

    ; 5. REPETIR EL BUCLE
    JMP MOTOR_PRINCIPAL

RET
#make_com#
ORG 100h

; --- FASE 1: APUNTAR AL MONITOR ---
MOV AX, 0B800h    
MOV DS, AX        

; --- FASE 2: DIBUJAR LA SERPIENTE INICIAL ---
MOV DI, 07D0h     ; DI apuntará siempre a la COLA (Inicia en el centro)
MOV BX, 07D0h     ; BX apuntará siempre a la CABEZA
MOV CX, 8         ; Longitud inicial: 8 bloques

MOV AX, 0A3Eh    ; AH = 0Ah (Fondo negro, texto Verde), AL = 03Eh (Bloque)

DIBUJAR_INICIAL:
    MOV [BX], AX    
    ADD BX, 2       
    LOOP DIBUJAR_INICIAL

SUB BX, 2         ; Corregimos la cabeza (el LOOP avanza BX una vez de más al final)
                  ; Ahora DI = Cola, BX = Cabeza. ¡Estamos listos!

; --- FASE 3: EL BUCLE PRINCIPAL DEL JUEGO (GAME LOOP) ---
GAME_LOOP:
    
    ; 1. Hablar con el hardware del teclado
    MOV AH, 00h     ; Comando 00h para la INT 16h: "Pausar y esperar una tecla"
    INT 16h         ; ¡Llamada al BIOS! (Devuelve la tecla en AH y AL)

    ; 2. Decodificar la señal física (Scan Codes)
    CMP AH, 4Dh     ; Comparamos (Resta lógica): ¿Fue la Flecha Derecha?
    JE MOVER_DER    ; Jump if Equal (Si ZF=1, salta a la rutina de derecha)
    
    CMP AH, 4Bh     ; ¿Fue la Flecha Izquierda?
    JE MOVER_IZQ    ; Jump if Equal (Salta a la rutina de izquierda)
    
    JMP GAME_LOOP   ; Si presionó cualquier otra cosa, ignorar y volver a esperar

; --- FASE 4: LAS RUTINAS DE FÍSICA (DESTRUCCIÓN Y CREACIÓN) ---
MOVER_DER:
    ; a) Borrar la Cola actual
    MOV WORD PTR [DI], 0020h ; Pintamos un 'Espacio' (20h) con fondo negro (00h)
    ADD DI, 2                ; La Cola virtual avanza a la derecha
    
    ; b) Dibujar la nueva Cabeza
    ADD BX, 2                ; La Cabeza virtual avanza a la derecha
    MOV WORD PTR [BX], 0A0DBh; Pintamos el nuevo bloque verde
    
    JMP GAME_LOOP            ; Volvemos a esperar otra tecla

MOVER_IZQ:
    ; Para retroceder, la física se invierte:
    ; a) Borramos la Cabeza actual (que ahora será el fondo)
    MOV WORD PTR [BX], 0020h 
    SUB BX, 2                ; La Cabeza virtual retrocede a la izquierda
    
    ; b) Dibujamos una nueva Cola (que actuará como la nueva punta izquierda)
    SUB DI, 2                ; La Cola virtual retrocede a la izquierda
    MOV WORD PTR [DI], 0A0DBh
    
    JMP GAME_LOOP

RET
#make_com#
ORG 100h

; --- FASE 1: APUNTAR AL MONITOR ---
MOV AX, 0B800h    ; Dirección base de la VRAM
MOV DS, AX        ; Nuestro segmento de datos ahora es la pantalla

; --- FASE 2: PREPARAR LOS PINCELES Y COORDENADAS ---
MOV BX, 07D0h     ; Offset del centro exacto (Fila 12, Columna 40)
                  ; Utilizamos la fórmula offset = 2(fila*80 + columna)
MOV CX, 8         ; Cargamos el contador con 8 (tamaño de la serpiente)

; ¡TRUCO LITTLE-ENDIAN!
; Queremos guardar el color (0Ah = Verde) y el carácter (2Ah = '*')
; Como la CPU guarda el Byte Bajo primero y el Alto después,
; metemos ambos en AX de un solo golpe:
MOV AX, 0A2Ah     ; AH = 0Ah (Color), AL = 2Ah (Carácter)

; --- FASE 3: EL BUCLE DE DIBUJO ---
DIBUJAR_CUERPO:
    MOV [BX], AX    ; Inyecta los 16 bits en la VRAM (Carácter y Color juntos)
    ADD BX, 2       ; Movemos el puntero 2 bytes a la derecha (siguiente columna)
    LOOP DIBUJAR_CUERPO ; Resta 1 a CX. Si CX no es cero, repite la inyección.

RET               ; Termina el programa
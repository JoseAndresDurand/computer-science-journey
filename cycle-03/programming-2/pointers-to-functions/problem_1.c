/* =============================================================================
 * Problema 1: El Enrutador Aritmético (Nivel Básico)
 * Límite de tiempo: 1.0 segundos
 * Límite de memoria: 256 MB
 *
 * DESCRIPCIÓN:
 * El sistema central de procesamiento de una antigua calculadora ha sufrido un
 * fallo en su módulo de control de flujo. Los ingenieros han prohibido el uso
 * de sentencias condicionales tradicionales por miedo a sobrecargar la pila de
 * ejecución.
 *
 * Se te ha asignado la tarea de construir un "enrutador directo" en la memoria
 * RAM. Recibirás un código de operación y dos operandos. Tu programa debe
 * enrutar directamente la ejecución a la función matemática correspondiente
 * basándose en el código de operación.
 *
 * REQUISITO ARQUITECTÓNICO ESTRICTO:
 * Tienes ABSOLUTAMENTE PROHIBIDO utilizar las palabras reservadas 'if', 'else',
 * 'else if' o el bloque 'switch' para decidir qué operación realizar. Debes
 * resolver el enrutamiento utilizando un arreglo de punteros a funciones
 * (Jump Table).
 *
 * ENTRADA:
 * La entrada consistirá en una única línea que contiene tres números enteros
 * separados por un espacio: op, A y B.
 * - 'op' representa el código de la operación:
 * 0: Suma (A + B)
 * 1: Resta (A - B)
 * 2: Multiplicación (A * B)
 * - 'A' y 'B' son los operandos.
 *
 * SALIDA:
 * Imprime un único número entero que represente el resultado matemático de la
 * operación seleccionada.
 *
 * RESTRICCIONES:
 * - El valor de 'op' siempre será exactamente 0, 1 o 2.
 * - Los valores de 'A' y 'B' estarán en el rango de -1000 a 1000.
 * - El resultado siempre cabrá en un tipo de dato 'int' estándar de C.
 *
 * EJEMPLOS:
 * Entrada 1: 0 15 20   | Salida 1: 35
 * Entrada 2: 1 10 25   | Salida 2: -15
 * Entrada 3: 2 7 8     | Salida 3: 56
 * =============================================================================
 */

#include <stdio.h>

int suma(int a, int b);
int resta(int a, int b);
int multiplicacion(int a, int b);
int division(int a, int b);
int (*operacion[4])(int, int) = {suma, resta, multiplicacion, division};

int main() {
  int op, a, b;

  if (scanf("%d %d %d", &op, &a, &b) == 3) {
    int resultado = operacion[op](a, b);
    printf("%d\n", resultado);
  }

  return 0;
}

int suma(int a, int b) { return a + b; }
int resta(int a, int b) { return a - b; }
int multiplicacion(int a, int b) { return a * b; }
int division(int a, int b) { return a / b; }

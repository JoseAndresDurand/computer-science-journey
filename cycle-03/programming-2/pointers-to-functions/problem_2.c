/* =============================================================================
 * Problema 2: El Inyector de Reglas (Nivel Intermedio)
 * Límite de tiempo: 1.0 segundos
 * Límite de memoria: 256 MB
 *
 * DESCRIPCIÓN:
 * El departamento de análisis de datos necesita ordenar los registros de
 * temperatura del servidor. Sin embargo, dependiendo del informe, a veces
 * necesitan los datos ordenados de menor a mayor (Ascendente) y otras veces
 * de mayor a menor (Descendente).
 *
 * En lugar de escribir dos funciones de ordenamiento gigantes que hagan
 * casi lo mismo, el Arquitecto Jefe te ha pedido escribir una ÚNICA función
 * de ordenamiento. Esta función no debe saber cómo comparar los números;
 * en su lugar, debe recibir un puntero a función (Callback) que le inyecte
 * la regla de comparación matemática en tiempo de ejecución.
 *
 * REQUISITOS ARQUITECTÓNICOS ESTRICTOS:
 * 1. Debes crear una función de ordenamiento (ej. Bubble Sort) con esta firma:
 * void ordenar(int arr[], int n, bool (*comparador)(int, int));
 * (Nota: incluye <stdbool.h> para usar booleanos en C).
 * 2. Debes crear dos funciones auxiliares pequeñas: 'ascendente' y
 * 'descendente' que devuelvan 'true' si es necesario intercambiar los números,
 * y 'false' si están en el orden correcto.
 *
 * ENTRADA:
 * La primera línea contiene dos enteros: 'modo' y 'N'.
 * - 'modo': 0 para ordenar Ascendente, 1 para Descendente.
 * - 'N': La cantidad de números a ordenar (1 <= N <= 100).
 * La segunda línea contiene 'N' números enteros separados por espacios.
 *
 * SALIDA:
 * Imprime el arreglo ordenado en una sola línea, con los números separados
 * por un único espacio.
 *
 * EJEMPLOS:
 * Entrada 1:
 * 0 5
 * 8 3 1 5 9
 * Salida 1:
 * 1 3 5 8 9
 *
 * Entrada 2:
 * 1 4
 * 10 50 20 5
 * Salida 2:
 * 50 20 10 5
 * =============================================================================
 */

#include <stdbool.h>
#include <stdio.h>

bool ascendente(int a, int b);
bool descendente(int a, int b);
void ordenar(int arr[], int n, bool (*comparador)(int, int));

int main() {
  int op, n;
  if (scanf("%d %d", &op, &n) == 2) {
    int arr[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", arr + i);
    }
    if (op == 0) {
      ordenar(arr, n, ascendente);
    } else {
      ordenar(arr, n, descendente);
    }

    for (int i = 0; i < n; i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");
  }

  return 0;
}

bool ascendente(int a, int b) { return a > b; }
bool descendente(int a, int b) { return a < b; }

void ordenar(int arr[], int n, bool (*comparador)(int, int)) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (comparador(arr[j], arr[j + 1])) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

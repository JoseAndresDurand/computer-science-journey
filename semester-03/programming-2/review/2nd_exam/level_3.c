/* =============================================================================
 * Problema 5: El Torneo Galáctico de Drones (Nivel Intermedio ICPC)
 * Límite de tiempo: 1.0 segundos
 * Límite de memoria: 256 MB
 *
 * DESCRIPCIÓN:
 * Se está llevando a cabo el campeonato anual de carreras de drones. Cada
 * participante inscribe su dron, el cual tiene un ID único, una velocidad
 * máxima (entero) y un peso en kilogramos (flotante).
 *
 * El comité organizador necesita publicar la tabla de posiciones finales.
 * El reglamento estipula que los drones deben ordenarse siguiendo estos
 * criterios de prioridad estricta:
 * * 1. Mayor velocidad primero (Descendente).
 * 2. Si dos drones tienen exactamente la misma velocidad, el desempate lo
 * gana el dron más ligero (Menor peso primero - Ascendente).
 * 3. Si tienen la misma velocidad y el mismo peso, gana el dron que
 * tenga el ID numéricamente más pequeño (Ascendente).
 *
 * Debes utilizar el motor `qsort` de la librería estándar para procesar
 * la clasificación.
 *
 * ENTRADA:
 * La primera línea contiene un número entero N (1 <= N <= 100), el número
 * de drones participantes.
 * Las siguientes N líneas contienen los datos de cada dron. Cada línea
 * contiene dos enteros y un flotante separados por espacios en este orden:
 * ID, Velocidad, Peso.
 *
 * SALIDA:
 * Imprime la tabla de posiciones final.
 * Cada línea debe mostrar un dron con el formato exacto:
 * "ID: <id> - Vel: <velocidad> - Peso: <peso>kg"
 * El peso debe imprimirse con 1 solo decimal.
 *
 * EJEMPLOS:
 * Entrada 1:
 * 5
 * 101 150 2.5
 * 102 140 1.8
 * 103 150 2.0
 * 104 150 2.5
 * 105 160 3.0
 * * Salida 1:
 * ID: 105 - Vel: 160 - Peso: 3.0kg
 * ID: 103 - Vel: 150 - Peso: 2.0kg
 * ID: 101 - Vel: 150 - Peso: 2.5kg
 * ID: 104 - Vel: 150 - Peso: 2.5kg
 * ID: 102 - Vel: 140 - Peso: 1.8kg
 * =============================================================================
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  int velocidad;
  float peso;
} Drone;

int comparar_drones(const void *a, const void *b);
void imprimir(Drone *d, int n);

int main() {
  int n;
  scanf("%d", &n);
  Drone competidores[n];
  for (int i = 0; i < n; i++) {
    scanf("%d %d %f", &competidores[i].id, &competidores[i].velocidad,
          &competidores[i].peso);
  }

  qsort(competidores, n, sizeof(Drone), comparar_drones);

  imprimir(competidores, n);
  return 0;
}

int comparar_drones(const void *a, const void *b) {
  // Casting
  const Drone *dronA = (const Drone *)a;
  const Drone *dronB = (const Drone *)b;

  if (dronA->velocidad != dronB->velocidad) {
    return dronB->velocidad - dronA->velocidad;
  }
  if (dronA->peso != dronB->peso) {
    if (dronA->peso < dronB->peso) {
      return -1;
    } else {
      return 1;
    }
  }

  return dronA->id - dronB->id;
}

void imprimir(Drone *d, int n) {
  for (int i = 0; i < n; i++) {
    printf("ID: <%d> - Vel: <%d> - Peso: <%.1f>kg \n", d[i].id, d[i].velocidad,
           d[i].peso);
  }
}

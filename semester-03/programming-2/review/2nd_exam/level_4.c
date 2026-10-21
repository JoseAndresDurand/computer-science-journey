/* =============================================================================
 * Problema 6: Misión Rescate en el Sector K-9 (Nivel Avanzado ICPC)
 * Límite de tiempo: 1.5 segundos
 * Límite de memoria: 256 MB
 *
 * DESCRIPCIÓN:
 * Un escuadrón de naves de rescate debe ser desplegado en el sector K-9.
 * Cada nave tiene una especialidad distinta y un nivel de urgencia asignado.
 *
 * Tienes una base de datos con las naves disponibles. Cada nave se define por:
 * 1. Un Código de Llamada (Callsign): Un número entero único.
 * 2. Un Nivel de Energía: Un valor flotante que indica cuánta energía le queda.
 * 3. Un Código de Especialidad: Un carácter ('M' para Médico, 'C' para Combate,
 * 'R' para Reparación).
 *
 * El Almirante necesita que organices a las naves para el despliegue siguiendo
 * un conjunto de reglas muy peculiares, que dependen del tipo de emergencia.
 * REGLAS DE DESPLIEGUE (Prioridades):
 * El Almirante te dará un código numérico (0 o 1) que indica la situación:
 *
 * Situación 0 (Modo Supervivencia):
 * 1. Mayor nivel de energía primero (Descendente).
 * 2. Si la energía es idéntica, prioridad a las naves Médicas ('M'), luego
 * Reparación ('R'), y al final Combate ('C').
 * 3. Si especialidad y energía empatan, menor Código de Llamada primero
 * (Ascendente).
 *
 * Situación 1 (Modo Asalto):
 * 1. Prioridad absoluta a las naves de Combate ('C'), luego Médicas ('M'),
 * y al final Reparación ('R').
 * 2. Si la especialidad es la misma, menor nivel de energía primero (Ascendente
 * - ¡Los más gastados van al frente como escudo!).
 * 3. Si empatan en especialidad y energía, mayor Código de Llamada primero
 * (Descendente).
 *
 * REQUISITOS ARQUITECTÓNICOS ESTRICTOS:
 * 1. Define el `struct Nave`.
 * 2. Implementa `mi_qsort`, `mi_particion` y `mi_intercambiar_bytes`
 * 3. Crea una "Jump Table" (Arreglo de punteros a funciones) en tu `main` para
 * enrutar la decisión entre `comparar_supervivencia` y `comparar_asalto`
 * basado en el código de situación (0 o 1).
 *
 * ENTRADA:
 * - Primera línea: Dos enteros separados por un espacio. El código de situación
 * (0 o 1) y el número de naves N (1 <= N <= 200).
 * - Siguientes N líneas: Los datos de cada nave (Código, Energía, Especialidad)
 * separados por espacios.
 *
 * SALIDA:
 * - Imprime la lista de naves ordenadas, una por línea, con el formato:
 * "Callsign: <codigo> | Energia: <energia> | Tipo: <especialidad>"
 * (Energía con 2 decimales).
 *
 * EJEMPLOS:
 * Entrada 1:
 * 0 4
 * 101 85.5 M
 * 102 90.0 C
 * 103 85.5 R
 * 104 90.0 M
 *
 * Salida 1:
 * Callsign: 104 | Energia: 90.00 | Tipo: M
 * Callsign: 102 | Energia: 90.00 | Tipo: C
 * Callsign: 101 | Energia: 85.50 | Tipo: M
 * Callsign: 103 | Energia: 85.50 | Tipo: R
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int callsign;
  float energia;
  char tipo;
} Nave;

int supervivencia(const void *x, const void *y);
int asalto(const void *x, const void *y);
void(*situacion[]) = {supervivencia, asalto};
void imprimir(Nave *s, int n);

int main() {
  int sit;
  int n;

  scanf("%d %d", &sit, &n);
  Nave flota[n];

  for (int i = 0; i < n; i++) {
    scanf("%d %f %c", &flota[i].callsign, &flota[i].energia, &flota[i].tipo);
  }

  qsort(flota, n, sizeof(Nave), situacion[sit]);

  imprimir(flota, n);

  return 0;
}

int supervivencia(const void *x, const void *y) {
  // casting
  const Nave *naveA = (const Nave *)x;
  const Nave *naveB = (const Nave *)y;

  if (naveA->energia != naveB->energia) {
    return naveB->energia - naveA->energia;
  }
  if (naveA->tipo != naveB->tipo) {
    if (naveA->tipo == 'M' || (naveA->tipo == 'R' && naveB->tipo != 'M')) {
      return -1;
    }
    return 1;
  }
  return naveA->callsign - naveB->callsign;
}

int asalto(const void *x, const void *y) {
  // casting
  const Nave *naveC = (const Nave *)x;
  const Nave *naveD = (const Nave *)y;
  // C->M->R
  if (naveC->tipo != naveD->tipo) {
    if (naveC->tipo == 'C' || (naveC->tipo == 'M' && naveD->tipo != 'C')) {
      return -1;
    }
    return 1;
  }

  if (naveC->energia != naveD->energia) {
    return naveC->energia - naveD->energia;
  }

  return naveC->callsign - naveD->callsign;
}

void imprimir(Nave *s, int n) {
  for (int i = 0; i < n; i++) {
    printf("Callsign: %d | Energia: %.1f | Tipo: %c \n", s[i].callsign,
           s[i].energia, s[i].tipo);
  }
}

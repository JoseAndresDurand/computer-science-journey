/* =============================================================================
 * Problema 4: Inyección de Datos en Estructuras (Nivel Básico)
 * Límite de tiempo: 1.0 segundos
 *
 * DESCRIPCIÓN:
 * Debes definir una estructura 'Sensor' usando typedef.
 * Luego, construirás una función que reciba la dirección de memoria de un
 * Sensor (puntero) y modifique sus valores directamente en la RAM. Finalmente,
 * otra función imprimirá esos valores.
 *
 * REQUISITOS ARQUITECTÓNICOS ESTRICTOS:
 * 1. Define una estructura 'Sensor' con: un 'id' (int), y un 'valor' (float).
 * 2. Crea la función: void inyectar(Sensor *s, int nuevo_id, float
 * nuevo_valor); (Usa el operador flecha '->' para modificar la memoria).
 * 3. Crea la función: void imprimir(const Sensor *s);
 * (Nota: Usamos 'const' aquí porque imprimir no debería modificar los datos.
 * Es una promesa de solo lectura).
 *
 * ENTRADA:
 * Dos números: un entero (id) y un flotante (valor), separados por espacio.
 *
 * SALIDA:
 * Imprime el formato exacto: "Sensor ID: <id> | Valor: <valor>"
 * (Muestra el flotante con 2 decimales).
 *
 * EJEMPLO:
 * Entrada: 404 15.75
 * Salida:  Sensor ID: 404 | Valor: 15.75
 * =============================================================================
 */

#include <stdio.h>

// 1. Define tu typedef struct aquí...
typedef struct {
  int id;
  float valor;
} Sensor;
// 2. Escribe los prototipos de inyectar e imprimir aquí...
void inyectar(Sensor *s, int nuevo_id, float nuevo_valor);
void imprimir(const Sensor *s);

int main() {
  int id;
  float valor;
  // 3. Instancia tu Sensor (ej. Sensor mi_sensor;)
  Sensor mi_sensor;
  // 4. Captura la entrada con scanf
  scanf("%d %f", &id, &valor);
  // 5. Llama a inyectar() pasándole la dirección de memoria (&mi_sensor)
  inyectar(&mi_sensor, id, valor);
  // 6. Llama a imprimir()
  imprimir(&mi_sensor);

  return 0;
}

// 7. Desarrolla las funciones aquí abajo usando el operador flecha (->)
void inyectar(Sensor *s, int nuevo_id, float nuevo_valor) {
  s->id = nuevo_id;
  s->valor = nuevo_valor;
}
void imprimir(const Sensor *s) {
  printf("Sensor ID: %d | Valor: %0.2f \n", s->id, s->valor);
}

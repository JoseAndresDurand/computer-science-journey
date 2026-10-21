#include <stdio.h>

typedef struct {
  int id;
  float bateria;
} Drone;

void recargar(Drone *d);

int main() {
  Drone flota[3];
  for (int i = 0; i < 3; i++) {
    scanf("%d", &flota[i].id);
  }
  for (int i = 0; i < 3; i++) {
    recargar(&flota[i]);
  }

  // imprimir:
  for (int i = 0; i < 3; i++) {
    printf("Drone %d - Bateria : %0.0f %%\n", flota[i].id, flota[i].bateria);
  }
  return 0;
}

void recargar(Drone *d) { d->bateria = 100; }

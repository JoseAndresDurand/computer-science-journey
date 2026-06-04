#include <stdio.h>

void imprimir(int arr[], int m);
void msb_sort(int arr[], int mascara, int min_index, int max_index);
int mascara_optimizada(int arr[], int m);

int main() {
  int arr[] = {342, 12, 501, 89, 256, 7, 410, 198, 45, 315, 62, 480};
  int m = 12; // numero de elementos a ordenar
  int mascara =
      mascara_optimizada(arr, m); // máscara calculada. Si es 8 = 0b1000
  int min_index = 0;              // indice inicial
  int max_index = m - 1;          // indice final

  printf("%s\n", "Array original:");
  imprimir(arr, m);
  printf("\n");

  msb_sort(arr, mascara, min_index, max_index);
  printf("%s\n", "Array con msb_sort_recursivo:");
  imprimir(arr, m);

  return 0;
}

int mascara_optimizada(int arr[], int m) {
  int mayor = arr[0];
  for (int i = 0; i < m; i++) {
    if (mayor < arr[i]) {
      mayor = arr[i];
    }
  }
  int mascara_optimizada = 1;
  while (mascara_optimizada <= mayor) {
    mascara_optimizada = mascara_optimizada << 1;
  }
  mascara_optimizada =
      mascara_optimizada >>
      1; // retrocedemos una posición porque en el anterior se pasó una.
  return mascara_optimizada;
}

void msb_sort(int arr[], int mascara, int min_index, int max_index) {
  int min = min_index;
  int max = max_index;
  if (mascara == 0 || min >= max)
    return;

  while (min <= max) {
    while (min <= max && ((arr[min] & mascara) == 0)) {
      min++;
    }
    while (min <= max && ((arr[max] & mascara) == mascara)) {
      max--;
    }
    if (min <= max) {
      int temp = arr[min];
      arr[min] = arr[max];
      arr[max] = temp;
      max--;
      min++;
    }
  }
  msb_sort(arr, mascara / 2, min_index, max);
  msb_sort(arr, mascara / 2, min, max_index);
}

void imprimir(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

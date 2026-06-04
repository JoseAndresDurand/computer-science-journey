#include <stdio.h>

void imprimir(int arr[], int m);
void msb_sort_recursivo(int arr[], int mascara, int min_index, int max_index);

int main() {
  int arr[] = {15, 9, 7, 1, 13, 11, 1, 0, 2};
  int m = 9;       // numero de elementos a ordenar
  int n = 4;       // numero de bits por numero
  int mascara = 8; // 0b1000
  int min_index = 0;
  int max_index = m - 1; // indice final

  printf("%s\n", "Array original:");
  imprimir(arr, m);
  printf("\n");

  msb_sort_recursivo(arr, mascara, min_index, max_index);
  printf("%s\n", "Array con msb_sort_recursivo:");
  imprimir(arr, m);

  return 0;
}

void msb_sort_recursivo(int arr[], int mascara, int min_index, int max_index) {
  int min = min_index;
  int max = max_index - 1;
  if (mascara == 0)
    return;

  while (min < max) {
    while (min < max && ((arr[min] & mascara) == 0)) {
      min++;
    }
    while (min < max && ((arr[max] & mascara) == mascara)) {
      max--;
    }
    if (min < max) {
      int temp = arr[min];
      arr[min] = arr[max];
      arr[max] = temp;
      max--;
      min++;
    }
  }
  msb_sort_recursivo(arr, mascara / 2, 0, max_index / 2);
  msb_sort_recursivo(arr, mascara / 2, max_index / 2, max_index);
}

void msb_sort(int m, int n, int arr[]) {
  int mascara = 8;
  int min = 0;
  int max = m - 1;
  while (min < max) {
    while (min < max && ((arr[min] & mascara) == 0)) {
      min++;
    }
    while (min < max && ((arr[max] & mascara) == mascara)) {
      max--;
    }
    if (min < max) {
      int temp = arr[min];
      arr[min] = arr[max];
      arr[max] = temp;
      max--;
      min++;
    }
  }
}

void imprimir(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

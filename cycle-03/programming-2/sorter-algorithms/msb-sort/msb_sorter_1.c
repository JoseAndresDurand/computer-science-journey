#include <stdio.h>

void imprimir(int arr[], int n);
void msb_sort(int m, int n, int arr[]);

int main() {
  int arr[] = {9, 7, 1, 13, 11};
  int m = 5; // numero de elementos a ordenar
  int n = 4; // numero de bit
  int matrix[m][n];

  printf("%s\n", "Array original:");
  imprimir(arr, m);
  printf("\n");

  msb_sort(m, n, arr);
  printf("%s\n", "Array con msb_sort:");
  imprimir(arr, m);

  return 0;
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

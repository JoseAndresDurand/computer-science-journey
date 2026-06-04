#include <stdio.h>

void numero_a_bits(int m, int n, int arr[], int matrix[][n]);
void imprimir(int arr[], int n);
void imprimir_matrix(int m, int n, int arr[][n]);
void msb_sort_1(int m, int n, int arr[]);

int main() {
  int arr[] = {9, 7, 1, 13, 11};
  int m = 5; // numero de elementos a ordenar
  int n = 4; // numero de bit
  int matrix[m][n];

  numero_a_bits(m, n, arr, matrix);

  printf("%s\n", "Array original:");
  imprimir(arr, m);
  printf("\n");
  printf("%s\n", "Matrix original:");
  imprimir_matrix(m, n, matrix);
  printf("\n");

  msb_sort_1(m, n, arr);
  printf("%s\n", "Array con msb_sort:");
  imprimir(arr, n);

  return 0;
}

void msb_sort_1(int m, int n, int arr[]) {
  int mascara = 8;
  int min = 0;
  int max = m - 1;
  while (min > max) {
    if (((arr[min] & mascara) == 8) ^ ((arr[max] & mascara) == 8)) {
      int temp = arr[min];
      arr[min] = arr[max];
      arr[max] = temp;
      min++;
      max--;
    }
    if (((arr[min] & mascara) == 8) && ((arr[max] & mascara) == 8)) {
      min++;
    }
  }
}

void numero_a_bits(int m, int n, int arr[], int matrix[][n]) {
  int mascara = 1;
  for (int i = 0; i < m; i++) {
    int numero = arr[i];
    for (int j = n; j > 0; j--) {
      matrix[i][j - 1] = numero & mascara;
      numero = numero >> 1;
    }
  }
}

void imprimir(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void imprimir_matrix(int m, int n, int arr[][n]) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

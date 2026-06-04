#include <stdio.h>

void numero_a_bits(int arr[], int matrix[], int n);
void imprimir(int arr[], int n);

int main() {
  int arr[] = {5};
  int n = 4;
  int matrix[n];

  numero_a_bits(arr, matrix, n);

  imprimir(arr, 1);
  imprimir(matrix, n);

  return 0;
}

void numero_a_bits(int arr[], int matrix[], int n) {
  int numero = arr[0];
  int mascara = 1;
  for (int i = n; i > 0; i--) {
    matrix[i - 1] = numero & mascara;
    numero = numero >> 1;
  }
}

void imprimir(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

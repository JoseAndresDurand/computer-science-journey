/*
6. Escriba un programa que a través de punteros a funciones halle la suma
de los elementos de la fila x y el producto de la columna de una matriz 
dinámica de enteros.
*/

#include <iostream>
using namespace std;


int resultado(int(*func)(int**, int, int, int), int **matriz, int fila, int columna, int p)
{
   return (*func)(matriz, fila, columna,p);
}
int sumaFila(int **matriz, int fila, int columna, int x)
{  
    int sum=0;
    for (int i=0;i<fila;i++){
        sum += matriz[x-1][i];
    }
    return sum;
}
int productoColumna(int **matriz, int fila, int columna, int y)
{
    int producto=1;
    for (int i=0;i<fila;i++){
        producto *= matriz[i][y-1];
    }
    return producto;
}


void ingresarValores(int **matriz, int fila, int columna){
   for (int i=0;i<fila;i++){
        for (int j=0;j<columna;j++){
            matriz[i][j] = i*1 + j;
        }
   }
}

void imprimirMatriz(int **matriz, int fila, int columna){
   for (int i=0;i<fila;i++){
        for (int j=0;j<columna;j++){
            cout<<matriz[i][j]<<"\t";
        }
        cout<<endl;
   }
}


int main()
{
   int fila = 10;
   int columna = 10;
   int x,y;
   int **matriz;
   matriz = new int*[fila];
   for (int i=0; i<fila;i++){
    matriz[i] = new int[columna];
   }
   ingresarValores(matriz, fila, columna);
   imprimirMatriz(matriz, fila, columna);
   cout<<"Qué número de fila (1 al 10) desea se sumen los valores? ";
   cin>>x;
   cout<<"Suma de los valores de la fila: "<<x<<endl;
   cout<<resultado(sumaFila,matriz,fila,columna,x)<<endl;
   cout<<"Qué número de columna (1 al 10) desea se multipliquen los valores? ";
   cin>>y;
   cout<<"Producto de los valores de la columna: "<<y<<endl;
   cout<<resultado(productoColumna,matriz,fila,columna,y)<<endl;
   
   for (int k=0; k<fila;k++){
    delete[] matriz[k];
   }
   delete[] matriz;

   return 0;
}

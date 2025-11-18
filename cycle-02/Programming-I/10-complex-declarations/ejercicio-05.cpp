/*
5. Escriba un programa que a través de punteros a funciones halle la suma de los
elementos de las posiciones pares y el producto de los elementos de las posiciones 
impares de un vector dinámicode enteros.
*/

#include <iostream>
using namespace std;


int resultado(int(*func)(int*, int), int *vector, int n)
{
   return (*func)(vector,n);
}
int pares(int *vector, int n)
{  
   int sum=0;
   for (int i=0;i<n;i++){
       if(i%2!=0){
           sum+= *(vector+i);
       }
   }
   return sum;
}
int impares(int *vector, int n)
{
   int producto=1;
   for (int i=0;i<n;i++){
       if(i%2 == 0){
           producto*= *(vector+i);
       }
   }
   return producto;
}


void ingresar(int *vector, int n){
   cout<<"Ingresar valores en el vector"<<endl;
   for (int i=0;i<n;i++){
       cin>>*(vector+i);
   }
}


int main()
{
   int n = 10;
   int *vector = new int[n];
   ingresar(vector, n);
   cout<<"Suma de posiciones pares ";
   cout<<resultado(pares,vector,n)<<endl;
   cout<<"Producto de posiciones impares ";
   cout<<resultado(impares,vector,n)<<endl;
   delete[] vector;
   return 0;
}

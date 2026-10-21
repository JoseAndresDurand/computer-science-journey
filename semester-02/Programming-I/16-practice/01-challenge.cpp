#include <iostream>
using namespace std;

// 1. Definimos dos funciones normales
int sumar(int a, int b) { return a+b;}
int restar(int a, int b){ return a-b;}

int main() {
    // RETO 1: Declara un puntero a función llamado 'operacion'
    // que pueda apuntar a 'sumar' o 'restar'.
    // Sintaxis: int (*nombre)(int, int);
    
    // TU CÓDIGO AQUÍ (Declara e inicialízalo apuntando a 'sumar')
    // ---------------------------------------------------------
    int (*operacion)(int, int) = sumar;
    cout<<"Suma 10 + 5 ="<<operacion(10,5)<<endl;
    // Prueba llamándolo:
    // cout << "Suma 10 + 5 = " << operacion(10, 5) << endl;


    // RETO 2 (Nivel Práctica 10): Array de Punteros
    // Declara un array llamado 'menu' de 2 posiciones.
    // menu[0] debe ser sumar.
    // menu[1] debe ser restar.
    
    // TU CÓDIGO AQUÍ
    // ---------------------------------------------------------
    int (*menu[2])(int, int);
    menu[0] = sumar;
    menu[1] = restar;

    // Prueba usándolo con índices:
    cout << "Usando Array posicion 0 (Suma 20+10): " << menu[0](20, 10) << endl;
    cout << "Usando Array posicion 1 (Resta 20-10): " << menu[1](20, 10) << endl;

    return 0;
}
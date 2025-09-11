/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-06.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Encontrar el menor numero de 3 numeros dados.
 * @problem Encontrar cuál de tres valores leídos (A, B, C) por la computadora, es el menor.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Tres numeros enteros.
 *
 * ### Outputs:
 * - Un numero entero.
 *
 * ### Key Variables:
 * - num1, num2, num3 (int): numero de entrada.
 * - menor (int): número menor.
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables num1, num2, num3, menor.
 * 3.  Mostrar mensaje "Ingrese tres numeros :"
 * 4.  Leer y almacenar el valor en num1, num2, num3.
 * 5.  Asignar el valor de num1 a la variable menor.
 * 6.  SI (num1 < num2 and num1<num3) ENTONCES
 * 7.       menor = num1
 * 8.  SINO SI (num2 < num1 and num2<num3) ENTONCES
 * 9.       menor = num2 
 * 10. SINO SI (num3 < num2 and num3<num1) ENTONCES
 * 11.      menor = num3
 * 12. SINO
 * 13.      Mostrar mensaje los 3 numeros son iguales 
 * 15. FIN SI
 *
 * ### Edge Cases & Limits:
 * Igualdad (Crítico): Este es el principal caso a considerar.
 * Dos números son iguales y son el mínimo (ej. 8, 3, 3). El programa debe identificar 3 como el menor.
 * Todos los números son iguales (ej. 7, 7, 7). El programa debe identificar 7 como el menor.
 * Números negativos: La lógica de comparación debe funcionar correctamente cuando uno o más de los números son negativos.
 * Inclusión del cero: El programa debe manejar sin problemas las comparaciones que incluyen el cero.
 * Entrada no numérica: Como en los problemas anteriores, asumimos que el usuario ingresa números válidos.
 *
 * ### Test Plan:
 * A es el menor: input: 3, 8, 5 -> output: El menor es 3
 * B es el menor: input: 9, 2, 4 -> output: El menor es 2
 * C es el menor: input: 6, 10, 1 -> output: El menor es 1
 * Dos mínimos iguales: input: 8, 3, 3 -> output: El menor es 3
 * Todos iguales: input: 7, 7, 7 -> output: El menor es 7
 * Con negativos: input: -10, 5, -5 -> output: El menor es -10
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    int num1;
    float calculo;
    cout<<"Ingresa un numero : "<<endl;
    cin>>num1;

    if (num1 % 5 == 0){
        calculo = pow(num1,3);
        cout<<"El numero "<<num1<<" al cubo es "<<calculo<<endl;
    }else if ( abs(num1) % 10 == 7){
        if (num1 >= 0){
            calculo = sqrt(num1);
            cout<<"La raiz cuadrada de "<<num1<<" es "<<calculo<<endl;
        }else{
            cout<<"[Error] El numero "<<num1<<" termina en 7 pero es menor a 0 "<<endl;
        }            
    }else{
            cout<<"El numero "<<num1<<" no es divisible por 5 ni termina en 7"<<endl;
    }
    return 0;
 }
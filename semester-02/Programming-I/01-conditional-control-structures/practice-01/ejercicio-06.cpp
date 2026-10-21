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
 * 5.  SI (num1 <= num2 and num1 <= num3) ENTONCES
 * 6.       menor = num1
 * 7.  SINO SI (num2 <= num1 and num2 <= num3) ENTONCES
 * 8.       menor = num2 
 * 9. SINO SI (num3 <= num2 and num3 <= num1) ENTONCES
 * 10.      menor = num3
 * 11. FIN SI
 *
 * ### Edge Cases & Limits:
 * Igualdad: Este es el principal caso a considerar.
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
    int num1, num2, num3, menor;
    cout<<"Ingresar 3 numeros : "<<endl;
    cin>>num1>>num2>>num3;

    if (num1 <= num2 && num1 <= num3){
        menor = num1;
    }else if (num2 <= num1 && num2 <= num3){
        menor = num2;
    }else if (num3 <= num2 && num3 <= num1){
        menor = num3;
    }
    cout<<"El menor es "<<menor<<endl;

    return 0;
 }
/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-05.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Modificar un número si es divisible entre 5 o si termina en 7.
 * @problem Ingresar un número entero y si el número es divisible entre 5 cambiar su valor
 *          por el mismo elevado al cubo y si el número termina en 7 cambiar su valor por su raíz cuadrada.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Un número entero.
 *
 * ### Outputs:
 * - Un número decimal como resultado de identificar si el input es divisible entre 5 o termina en 7
 *
 * ### Key Variables:
 * - num1 (int): numero de entrada.
 * - calculo (float): resultado de operación (num1^3 o sqrt(num1))
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar la variable float num1
 * 3.  Mostrar mensaje "Ingrese un numero :"
 * 4.  Leer y almacenar el valor en num1
 * 5.  SI (num1 % 5 = 0) ENTONCES
 * 6.       calculo = pow(num1,3)
 * 7.       Mostrar resultado de calculo
 * 8.  SINO
 * 9.       SI (num1 % 10 = 7) ENTONCES
 * 10.          SI (num1 >= 0)ENTONCES
 * 11.              calculo = sqrt(num1)
 * 12.              Mostrar resultado de calculo
 * 13.          SINO
 * 14.              El valor termina en 7 pero es menor a 0
 * 14.      SINO
 * 15.          El número no es divisible por 5 ni termina en 7
 * 16.      FIN SI
 * 15. FIN SI
 *
 * ### Edge Cases & Limits:
 * Condición "divisible por 5": La lógica debe funcionar para números positivos (10), negativos (-5) y, muy importante, para el cero (0), que es divisible por 5.
 * Condición "termina en 7": El programa intentará calcular una raíz cuadrada. Es necesario verificar que el número no sea negativo antes de llamar a la función sqrt().
 * Ninguna condición: El programa debe manejar correctamente los casos en que el número no cumple ninguna condición (ej. 13), dejando el valor original sin cambios.
 *
 * ### Test Plan:
 * Divisible por 5 (Positivo): input: 10 -> output: 1000
 * Divisible por 5 (Cero): input: 0 -> output: 0
 * Divisible por 5 (Negativo): input: -5 -> output: -125
 * Termina en 7 (Positivo): input: 27 -> output: 5.196...
 * Termina en 7 (Negativo - Error): input: -7 -> output: Error (no se puede calcular la raíz de un negativo)
 * Ninguna condición: input: 13 -> output: 13 (valor no cambia)
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
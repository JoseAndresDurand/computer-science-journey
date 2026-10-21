/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-04.cpp
 * @author  José Andrés
 * @date    2025-09-09
 * @brief   Realizar las 4 operaciones con 2 números.
 * @problem Hallar la suma, resta, multiplicación y división de dos números.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Dos números decimales 
 *
 * ### Outputs:
 * - Cuatro resultados correspondiente a la suma, resta, multiplicación y división 
 *   de los 2 números ingresados.
 *
 * ### Key Variables:
 * - num1 (float): numero de entrada.
 * - num2 (float): numero de entrada.
 * - suma (float): suma de num1 + num2.
 * - resta (float): resta de num1 - num2.
 * - multiplicacion (float): producto de num1 * num2.
 * - división (float): división de num1 / num2.
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables float num1, num2.
 * 3.  Mostrar mensaje "Ingrese dos numeros :".
 * 4.  Leer y almacenar el valor en num1, y num2.
 * 5.  Calcular suma = num1 + num2.
 * 6.  Calcular resta = num1 - num2.
 * 7.  Calcular multiplicacion = num1 * num2.
 * 8.  Mostrar resultado de suma, resta y multiplicacion
 * 8.  SI (num2 es diferente de 0) ENTONCES
 * 9.       Calcular division = num1 / num2.
 * 10.      Mostar resultado de division
 * 10. SINO
 * 11.      Mostrar mensaje de error de división indeterminada
 * 12. FIN SI
 *
 * ### Edge Cases & Limits:
 * División por cero: El denominador (num2) no puede ser cero. 
 * Operaciones con cero: Ej. 0 / 5 es un caso válido y su resultado es 0.
 * Números negativos: Las cuatro operaciones deben funcionar correctamente si uno o ambos números son negativos.
 * Entrada no numérica: Asumimos que el usuario ingresa números válidos.
 *
 * ### Test Plan:
 * Normal: input: 10, 2 -> output: Suma: 12, Resta: 8, Mult: 20, Div: 5
 * División por Cero: input: 5, 0 -> output: Suma: 5, Resta: 5, Mult: 0, Div: Error
 * Cero Numerador: input: 0, 7 -> output: Suma: 7, Resta: -7, Mult: 0, Div: 0
 * Negativos: input: -8, -2 -> output: Suma: -10, Resta: -6, Mult: 16, Div: 4
 * Decimales: input: 7.5, 2.5 -> output: Suma: 10.0, Resta: 5.0, Mult: 18.75, Div: 3.0
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    float num1, num2, suma, resta, multiplicacion, division;

    cout<<"Ingrese dos numeros: "<<endl;
    cin>>num1>>num2;
    suma = num1 + num2;
    resta = num1 - num2;
    multiplicacion = num1 * num2;
    cout<<"La suma de "<<num1<<" y "<<num2<<" es: "<<suma<<endl;
    cout<<"La resta de "<<num1<<" y "<<num2<<" es: "<<resta<<endl;
    cout<<"La multiplicacion de "<<num1<<" y "<<num2<<" es: "<<multiplicacion<<endl;
    if (num2 != 0){
        division = num1 / num2;
        cout<<"La division de "<<num1<<" y "<<num2<<" es: "<<division<<endl;
    }else{
        cout<<"[Error] La division de "<<num1<<" y "<<num2<<" es no definida "<<endl;
    }
    return 0;
 }
/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-03.cpp
 * @author  José
 * @date    2025-09-09
 * @brief   Convertir temperaturas de grados Centígrados a Fahrenheit
 * @problem Una temperatura en ºC se puede convertir a su equivalente Fahrenheit (ºF)
 *          con la fórmula: F = 9/5 C + 32. Hacer un programa que lea una temperatura 
 *          en grados Centígrados y obtenga e imprima la temperatura Fahrenheit equivalente.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Un número con decimales para grados centígrados.
 *
 * ### Outputs:
 * - La temperatura en grados Fahrenheit.
 *
 * ### Key Variables:
 * - c (float): Valor de entrada.
 * - f (float): Valor de salida.
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables flotantes c,f.
 * 3.  Mostrar mensaje "Ingrese temperatura en grados Centígrados:".
 * 4.  Leer y almacenar el valor en 'c'.
 * 5.  SI (c >= -273.15) ENTONCES
 * 6.       Calcular la temperatura en grados Fahrenheit a partir de grados Centígrados:
 * 7.       f = 9/5*c + 32.
 * 8.  Mostrar la temperatura en grados Fharenheit.
 * 9.  SINO
 * 10.      Mostrar mensaje de limite físico de temperatura
 * 11. FIN
 *
 * ### Edge Cases & Limits:
 * Punto de congelación del agua (0°C): Un punto de referencia estándar.
 * Punto de ebullición del agua (100°C): Otro punto de referencia clave.
 * Temperaturas negativas: La fórmula debe funcionar igual con valores bajo cero.
 * Cruce de escalas (-40°C): El único punto donde Celsius y Fahrenheit son iguales.
 * Cero absoluto (-273.15°C): El límite físico de la temperatura.
 * Entrada no numérica: Se asume que el usuario ingresa un número válido.
 *
 * ### Test Plan:
 * Congelación: input: 0 -> output: 32
 * Corporal aprox: input: 37 -> output: 98.6
 * Ebullición: input: 100 -> output: 212
 * Negativo: input: -10 -> output: 14
 * Cruce: input: -40 -> output: -40
 * Límite físico: input: -273.15 -> output: -459.67
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    float celsius,fahrenheit;
    const float CERO_ABSOLUTO_C = -273.15;

    cout<<"Ingrese temperatura en grados Centígrados (c°): "<<endl;
    cin>>celsius;
    if (celsius >= CERO_ABSOLUTO_C){
        fahrenheit = (9.0/5.0)*celsius + 32;
        cout<<"La temperatura en grados Fahrenheit es: "<<fahrenheit<<endl;
    }else{
        cout<<"El cero absoluto (límite físico) es "<<CERO_ABSOLUTO_C<<endl;
    }
    return 0;
 }
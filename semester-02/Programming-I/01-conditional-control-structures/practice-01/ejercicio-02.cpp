/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-02.cpp
 * @author  José Andrés
 * @date    2025-09-09
 * @brief   Hallar la media aritmética y media geométrica de tres números.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Tres números con decimales (num1, num2, num3).
 *
 * ### Outputs:
 * - La media aritmética calculada.
 * - La media geométrica calculada (o un mensaje de error).
 *
 * ### Key Variables:
 * - num1, num2, num3 (float): Números de entrada.
 * - mediaAritmetica (float): Resultado de la media aritmética.
 * - mediaGeometrica (float): Resultado de la media geométrica.
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables flotantes num1, num2, num3, mediaAritmetica, mediaGeometrica.
 * 3.  Mostrar mensaje "Ingrese el primer número:".
 * 4.  Leer y almacenar el valor en 'num1'.
 * 5.  Mostrar mensaje "Ingrese el segundo número:".
 * 6.  Leer y almacenar el valor en 'num2'.
 * 7.  Mostrar mensaje "Ingrese el tercer número".
 * 8.  Leer y almacenar el valor 'num3'.
 * 9.  Calcular la media aritmética: mediaAritmetica = (num1 + num2 + num3) / 3.0.
 * 10.  Mostrar la media aritmética.
 * 11.  Verificar si el producto de num1, num2y num3 es no negativo.
 * 12.    SI (num1 * num2 * num 3 >= 0) ENTONCES
 * 13.       Calcular la media geométrica: mediaGeometrica = raiz_cuadrada(num1 * num2 * num3).
 * 14.       Mostrar media geométrica
 * 15.   SINO
 * 16.       Mostrar mensaje de error para la media geométrica.
 * 17.   FIN SI
 * 18. FIN
 *
 * ### Edge Cases & Limits:
 * - **Producto Negativo:** Se debe validar que el producto no sea negativo para la media geométrica.
 * - **Al menos un Cero:** Si un número es cero, la media geométrica será 0 (caso válido).
 * - **Entrada no numérica:** Se asume que el usuario ingresa números válidos.
 *
 * ### Test Plan:
 * 1. **Normal:** input: 1, 8, 27   -> output: Aritmética: 12.0, Geométrica: 6.0
 * 2. **Decimales:** input: 2.5, 5, 10 -> output: Aritmética: 5.83, Geométrica: 5.0
 * 3. **Con Cero:** input: 15, 9, 0    -> output: Aritmética: 8.0, Geométrica: 0.0
 * 4. **Error:** input: -2, 4, 5    -> output: Aritmética: 2.33, Error en media geométrica.
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    float num1,num2,num3;

    cout<<"Ingrese tres numeros"<<endl;
    cin>>num1>>num2>>num3;
    
    float mediaAritmetica = (num1+num2+num3)/3.0;
    cout<<"La media aritmética de "<<num1<<", "<<num2<<" y "<<num3<<" es "<<mediaAritmetica<<endl;
    
    if (num1*num2*num3>=0){
        float mediaGeometrica = sqrt(num1*num2*num3);
        cout<<"La media geométrica de "<<num1<<", "<<num2<<" y "<<num3<<" es "<<mediaGeometrica<<endl;
    }else{
        cout<<"La media geométrica no es válida, el producto debe ser mayor o igual a 0";
    }        
    return 0;
 }
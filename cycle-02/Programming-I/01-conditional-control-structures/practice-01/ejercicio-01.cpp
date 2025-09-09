/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-01.cpp
 * @author  José
 * @date    2025-09-08
 * @brief   Calcula la media aritmética y geométrica de dos números.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Un primer número con decimales, 'num1'.
 * - Un segundo número con decimales, 'num2'.
 *
 * ### Outputs:
 * - Un mensaje en consola mostrando la media aritmética calculada.
 * - Un mensaje en consola mostrando la media geométrica calculada.
 *
 * ### Key Variables:
 * - `float num1, num2`: Almacenan los dos números ingresados por el usuario.
 * - `float mediaAritmetica`: Almacena el resultado de (num1 + num2) / 2.
 * - `float mediaGeometrica`: Almacena el resultado de la raíz cuadrada de (num1 * num2).
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables flotantes num1, num2, mediaAritmetica, mediaGeometrica.
 * 3.  Mostrar mensaje "Ingrese el primer número:".
 * 4.  Leer y almacenar el valor en 'num1'.
 * 5.  Mostrar mensaje "Ingrese el segundo número:".
 * 6.  Leer y almacenar el valor en 'num2'.
 * 7.  Calcular la media aritmética: mediaAritmetica = (num1 + num2) / 2.0.
 * 8.  Verificar si el producto de num1 y num2 es no negativo.
 * 9.    SI (num1 * num2 >= 0) ENTONCES
 * 10.       Calcular la media geométrica: mediaGeometrica = raiz_cuadrada(num1 * num2).
 * 11.       Mostrar ambos resultados.
 * 12.   SINO
 * 13.       Mostrar la media aritmética y un mensaje de error para la geométrica.
 * 14.   FIN SI
 * 15. FIN
 *
 * ### Edge Cases & Limits:
 * - **Producto Negativo:** La media geométrica no está definida en los números reales si el producto de los números es negativo (ej. -4 y 4). El programa debe manejar este caso.
 * - **Cero:** Si uno o ambos números son cero, la media geométrica es 0. Es un caso válido.
 * - **Entrada no numérica:** Si el usuario ingresa texto, el programa podría fallar. (Por ahora, asumimos entradas válidas).
 *
 * ### Test Plan:
 * 1.  **Test Case 1 (Normal):**
 * - Input: 4, 9
 * - Expected Output: Media Aritmética: 6.5, Media Geométrica: 6.0
 * 2.  **Test Case 2 (Decimales):**
 * - Input: 2.5, 10
 * - Expected Output: Media Aritmética: 6.25, Media Geométrica: 5.0
 * 3.  **Test Case 3 (Error - Producto Negativo):**
 * - Input: -4, 4
 * - Expected Output: Media Aritmética: 0, Mensaje de error para la media geométrica.
 *
 ******************************************************************************/

 #include <iostream>
 
 int main()
 {
    float num1,num1,mediaAritmetica,mediaGeometrica;

    std::cout<<"Ingrese el primer número"<<std::endl;
    std::cin>>num1;
    std::cout<<"Ingrese el segundo número"<<std::endl;
    std::cin>>num2;



    return 0;


 }
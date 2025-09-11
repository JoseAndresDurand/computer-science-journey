/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-07.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Realizar un menu con 6 tipos de opciones.
 * @problem Considere que está desarrollando una web donde trabaja con tipos de motor 
 *          (suponemos que se trata del tipo de motor de una bomba para mover fluidos). 
 *          Los valores posibles son 1, 2, 3, 4.
 *          a) Si el tipo de motor es 0, mostrar un mensaje indicando “No hay establecido un valor definido para el tipo de bomba”.
 *          b) Si el tipo de motor es 1, mostrar un mensaje indicando “La bomba es una bomba de agua”.
 *          c) Si el tipo de motor es 2, mostrar un mensaje indicando “La bomba es una bomba de gasolina”.
 *          d) Si el tipo de motor es 3, mostrar un mensaje indicando “La bomba es una bomba de hormigón”.
 *          e) Si el tipo de motor es 4, mostrar un mensaje indicando “La bomba es una bomba de pasta alimenticia”.
 *          f) Si no se cumple ninguno de los valores anteriores mostrar el mensaje “No existe un valor válido para tipo de bomba”.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Un tipo de numero entero.
 *
 * ### Outputs:
 * - Un mensaje de acuerdo al tipo de opción del menú.
 *
 * ### Key Variables:
 * - menu (int): numero de opcion.
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar la variable menu.
 * 3.  Mostrar mensaje "Ingrese la opción de motor que desea consultar :"
 * 4.  Leer y almacenar el valor en la variable menu.
 * 6.  SWITCH (menu):
 * 7.        CASO 0:
 * 8.        Mostrar mensaje: No hay establecido un valor definido para el tipo de bomba
 * 9.        CASO 1:
 * 10.       Mostrar mensaje: La bomba es una bomba de agua
 * 11.       CASO 2:
 * 12.       Mostrar mensaje: La bomba es una bomba de gasolina
 * 13.       CASO 3:
 * 14.       Mostrar mensaje: La bomba es una bomba de hormigón
 * 15.       CASO 4:
 * 16.       Mostrar mensaje: La bomba es una bomba de pasta alimenticia
 * 17.       DEFAULT:
 * 18.       Mostrar mensaje: [Error] No existe un valor válido para tipo de bomba
 *
 * ### Edge Cases & Limits:
 * Valores definidos (0, 1, 2, 3, 4): El programa debe manejar correctamente cada uno de los casos explícitamente mencionados en el problema.
 * Valores fuera de rango (Crítico): Este es el principal "edge case". El programa debe ser capaz de identificar cualquier número que no esté
 * en el conjunto {0, 1, 2, 3, 4} y mostrar el mensaje por defecto. Esto incluye números positivos mayores que 4 (como 5 o 100) y números negativos (como -1).
 * Entrada no numérica: Como en los problemas anteriores, asumimos que el usuario ingresa números válidos.
 *
 * ### Test Plan:
 * Caso 0: input: 0 -> output: "No hay establecido un valor definido para el tipo de bomba." 
 * Caso 1: input: 1 -> output: "La bomba es una bomba de agua." 
 * Caso 2: input: 2 -> output: "La bomba es una bomba de gasolina." 
 * Caso 3: input: 3 -> output: "La bomba es una bomba de hormigón." 
 * Caso 4: input: 4 -> output: "La bomba es una bomba de pasta alimenticia." 
 * Inválido (Positivo): input: 5 -> output: "No existe un valor válido para tipo de bomba." 
 * Inválido (Negativo): input: -1 -> output: "No existe un valor válido para tipo de bomba." 
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    int menu;
    cout<<"Ingrese el numero de motor a consultar : "<<endl;
    cin>>menu;

    switch (menu)
    {
        case 0:
            cout<<"No hay establecido un valor definido para el tipo de bomba.";
            break;
        case 1:
            cout<<"La bomba es una bomba de agua.";
            break;
        case 2:
            cout<<"La bomba es una bomba de gasolina.";
            break;
        case 3:
            cout<<"La bomba es una bomba de hormigón.";
            break;
        case 4:
            cout<<"La bomba es una bomba de pasta alimenticia.";
            break;
        default:
            cout<<"No existe un valor válido para tipo de bomba.";
            break;
    }

    return 0;
 }
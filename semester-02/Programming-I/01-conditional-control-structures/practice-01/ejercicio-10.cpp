/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-10.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Calcular la cantidad de dinero en billetes y monedas y cambiar a USD o Euros
 * @problem El programa irá preguntando por la cantidad de billetes y monedas de cada valor que 
 *          tiene el usuario y luego determinará la suma de dinero que hay en monedas y luego la 
 *          suma de dinero que hay en billetes. Luego el programa dirá la suma total de dinero que hay. 
 *          Finalmente, el programa dará al usuario la posibilidad de transformar la cantidad en soles a 
 *          la cantidad equivalente en dólares o euros, según lo decida el usuario.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - 
 *
 * ### Outputs:
 * - 
 *
 * ### Key Variables:
 * - 
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 *
 * ### Edge Cases & Limits:
 * Entradas negativas (Crítico): El programa debe preguntar por la cantidad de billetes y monedas. Una cantidad no puede ser negativa. Es crucial validar que el usuario no ingrese números menores que cero para ninguna denominación.
 * Todas las entradas son cero: Un caso válido donde el usuario no tiene dinero. Todos los totales deben ser 0.00 y la conversión final también debe dar 0.00.
 * Opción de conversión inválida: Cuando se le pida al usuario elegir entre dólares o euros, este podría ingresar una opción no válida (ej. 'X', 'soles', etc.). El programa debe manejar este caso con un mensaje por defecto.
 * Precisión de punto flotante (Concepto avanzado): Al sumar repetidamente valores decimales (como monedas de 0.10 o 0.20), pueden ocurrir pequeños errores de precisión (ej. obtener 9.999999 en lugar de 10.0). Para este ejercicio, usar double es suficiente, pero en sistemas financieros reales, los cálculos se suelen hacer con enteros (trabajando en céntimos) para evitar este problema.
 * 
 * ### Test Plan:
 * Normal (Dólares):
 * input: 2 monedas de S/ 5, 3 billetes de S/ 20, Opción 'D'.
 * output: Total Monedas: S/ 10.00, Total Billetes: S/ 60.00, Total General: S/ 70.00, Total Dólares: $18.67.
 * Todo Cero (Euros):
 * input: Todas las cantidades en 0, Opción 'E'.
 * output: Total Monedas: S/ 0.00, Total Billetes: S/ 0.00, Total General: S/ 0.00, Total Euros: €0.00.
 * Error (Entrada Negativa):
 * input: El usuario ingresa -3 para la cantidad de billetes de S/ 50.
 * output: "Error: La cantidad no puede ser negativa." y el programa debería detenerse o volver a preguntar.
 * Solo Monedas:
 * input: 10 monedas de S/ 0.50, 0 billetes, Opción 'E'.
 * output: Total Monedas: S/ 5.00, Total Billetes: S/ 0.00, Total General: S/ 5.00, Total Euros: €1.25.
 * Opción de Conversión Inválida:
 * input: Cantidades varias, Opción 'X'.
 * output: Se muestran los totales en Soles y al final un mensaje como "Opción de conversión no válida."
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    float billete_10, billete_20, billete_50, billete_100, billete_200;
    float moneda_010, moneda_020, moneda_050, moneda_1, moneda_2, moneda_5;
    float sum_billetes, sum_monedas, sum_dinero;
    int decision;
    float total_dolares, total_euros;

    cout<<"Ingresar cantidad de billetes de 10 "<<endl;
    cin>>billete_10;
    cout<<"Ingresar cantidad de billetes de 20 "<<endl;
    cin>>billete_20;
    cout<<"Ingresar cantidad de billetes de 50 "<<endl;
    cin>>billete_50;
    cout<<"Ingresar cantidad de billetes de 100 "<<endl;
    cin>>billete_100;
    cout<<"Ingresar cantidad de billetes de 200 "<<endl;
    cin>>billete_200;
    cout<<"Ingrese cantidad de monedas de 0.10 "<<endl;
    cin>>moneda_010;
    cout<<"Ingrese cantidad de monedas de 0.20 "<<endl;
    cin>>moneda_020;
    cout<<"Ingrese cantidad de monedas de 0.50 "<<endl;
    cin>>moneda_050;
    cout<<"Ingrese cantidad de monedas de 1 "<<endl;
    cin>>moneda_1;
    cout<<"Ingrese cantidad de monedas de 2 "<<endl;
    cin>>moneda_2;
    cout<<"Ingrese cantidad de monedas de 5 "<<endl;
    cin>>moneda_5;

    sum_billetes = billete_10*10+billete_20*20+billete_50*50+billete_100*100+billete_200*200;
    sum_monedas = moneda_010*0.1+moneda_020*0.2+moneda_050*0.5+moneda_1+moneda_2*2+moneda_5*5;
    sum_dinero = sum_billetes + sum_monedas;

    cout<<"El monto total de dinero es: S/"<<sum_dinero<<endl;
    cout<<"Desea cambiar a dólares o a euros? [dolares = 1, euros = 2, ninguno = 0] "<<endl;
    cin>>decision;

    switch(decision){
       case 1:
            total_dolares = sum_dinero/3.52; //TC 3.52 dólares
            cout<<"El total en dólares es USD"<<total_dolares;
            break;
        case 2:
            total_euros = sum_dinero/4.12; //TC 4.12 euros
            cout<<"El total en euros es €"<<total_euros;
            break;
        default:
            cout<<"Programa finalizado";
            break;

    }

    return 0;
 }
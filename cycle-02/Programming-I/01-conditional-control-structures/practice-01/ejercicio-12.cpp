/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-12.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Detemrinar el descuento de una compra de forma aleatoria.
 * @problem Este programa pide primeramente la cantidad total de compras de una persona.
 *          Si la cantidad es inferior a $100.00, el programa dirá que el cliente no aplica 
 *          a la promoción. Pero si la persona ingresa una cantidad en compras igual o superior 
 *          a $100.00, el programa genera de forma aleatoria un número entero del cero al cinco. 
 *          Cada número corresponderá a un color diferente de cinco colores de bolas que hay para 
 *          determinar el descuento que el cliente recibirá como premio. Si la bola aleatoria es color
 *          blanco, no hay descuento, pero si es uno de los otros cuatro colores, sí se aplicará un 
 *          descuento determinado según la tabla que aparecerá, y ese descuento se aplicará sobre el 
 *          total de la compra que introdujo inicialmente el usuario, de manera que el programa mostrará
 *          un nuevo valor a pagar luego de haber aplicado el descuento.
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
 * Valor Límite (Crítico): El umbral de la promoción, $100.00. Tu programa debe manejar correctamente los valores exactos en esta frontera.
 * Una compra de 99.99 no debe aplicar.
 * Una compra de 100.00 sí debe aplicar.
 * Entradas Inválidas: El total de una compra no puede ser un número negativo. El programa debe validar que la entrada sea >= 0.
 * Generación de Números Aleatorios:
 * Rango: El problema dice "del cero al cinco" (6 posibilidades), pero la tabla de premios mostrada tiene 5 bolas. Supondremos que el rango correcto es de 0 a 4 (5 posibilidades) para que coincida con los premios. Es importante que tu código genere números dentro del rango exacto que decidas.
 * Pruebas: Es imposible probar la aleatoriedad en un plan de pruebas simple. En su lugar, para verificar la lógica, asumimos que se genera un número específico y comprobamos si el cálculo del descuento es correcto para ese caso.
 * 
 * ### Test Plan:
 * No Califica: input: 99.99 output: "No aplica a la promoción."
 * Límite (Califica con Descuento Máximo): input: 100.00, si número_aleatorio = 4 (Amarilla) output: "Ha ganado un 50% de descuento. Nuevo total a pagar: $50.00"
 * Error (Entrada Negativa): input: -50.00 output: "Error: El total de la compra no puede ser negativo."
 * Califica (Sin descuento): input: 200.00, si número_aleatorio = 0 (Blanca) output: "Ha obtenido una bola blanca. No ha ganado descuento. Total a pagar: $200.00"
 * Califica (Con descuento): input: 150.00, si número_aleatorio = 1 (Roja) output: "Ha ganado un 10% de descuento. Nuevo total a pagar: $135.00"
 *
 ******************************************************************************/

 #include <iostream>
 #include <random>
 using namespace std;
 int main()
 {
    random_device rd; // Obtiene una semilla aleatoria de la fuente del sistema
    mt19937 gen(rd()); // Motor de Mersenne Twister inicializado con rd
    uniform_int_distribution<> distrib(1, 5); // Distribución uniforme de 1 a 100

    int numeroEnRango = distrib(gen); // Genera un número aleatorio entre 1 y 100

    float total_compras;

    cout<<"Introduzca la cantidad total de la compras: S/ "<<endl;
    cin>>total_compras;

    if (total_compras<100)
        cout<<"El cliente no aplica a la promocion";
    else
        if (total_compras>=100)
        cout<<"Su gasto iguala o supera los S/ 100 y por tanto participa en la promocion"<<endl;
        cout<<endl;
        cout<<"COLOR - DESCUENTO"<<endl;
        cout<<"1: BOLA BLANCA - no tiene"<<endl;
        cout<<"2: BOLA ROJA - 10% descuento"<<endl;
        cout<<"3: BOLA AZUL - 20% descuento"<<endl;
        cout<<"4: BOLA VERDE - 25% descuento"<<endl;
        cout<<"5: BOLA AMARILLA - 50% descuento"<<endl;
        cout<<endl;

        cout<<"Numero aleatorio : "<<numeroEnRango<<endl;
        cout<<endl;

        switch(numeroEnRango)
        {
            case 1:
                cout<<"Aleatoriamente obtuvo una BOLA BLANCA"<<endl;
                cout<<"No tiene descuento"<<endl;
                break;
            case 2:
                cout<<"Aleatoriamente obtuvo una BOLA ROJA"<<endl;
                cout<<"Felicidades ha ganado un 10% de descuento"<<endl;
                cout<<"Su nuevo total a pagar es: S/"<<total_compras*0.90<<endl;
                break;
            case 3:
                cout<<"Aleatoriamente obtuvo una BOLA AZUL"<<endl;
                cout<<"Felicidades ha ganado un 20% de descuento"<<endl;
                cout<<"Su nuevo total a pagar es: S/"<<total_compras*0.80<<endl;
                break;
            case 4:
                cout<<"Aleatoriamente obtuvo una BOLA VERDE"<<endl;
                cout<<"Felicidades ha ganado un 25% de descuento"<<endl;
                cout<<"Su nuevo total a pagar es: S/"<<total_compras*0.75<<endl;
                break;
            case 5:
                cout<<"Aleatoriamente obtuvo una BOLA AMARILLA"<<endl;
                cout<<"Felicidades ha ganado un 50% de descuento"<<endl;
                cout<<"Su nuevo total a pagar es: S/"<<total_compras*0.50<<endl;
                break;

        }
        cout<<"Si desea salir presione 1 o de lo contrario presione otro numero: ";
    return 0;
 }
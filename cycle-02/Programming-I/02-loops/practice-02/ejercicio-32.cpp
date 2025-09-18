/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-26.cpp
 * @author  José Andrés
 * @date    2025-09-16
 * @brief   Cantidad de dígitos de un n
 * @problem 32. Escribir un programa que indique cuántos dígitos tiene un valor ingresado.
*           Diálogo ejemplo:
*           Número? 2006
*           El valor ingresado tiene = 4 dígitos
 *          
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - un numero entero.
 *
 * ### Outputs:
 * - un numero entero con la cantidad de digitos del numero ingresado
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
 * 
 * ### Test Plan:
 *
 ******************************************************************************/

 #include <iostream>
 using namespace std;

 int main(){
    int num, valor, contador=1;
    cout<<"Numero? : "<<endl;
    cin>>num;
    
    cout<<endl;
    valor = num;
    while (valor >= 0){
      valor = valor / 10;
      cout<<valor<<endl;
      contador++;
    }
    cout<<"El valor ingresado tiene = "<<contador<<" digitos "<<endl;
    return 0;
 } 
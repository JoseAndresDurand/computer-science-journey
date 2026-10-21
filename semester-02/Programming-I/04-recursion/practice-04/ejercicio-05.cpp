/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-05.cpp
 * @author  José Andrés
 * @date    2025-09-25
 * @brief   Mostrar las permutaciones de los dígitos de un numero dado.
 * @problem 5. Dado un número entero positivo N con m dígitos mostrar todas las permutaciones de sus dígitos
 *          
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - un numero entero positivo.
 *
 * ### Outputs:
 * - las permutaciones de los digitos del numero.
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
#include <string>
#include <algorithm>

using namespace std;

void permutar(string& texto, int inicio) {
    if (inicio == texto.length() - 1) {
        cout<<texto<< endl;
        return;
    }
    for (int i = inicio; i < texto.length(); i++) {
        swap(texto[inicio], texto[i]);
        permutar(texto, inicio + 1);
        swap(texto[inicio], texto[i]);
    }
}


int main() {
    int numero;
    cout<<"Ingrese un numero :"<<endl;
    cin>>numero;
    if (numero >= 0){
        string digitos = to_string(numero);
        cout<<"Las permutaciones de los digitos del numero "<<numero<<" son: "<<endl;
        permutar(digitos,0);
    }else{
        cout<<"Debe ingresar un numero positivo";
    }


    return 0;
}

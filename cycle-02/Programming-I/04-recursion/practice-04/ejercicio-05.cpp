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
    cout<<endl;
    cout<<"1era impresion"<<endl;
    if (inicio == texto.length() - 1) {
        cout<<"inicio: "<<inicio<<" length - 1: "<<texto.length()-1<<endl;
        cout <<"***"<< texto << endl;
        return;
    }
    for (int i = inicio; i < texto.length(); i++) {
        cout<<"i del for: "<<i<<" - inicio: "<<inicio<<endl;
        swap(texto[inicio], texto[i]);
        cout<<"1er Swap: "<<texto[inicio]<<" cambia por "<<texto[i]<<endl;
        cout<<"1er Swap: "<<texto<<endl;
        cout<<"Recursividad: "<<i+1<<endl;
        permutar(texto, inicio + 1);
        cout<<endl;
        swap(texto[inicio], texto[i]);
        cout<<"2do Swap: "<<texto[inicio]<<" cambia por "<<texto[i]<<endl;
        cout<<"2do Swap: "<<texto<<endl;
        cout<<endl;
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
/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-10.cpp
 * @author  José Andrés
 * @date    2025-09-26
 * @brief   Verificar si una cadena es palíndroma.
 * @problem 10. Verificar si una cadena es palíndroma.
 *          
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 *
 * ### Outputs:
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

using namespace std;

bool palindromo(string cadena){
    string cadenaInvertida;
    if (cadena.size() == 1){
        return true;
    }
    for (int i=cadena.size()-1; i>=0;i--){
        cadenaInvertida = cadenaInvertida + cadena[i];
    }
    if (cadena == cadenaInvertida){
        return true;
    }
    return false;
}

int main(){
    string cadena;
    cout<<"Ingrese una cadena de texto: "<<endl,
    cin>>cadena;

    if (palindromo(cadena)){
        cout<<"La cadena SÍ es palíndroma"<<endl;
    }else{
        cout<<"La cadena NO es palíndroma"<<endl;
    }
    return 0;
}

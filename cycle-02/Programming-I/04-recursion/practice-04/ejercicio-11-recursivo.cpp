/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-11.cpp
 * @author  José Andrés
 * @date    2025-09-26
 * @brief   Funcion recursiva que cuenta el numero de 2 unos seguidos en una cadena binaria.
 * @problem 11. Escribir una función recursiva que cuente el número de secuencias de 
 *          dos 1 seguidos que hay en una cadena de caracteres que represente un número binario.
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

int dosUnosSeguidos(string cadenaNumBinario){
    if (cadenaNumBinario.size() < 2){
        return 0;
    }
    int unos = 0;
    if (cadenaNumBinario[0]=='1' && cadenaNumBinario[1]=='1'){
        unos = 1;
    }
    return unos + dosUnosSeguidos(cadenaNumBinario.substr(1));
}

int main(){
    string cadenaNumBinario;
    cout<<"Ingrese una cadena binaria (solo 1s y 0s): "<<endl;
    cin>>cadenaNumBinario;
    cout<<"La cadena "<<cadenaNumBinario<<" contiene "<<dosUnosSeguidos(cadenaNumBinario)<<" dos unos seguidos"<<endl;
    return 0;
}

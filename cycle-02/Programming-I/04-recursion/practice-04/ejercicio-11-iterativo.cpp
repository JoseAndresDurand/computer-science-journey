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
    int count = 0;
    for (int i=0; i<cadenaNumBinario.size()-1;i++){
        if (cadenaNumBinario[i]=='1' && cadenaNumBinario[i+1]=='1'){
            count ++;
            i += 2;  
        }
    }
    return count;
}

int main(){
    string cadenaNumBinario;
    cout<<"Ingrese una cadena binaria (solo 1s y 0s): "<<endl;
    cin>>cadenaNumBinario;
    cout<<"La cadena "<<cadenaNumBinario<<" contiene "<<dosUnosSeguidos(cadenaNumBinario)<<" dos unos seguidos"<<endl;
    return 0;
}

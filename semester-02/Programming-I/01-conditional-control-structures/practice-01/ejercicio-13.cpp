/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-13.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Hallar el numero central de 3 numeros.
 * @problem El usuario introduce tres números enteros y el programa se encargará de
 *          decir cuál de los tres es el central o el de en medio.
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
 * 
 * ### Test Plan:
 *
 ******************************************************************************/

 #include <iostream>
 using namespace std;
 int main()
 {
    int num1, num2, num3, central;
    cout<<"Ingresar 3 numeros"<<endl;
    cin>>num1>>num2>>num3;

    if (num2 <= num1 && num1 <= num3 || num3 <= num1 && num1 <= num2){
        central = num1;
    }else if (num1 <= num2 && num2 <= num3 || num3 <= num2 && num2 <= num1){
        central = num2;
    }else if (num1 <= num3 && num3 <= num2 || num2 <= num3 && num3 <= num1){
        central = num3;
    }
    cout<<"El numero central es: "<<central<<endl;
    return 0;
 }
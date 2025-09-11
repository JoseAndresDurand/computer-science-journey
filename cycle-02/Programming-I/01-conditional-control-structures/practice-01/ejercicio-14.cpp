/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-14.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Ordenar de menor a mayor y viceversa 3 numeros enteros.
 * @problem El usuario introduce tres números enteros y el programa los ordenará en orden ascendente
 *          y a continuación en orden descendente, mostrando en la primer columna los números de menor
 *          a mayor y en la siguiente columna a continuación los números de mayor a menor.
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
    int num1, num2, num3, menor, central, mayor;
    cout<<"Ingresar 3 numeros"<<endl;
    cin>>num1>>num2>>num3;
    menor = num1;
    central = num2;
    mayor = num3;
    if (num2 < menor){
        menor = num2;
        if (num3 < num1){
            central = num3;
            mayor = num1;
        }else{
            central = num1;
            mayor = num3;
        }
    }
    if (num3 < menor){
        menor = num3;
        if (num1 < num2){
            central = num1;
            mayor = num2;
        }else{
            central = num2;
            mayor = num1;
        }
    }

    cout<<menor<<"  "<<mayor<<endl;
    cout<<central<<"  "<<central<<endl;
    cout<<mayor<<"  "<<menor<<endl;
    return 0;
 }
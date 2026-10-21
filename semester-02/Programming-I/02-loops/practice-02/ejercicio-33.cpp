/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-26.cpp
 * @author  José Andrés
 * @date    2025-09-16
 * @brief   Lista de numeros primos entre a y b.
 * @problem 33. Escribir un programa que muestre todos los números primos entre un intervalo [a,b] y cuyo
*           encabezamiento sea el siguiente:
*           Números Primos entre [a , b]
*           a? 5
*           b? 10
*           Los números primos son:
*           5 7
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
 #include <cmath>
 using namespace std;

 int main(){
    int num1, num2, contador=0;
    bool esPrimo;
    cout<<"Numeros Primos entre [a , b] "<<endl;
    cout<<"a :? "<<endl;
    cin>>num1;
    cout<<"b :? "<<endl;
    cin>>num2;
    cout<<endl;
    
    for (int i=num1; i<=num2;i++){
      for (int j=2;j<=sqrt(i);j++){
        if (i % j == 0){
          contador++;
        }
      }
      if (contador < 1){
        cout<<i<<" ";
      }
      contador = 0;
    }
    return 0;
 } 
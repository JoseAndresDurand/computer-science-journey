/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-26.cpp
 * @author  José Andrés
 * @date    2025-09-16
 * @brief   Todas las permutaciones de 1 a n
 * @problem 26. Escriba un programa que despliegue todas las permutaciones de los 
 *          números del 1 a n. Por ejemplo, si n = 3, debe obtenerse:
 *          1 2 3
 *          3 2 1
 *          3 1 2
 *          2 1 3
 *          2 3 1      
 *          1 3 2
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
 * - lista con todas las permutaciones 
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
    int num, numFactorial;
    cout<<"Ingresar el numero para realizar las permutaciones: "<<endl;
    cin>>num;
    cout<<"Las permutaciones son"<<endl;

    numFactorial = 1;
    for (int i=1;i<=num;i++){
        numFactorial *= i;
    }

    for (int i=1; i<=numFactorial;i++){
        cout<<i<<": ";
        for (int j=1; j<=num;j++){
            int valor = (i+j) % num + 1;
            cout<<valor<<" "; 
            
            /*
            1: 3 1 2
            2: 1 2 3
            3: 2 3 1
            Lograr invertir cada una y se tiene todas las combinaciones.            
            */
            
            
        }
        
        cout<<endl;
    }

    return 0;
 }
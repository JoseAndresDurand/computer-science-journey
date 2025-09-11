/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-15.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Calcular el precio del boleta de ferrocarril en función a la distancia (km) y dias entre ida y vuelta.
 * @problem El programa determina el precio de un boleto de ida y vuelta en ferrocarril, 
 *          conociendo la distancia a recorrer y sabiendo que si el número de días de estancia
 *          es mayor o igual a 7 y la distancia mayor o igual a 100 kilómetros, el boleto tiene
 *          una reducción del 50%. El precio por kilómetro es de 1 dólar.
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
    int distancia, dias, precioBoleto;
    cout<<"Ingresar distancia del viaje en km : "<<endl;
    cin>>distancia;
    cout<<"Ingresar cantidad de dias entre la ida y el retorno : "<<endl;
    cin>>dias;

    if (dias >= 7 && distancia > 100){
        precioBoleto = distancia*2*0.5;
        cout<<"El precio del boleto tiene una reducción del 50%, por lo que el precio es USD: "<<precioBoleto<<endl;
    }else{
        precioBoleto = distancia*2;
        cout<<"El precio del boleto es USD : "<<precioBoleto<<endl;
    }

    return 0;
 }
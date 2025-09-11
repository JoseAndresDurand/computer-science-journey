/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-15.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Calcular los puntos y tabla de posición de 3 equipos de futbol.
 * @problem El usuario introduce el total de puntos de 3 equipos de futbol. El programa 
 *          determinara qué equipo va en primero, segundo y tercer lugar o si hay empate 
 *          en puntos entre algunos equipos, dirá quiénes van empatados y en qué lugar están 
 *          empatados. Luego el programa dirá cuántos puntos le faltan al segundo lugar para alcanzar
 *          al primer lugar y cuántos puntos le faltan al tercer lugar para alcanzar al segundo lugar, y
 *          en caso de haber empates en puntos, el programa hará saber quiénes están empatados en puntos,
 *          en qué lugar de la tabla de posiciones empatan y cuántos puntos les falta a ambos para alcanzar 
 *          a otro equipo o para que los alcancen a ellos. Si los tres equipos empatan en puntos, el programa
 *          dirá que los tres empatan.
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
    int equipo1, equipo2, equipo3, primero, segundo, tercero;

    cout<<"Ingresar puntaje para el equipo 1, 2 y 3 : "<<endl;
    cin>>equipo1>>equipo2>>equipo3;

    primero = equipo1;
    segundo = equipo2;
    tercero = equipo3;
    if (equipo2 < tercero){
        tercero = equipo2;
        if (equipo3 < equipo1){
            segundo = equipo3;
            primero = equipo1;
        }else{
            segundo = equipo1;
            primero = equipo3;
        }
    }
    if (equipo3 < tercero){
        tercero = equipo3;
        if (equipo1 < equipo2){
            segundo = equipo1;
            primero = equipo2;
        }else{
            segundo = equipo2;
            primero = equipo1;
        }
    }

    

    return 0;
 }
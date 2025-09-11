/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-08.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Mostrar mensajes de acuerdo al diámetro y grosor del objeto rueda.
 * @problem Considera estás desarrollando un programa donde necesitas trabajar con objetos de tipo Rueda
 *          (que representa a una rueda de un vehículo). Realizar las siguientes comprobaciones:
 *          a) Si el diámetro es superior a 1.4 debe mostrar por consola el mensaje “La rueda es para un vehículo grande”. 
 *          Si es menor o igual a 1.4 pero mayor que 0.8 debe mostrarse por consola el mensaje “La rueda es para un vehículo
 *          mediano”. Si no se cumplen ninguna de las condiciones anteriores debe mostrarse por pantalla el mensaje “La rueda es para un vehículo pequeño”.
 *          b) Si el diámetro es superior a 1.4 con un grosor inferior a 0.4, ó si el diámetro es menor o igual a 1.4 pero mayor que 0.8, con un grosor inferior 
 *          a 0.25, deberá mostrarse por consola el mensaje “El grosor para esta rueda es inferior al recomendado”.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Dos tipos de numeros decimales
 *
 * ### Outputs:
 * - Dos mensajes de acuerdo al diametro y grosos de la rueda
 *
 * ### Key Variables:
 * - diametro (float): diámetro de la rueda.
 * - grosor (float): grosor de la rueda.
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables diametro y grosor.
 * 3.  Mostrar mensaje "Ingrese el diametro y grosor de la rueda:"
 * 4.  Leer y almacenar el valor en las variables diametro y grosor.
 * 6.  SI (diametro > 1.4) ENTONCES
 * 7.       Mostrar mensaje: La rueda es para un vehículo grande
 * 8.  SINO SI (diametro > 0.8) ENTONCES
 * 9.       Mostrar mensaje: La rueda es para un vehículo mediano
 * 10. SINO
 * 11.      Mostrar mensaje: La rueda es para un vehículo pequeño
 * 12. FIN SI
 * 13. SI ((diametro > 1.4 and grosor < 0.4) or ((diametro <= 1.4 and diametro > 0.8) and grosor < 0.25) ) ENTONCES
 * 14.      Mostrar mensaje: El grosor para esta rueda es inferior al recomendado
 * 15. FIN SI
 *
 * ### Edge Cases & Limits:
 * Valores Límite: El programa debe comportarse correctamente justo en los límites de las condiciones.
 *  Cuando el diámetro es exactamente 1.4.
 *  Cuando el diámetro es exactamente 0.8.
 *  Cuando el grosor es exactamente 0.4 (para ruedas grandes) o 0.25 (para ruedas medianas).
 * Entradas Inválidas (Lógica de Negocio): Un objeto físico como una rueda no puede tener dimensiones negativas o nulas. El programa debería validar que tanto el diámetro como el grosor sean mayores que cero.
 * Condiciones Compuestas: La lógica de la parte (b) tiene una condición O (||). Tu plan de pruebas debe tener al menos un caso que cumpla la primera parte de la condición y otro que cumpla la segunda, para asegurar que ambas funcionan.
 *
 * ### Test Plan:
 * Grande (OK): input: 1.5, 0.5 -> output: "La rueda es para un vehículo grande."
 * Grande (Grosor Bajo): input: 1.5, 0.3 -> output: "La rueda es para un vehículo grande." y  "El grosor para esta rueda es inferior al recomendado."
 * Mediano (OK): input: 1.2, 0.3 -> output: "La rueda es para un vehículo mediano."
 * Mediano (Grosor Bajo): input: 1.2, 0.2 -> output: "La rueda es para un vehículo mediano." y "El grosor para esta rueda es inferior al recomendado."
 * Pequeño: input: 0.7, 0.2 -> output: "La rueda es para un vehículo pequeño."
 * Límite (Grande/Mediano): input: 1.4, 0.3 -> output: "La rueda es para un vehículo mediano."
 * Límite (Mediano/Pequeño): input: 0.8, 0.2 -> output: "La rueda es para un vehículo pequeño."
 * Error (Diámetro Inválido): input: -2, 0.5 -> output: "Error: El diámetro no puede ser negativo o cero."
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    float diametro, grosor;
    cout<<"Ingrese el diametro y grosor de la rueda : "<<endl;
    cin>>diametro>>grosor;
    if (diametro > 0 && grosor > 0){
            if (diametro > 1.4){
                cout<<"La rueda es para un vehículo grande"<<endl;
            }else if (diametro > 0.8){
                cout<<"La rueda es para un vehículo mediano"<<endl;
            }else{
                cout<<"La rueda es para un vehículo pequeño"<<endl;
            }

            if ((diametro > 1.4 && grosor < 0.4) || ((diametro <= 1.4 && diametro > 0.8) && grosor < 0.25)){
                cout<<"El grosor para esta rueda es inferior al recomendado"<<endl;
            }
    }else{
        cout<<"[Error] El grosor y diametro deben ser mayores a 0"<<endl;
    }
    return 0;
 }
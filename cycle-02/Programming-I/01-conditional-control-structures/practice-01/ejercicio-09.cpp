/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-09.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Mostrar el signo zodiacal en función al día y mes de nacimiento.
 * @problem Este programa muestra el signo zodiacal de una persona. Para ello el usuario debe
 *          introducir únicamente el día y el mes de nacimiento y el programa determinará inmediatamente
 *          el signo zodiacal de la persona.
 *
 *******************************************************************************
 * -----------------------------------------------------------------------------
 * ANALYSIS & DESIGN
 * -----------------------------------------------------------------------------
 *
 * ## ANALYSIS
 *
 * ### Inputs:
 * - Dos tipos de numeros enteros.
 *
 * ### Outputs:
 * - Mensaje indicando el signo zodiacal
 *
 * ### Key Variables:
 * - dia (int): dia de nacimiento
 * - mes (int): mes de nacimiento
 *
 * ## DESIGN
 *
 * ### Logic (Pseudocode):
 * 1.  INICIO
 * 2.  Declarar las variables diametro y grosor.
 * 3.  Mostrar mensaje "Ingrese el dia y mes de nacimiento "dia mes" (Ej. 16 05):"
 * 4.  Leer y almacenar el valor en las variables dia y mes.
 * 5.  SI ((dia > 0 and dia < 31) and (mes > 0 and mes < 13)) ENTONCES
 * 5.  SWITCH (mes)
 * 6.        CASO 1:
 * 7.           SI (dia <= 19) ENTONCES
 * 8.               Mostrar mensaje: Tu signo es Capricornio.
 * 9.           SINO SI (dia >= 20) ENTONCES
 * 10.              Mostrar mensaje: Tu signo es Acuario.
 * 11.       CASO 2:
 * 12.           SI (dia <= 18) ENTONCES
 * 13.               Mostrar mensaje: Tu signo es Acuario.
 * 14.           SINO SI (dia >= 19) ENTONCES
 * 15.              Mostrar mensaje: Tu signo es Piscis.
 * 16.       CASO 3:
 * 17.           SI (dia <= 20) ENTONCES
 * 18.               Mostrar mensaje: Tu signo es Piscis.
 * 19.           SINO SI (dia >= 21) ENTONCES
 * 20.              Mostrar mensaje: Tu signo es Aries.
 * 21.       CASO 4:
 * 22.           SI (dia <= 19) ENTONCES
 * 23.               Mostrar mensaje: Tu signo es Aries.
 * 24.           SINO SI (dia >= 20) ENTONCES
 * 25.              Mostrar mensaje: Tu signo es Tauro.
 * 26.       CASO 5:
 * 27.           SI (dia <= 20) ENTONCES
 * 38.               Mostrar mensaje: Tu signo es Tauro.
 * 99.           SINO SI (dia >= 21) ENTONCES
 * 30.              Mostrar mensaje: Tu signo es Geminis.
 * 31.       CASO 6:
 * 32.           SI (dia <= 20) ENTONCES
 * 33.               Mostrar mensaje: Tu signo es Geminis.
 * 34.           SINO SI (dia >= 21) ENTONCES
 * 35.              Mostrar mensaje: Tu signo es Cancer.
 * 36.       CASO 7:
 * 37.           SI (dia <= 22) ENTONCES
 * 38.               Mostrar mensaje: Tu signo es Cancer.
 * 39.           SINO SI (dia >= 23) ENTONCES
 * 40.              Mostrar mensaje: Tu signo es Leo.
 * 41.       CASO 8:
 * 42.           SI (dia <= 22) ENTONCES
 * 43.               Mostrar mensaje: Tu signo es Leo.
 * 44.           SINO SI (dia >= 23) ENTONCES
 * 45.              Mostrar mensaje: Tu signo es Virgo.
 * 46.       CASO 9:
 * 47.           SI (dia <= 22) ENTONCES
 * 48.               Mostrar mensaje: Tu signo es Virgo.
 * 49.           SINO SI (dia >= 23) ENTONCES
 * 50.              Mostrar mensaje: Tu signo es Libra.
 * 51.       CASO 10:
 * 52.           SI (dia <= 22) ENTONCES
 * 53.               Mostrar mensaje: Tu signo es Libra.
 * 54.           SINO SI (dia >= 23) ENTONCES
 * 55.              Mostrar mensaje: Tu signo es Escorpio.
 * 56.       CASO 11:
 * 57.           SI (dia <= 21) ENTONCES
 * 58.               Mostrar mensaje: Tu signo es Escorpio.
 * 59.           SINO SI (dia >= 22) ENTONCES
 * 60.              Mostrar mensaje: Tu signo es Sagitario.
 * 61.       CASO 12:
 * 62.           SI (dia <= 21) ENTONCES
 * 63.               Mostrar mensaje: Tu signo es Sagitario.
 * 64.           SINO SI (dia >= 22) ENTONCES
 * 65.              Mostrar mensaje: Tu signo es Capricornio.
 * 66. SINO
 * 67.      Mostrar mensaje: [Error] Mes o dia no valido.
 * 
 * ### Edge Cases & Limits:
 * Validación de Fechas (Crítico): Antes de cualquier otra lógica, debes asegurarte de que la fecha sea válida.
 *  El mes debe estar en el rango [1, 12].
 *  El día debe ser mayor que 0.
 *  El día debe ser válido para el mes correspondiente (ej. no puede ser 31 para abril, que tiene 30 días, o 30 para febrero). Para simplificar, podemos asumir que febrero siempre tiene un máximo de 29 días, ignorando los años bisiestos.
 * Fechas Límite (Cúspides): Estos son los días exactos en que un signo zodiacal cambia a otro (ej. 20 y 21 de marzo). Tu lógica debe clasificar correctamente cada uno de estos días límite para asegurar que las condiciones (>=, <=) están bien definidas.
 * 
 * ### Test Plan:
 * Mes inválido: input: 13, 10 -> output: "Error: Mes inválido."
 * Día inválido (para mes de 30): input: 4, 31 -> output: "Error: Día inválido para este mes."
 * Día inválido (para febrero): input: 2, 30 -> output: "Error: Día inválido para febrero."
 * Día inválido (cero o negativo): input: 1, -5 -> output: "Error: Día inválido."
 * Transición Piscis a Aries: input: 3, 20 -> output: "Piscis"
 * Transición Piscis a Aries: input: 3, 21 -> output: "Aries"
 * Transición Aries a Tauro: input: 4, 19 -> output: "Aries"
 * Caso de prueba Leo: input: 8, 15 -> output: "Leo"
 * Caso de prueba Escorpio: input: 11, 5 -> output: "Escorpio"
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    int dia, mes;
    cout<<"Ingresar tu dia y mes de nacimiento dia mes (Ej. 16 03)"<<endl,
    cin>>dia>>mes;

    if ((dia > 0 && dia < 32) && (mes > 0 && mes < 13)){
        switch (mes){
            case 1: //enero
                if (dia <= 19){
                    cout<<"Tu signo es Capricornio"<<endl;
                }else{
                    cout<<"Tu signo es Acuario"<<endl;
                }
                break;
            case 2: //febrero
                if (dia < 30){
                    if (dia <= 18){
                    cout<<"Tu signo es Acuario"<<endl;
                    }else{
                        cout<<"Tu signo es Piscis"<<endl;
                    }
                }else{
                    cout<<"El mes de febrero tiene maximo 29 dias"<<endl;
                }
                
                break;
            case 3: //marzo
                if (dia <= 20){
                    cout<<"Tu signo es Piscis"<<endl;
                }else{
                    cout<<"Tu signo es Aries"<<endl;
                }
                break;
            case 4: //abril
                if (dia < 31){
                    if (dia <= 19){
                    cout<<"Tu signo es Aries"<<endl;
                    }else{
                        cout<<"Tu signo es Tauro"<<endl;
                    }
                }else{
                    cout<<"El mes de abril tiene maximo 30 dias"<<endl;
                }
                break;
            case 5: //mayo
                if (dia <= 20){
                    cout<<"Tu signo es Tauro"<<endl;
                }else if (dia >= 21){
                    cout<<"Tu signo es Geminis"<<endl;
                }
                break;
            case 6: //junio
                if (dia < 31){
                    if (dia <= 20){
                        cout<<"Tu signo es Geminis"<<endl;
                    }else if (dia >= 21){
                        cout<<"Tu signo es Cancer"<<endl;
                    }
                }else{
                    cout<<"El mes de junio tiene maximo 30 dias"<<endl;
                }
                break;
            case 7: //julio
                if (dia <= 22){
                    cout<<"Tu signo es Cancer"<<endl;
                }else{
                    cout<<"Tu signo es Leo"<<endl;
                }
                break;
            case 8: //agosto
                if (dia <= 22){
                    cout<<"Tu signo es Leo"<<endl;
                }else{
                    cout<<"Tu signo es Virgo"<<endl;
                }
                break;
            case 9: //setiembre
                if (dia < 31){
                    if (dia <= 22){
                        cout<<"Tu signo es Virgo"<<endl;
                    }else{
                        cout<<"Tu signo es Libra"<<endl;
                    }
                }else{
                    cout<<"El mes de setiembre tiene como maximo 30 dias"<<endl;
                }
                
                break;
            case 10: //octubre
                if (dia <= 22){
                    cout<<"Tu signo es Libra"<<endl;
                }else{
                    cout<<"Tu signo es Escorpio"<<endl;
                }
                break;
            case 11: //noviembre
                if (dia < 31){
                    if (dia <= 21){
                        cout<<"Tu signo es Escorpio"<<endl;
                    }else{
                        cout<<"Tu signo es Sagitario"<<endl;
                    }
                }else{
                    cout<<"El mes de noviembre tiene como maximo 30 dias"<<endl;
                }
                
                break;
            case 12: //diciembre
                if (dia <= 21){
                    cout<<"Tu signo es Sagitario"<<endl;
                }else{
                    cout<<"Tu signo es Capricornio"<<endl;
                }
                break;
        }
    }else{
        cout<<"El mes y dia no son validos"<<endl;
    }

    return 0;
 }
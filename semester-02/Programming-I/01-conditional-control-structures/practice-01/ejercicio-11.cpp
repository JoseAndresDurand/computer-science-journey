/*******************************************************************************
 * -----------------------------------------------------------------------------
 * METADATA
 * -----------------------------------------------------------------------------
 * @file    ejercicio-11.cpp
 * @author  José Andrés
 * @date    2025-09-10
 * @brief   Calculo de horas trabajadas en horario de oficina y extras.
 * @problem Este programa muestra los pagos que recibirá un trabajador por cada hora laboral 
 *          en base a la hora del día en que trabaja. El usuario deberá escribir el número de horas 
 *          trabajadas en cada uno de los horarios y el programa determinará el total de dinero a recibir 
 *          por el trabajador y también dirá si ganó más dinero por horas extras que por horas de oficina 
 *          trabajadas o viceversa, o si el trabajador ganó exactamente lo mismo por horas extras que por horas
 *          de oficina. Diálogo ejemplo: [Ver imagen].
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
 * Entradas negativas (Crítico): El programa debe validar que el número de horas ingresado para cada categoría no sea negativo. No se pueden trabajar horas negativas.
 * Todas las entradas son cero: Un caso de prueba fundamental. Si un trabajador no registra horas, todos sus pagos deben ser cero, y el resultado de la comparación debe ser que "ganó lo mismo" (S/ 0 es igual a S/ 0).
 * Caso de igualdad (Crítico para la lógica): El programa debe poder identificar correctamente la situación en la que el pago por horas de oficina es exactamente igual al pago total por horas extras. La lógica de comparación final (if-else if-else) debe manejar este caso explícitamente.
 * Solo un tipo de horas: El programa debe funcionar correctamente si solo se ingresan horas de oficina (y cero en todas las extras) o si solo se ingresan horas extras (y cero en las de oficina).
 * 
 * ### Test Plan:
 * Gana más en Oficina (Caso del PDF):
 * input: [40, 10, 2, 1]
 * output: Oficina: S/ 480, Extras: S/ 210, Total: S/ 690. Mensaje: "Ganó más por horas de oficina..."
 * Gana más en Extras:
 * input: [10, 10, 0, 0]
 * output: Oficina: S/ 120, Extras: S/ 150, Total: S/ 270. Mensaje: "Ganó más por horas extras..."
 * Ganan lo Mismo:
 * input: [10, 0, 0, 5]
 * output: Oficina: S/ 120, Extras: S/ 120, Total: S/ 240. Mensaje: "Ganó exactamente lo mismo..."
 * Todo Cero:
 * input: [0, 0, 0, 0]
 * output: Oficina: S/ 0, Extras: S/ 0, Total: S/ 0. Mensaje: "Ganó exactamente lo mismo..."
 * Error (Entrada Negativa):
 * input: [40, -5, 2, 1]
 * output: "Error: Las horas trabajadas no pueden ser negativas."
 *
 ******************************************************************************/

 #include <iostream>
 #include <cmath>
 using namespace std;
 int main()
 {
    float horas_turno_A,horas_turno_B,horas_turno_C, horas_turno_D;
    float pago_total, pago_horas_oficina, pago_horas_extra;

    cout<<"HORARIO"<<endl;
    cout<<"TURNO A: Pago: base"<<endl;
    cout<<"08:00 AM - 04:00 PM"<<endl;
    cout<<"TURNO B: Pago: 25% extra"<<endl;
    cout<<"04:00 PM - 08:00 PM"<<endl;
    cout<<"TURNO C: Pago: 50% extra"<<endl;
    cout<<"08:00 PM - 12:00 AM"<<endl;
    cout<<"TURNO D: Pago: doble"<<endl;
    cout<<"12:00 AM - 08:00 AM"<<endl;
    cout<<endl;
    cout<<"Sueldo base por hora trabajada: 12"<<endl;
    cout<<endl;
    cout<<"Horas trabajadas en el turno 08:00 AM - 04:00 PM"<<endl;
    cin>>horas_turno_A;
    cout<<"Horas trabajadas en el turno 04:00 PM - 08:00 PM"<<endl;
    cin>>horas_turno_B;
    cout<<"Horas trabajadas en el turno 08:00 PM - 12:00 AM"<<endl;
    cin>>horas_turno_C;
    cout<<"Horas trabajadas en el turno 12:00 AM - 08:00 AM"<<endl;
    cin>>horas_turno_D;
    cout<<endl;

    pago_total = horas_turno_A*12 + horas_turno_B*12*1.25 + horas_turno_C*12*1.5 + horas_turno_D*12*2;
    pago_horas_oficina = horas_turno_A*12 + horas_turno_D*12*2;
    pago_horas_extra = horas_turno_B*12*1.25 + horas_turno_C*12*1.5;

    cout<<"El pago total que recibira el trabajador es : S/"<<pago_total<<endl;
    cout<<"El salario del trabajador por horas de oficina es : S/"<<pago_horas_oficina<<endl;
    cout<<"El salario del trabajador por horas extra es : S/"<<pago_horas_extra<<endl;

    if (pago_horas_oficina > pago_horas_extra)
        cout<<"El trabajador gano mas dinero por horas de oficina que por horas extra";
    else
        if (pago_horas_oficina < pago_horas_extra)
            cout<<"El trabajador gano mas dinero por horas extra que por horas de oficina";
        else
            cout<<"El trabajador gano igual cantidad en horas trabajadas de oficina y extras";
    return 0;
 }
#include <iostream>
#include <iomanip>  // Para setw, setprecision
#include <random>   // Para random_device y mt19937 (Generación profesional)

using namespace std;

// ======================================================================================
// CONSTANTES DEL ESCENARIO MÉDICO (Configurables)
// ======================================================================================
const double PREVALENCIA    = 0.01; // 1% de la población tiene la enfermedad
const double SENSIBILIDAD   = 0.99; // 99% de acierto si estás enfermo (Verdadero Positivo)
const double ESPECIFICIDAD  = 0.95; // 95% de acierto si estás sano (Verdadero Negativo)
// Nota: La Tasa de Falsos Positivos es 1.0 - ESPECIFICIDAD = 0.05 (5%)

// ======================================================================================
// FUNCIONES DE INTERFAZ (TUI)
// ======================================================================================
void imprimirLinea() {
    cout << string(60, '-') << endl;
}

// Función para imprimir porcentajes bonitos
void imprimirPorcentaje(string etiqueta, double valor) {
    cout << left << setw(35) << etiqueta 
         << ": " << right << fixed << setprecision(2) << (valor * 100.0) << "%" << endl;
}

// ======================================================================================
// MAIN
// ======================================================================================
int main() {
    // Configuración de la "semilla" aleatoria (Hardware entropy)
    random_device rd;  
    // El motor Mersenne Twister (Estándar de oro para simulaciones científicas)
    mt19937 gen(rd()); 
    // Distribución uniforme entre 0.0 y 1.0 (como tirar un dado de infinitas caras)
    uniform_real_distribution<> dis(0.0, 1.0);

    long long n; // Cantidad de simulaciones (long long por si quieres millones)

    // 1. ENTRADA DE DATOS
    cout << "=== SIMULADOR MONTE CARLO: DIAGNOSTICO MEDICO ===" << endl;
    cout << "Este programa simula miles de pacientes para demostrar" << endl;
    cout << "el Teorema de Bayes vs Resultados Empiricos." << endl;
    imprimirLinea();
    
    do {
        cout << "Ingrese numero de pacientes a simular (ej. 100000): ";
        cin >> n;
        if (n <= 0) cout << "ERROR: Ingrese un numero positivo mayor a 0." << endl;
    } while (n <= 0);

    // 2. MOTOR DE SIMULACIÓN (EL LOOP PRINCIPAL)
    long long cont_enfermos_reales = 0;
    long long cont_total_positivos = 0;
    long long cont_verdaderos_positivos = 0;
    long long cont_falsos_positivos = 0;

    cout << "\nSimulando..." << endl;

    for (long long i = 0; i < n; ++i) {
        
        // PASO A: DETERMINAR EL ESTADO REAL (Enfermo o Sano)
        // Tiramos el dado. Si sale menor a 0.01 (1%), la persona está enferma.
        bool esta_enfermo = dis(gen) < PREVALENCIA; 

        if (esta_enfermo) {
            cont_enfermos_reales++;
        }

        // PASO B: APLICAR EL TEST MÉDICO
        bool resultado_test_positivo = false;

        if (esta_enfermo) {
            // Si está enfermo, el test da positivo según la SENSIBILIDAD (99%)
            if (dis(gen) < SENSIBILIDAD) {
                resultado_test_positivo = true;
                cont_verdaderos_positivos++; // Acertamos
            }
        } else {
            // Si está sano, el test da positivo (error) según (1 - ESPECIFICIDAD)
            // Es decir, hay un 5% de probabilidad de Falso Positivo
            if (dis(gen) < (1.0 - ESPECIFICIDAD)) {
                resultado_test_positivo = true;
                cont_falsos_positivos++; // Nos equivocamos
            }
        }

        // Acumular si el test dio luz roja
        if (resultado_test_positivo) {
            cont_total_positivos++;
        }
    }

    // 3. CÁLCULOS FINALES
    
    // A) Probabilidad Empírica (Lo que observó la simulación)
    // Formula: De todos los que dieron positivo, ¿cuántos estaban realmente enfermos?
    double prob_empirica = 0.0;
    if (cont_total_positivos > 0) {
        prob_empirica = (double)cont_verdaderos_positivos / cont_total_positivos;
    }

    // B) Probabilidad Teórica (Teorema de Bayes)
    // P(Enfermo|Positivo) = [P(Pos|Enfermo) * P(Enfermo)] / P(Positivo)
    // P(Positivo) = P(Pos|Enfermo)*P(Enfermo) + P(Pos|Sano)*P(Sano)
    
    double p_enfermo = PREVALENCIA;
    double p_sano = 1.0 - PREVALENCIA;
    double p_pos_dado_enfermo = SENSIBILIDAD;
    double p_pos_dado_sano = 1.0 - ESPECIFICIDAD; // Tasa Falsos Positivos

    double numerador = p_pos_dado_enfermo * p_enfermo;
    double denominador = (p_pos_dado_enfermo * p_enfermo) + (p_pos_dado_sano * p_sano);
    
    double prob_teorica_bayes = numerador / denominador;


    // 4. SALIDA DE RESULTADOS
    cout << "\n\n";
    imprimirLinea();
    cout << " PARAMETROS DE LA POBLACION" << endl;
    imprimirLinea();
    cout << left << setw(35) << "Poblacion simulada (N)" << ": " << n << endl;
    imprimirPorcentaje("Prevalencia enfermedad", PREVALENCIA);
    imprimirPorcentaje("Sensibilidad del Test", SENSIBILIDAD);
    imprimirPorcentaje("Especificidad del Test", ESPECIFICIDAD);
    imprimirPorcentaje("Tasa Falsos Positivos (Calc)", 1.0 - ESPECIFICIDAD);

    cout << "\n";
    imprimirLinea();
    cout << " RESULTADOS DE LA SIMULACION" << endl;
    imprimirLinea();
    cout << left << setw(35) << "Total Enfermos Reales" << ": " << cont_enfermos_reales << endl;
    cout << left << setw(35) << "Total Tests Positivos (+)" << ": " << cont_total_positivos << endl;
    cout << left << setw(35) << "   -> Verdaderos Positivos" << ": " << cont_verdaderos_positivos << endl;
    cout << left << setw(35) << "   -> Falsos Positivos (Sanos)" << ": " << cont_falsos_positivos << endl;

    cout << "\n";
    imprimirLinea();
    cout << " CONCLUSION BAYESIANA" << endl;
    cout << " Pregunta: Si el test da positivo, cual es la probabilidad real" << endl;
    cout << " de tener la enfermedad?" << endl;
    imprimirLinea();
    
    imprimirPorcentaje("Probabilidad Teorica (Bayes)", prob_teorica_bayes);
    imprimirPorcentaje("Probabilidad Empirica (Simul.)", prob_empirica);
    
    double diferencia = abs(prob_teorica_bayes - prob_empirica);
    cout << string(60, '.') << endl;
    imprimirPorcentaje("Diferencia (Error de Simul.)", diferencia);
    imprimirLinea();

    return 0;
}
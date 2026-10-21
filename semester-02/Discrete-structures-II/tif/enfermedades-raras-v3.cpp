#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ======================================================================================
// CONFIGURACIÓN (CONSTANTES)
// ======================================================================================
const int POBLACION = 1000;          // Base para el cálculo
const double PREVALENCIA = 0.01;     // 1%
const double SENSIBILIDAD = 0.99;    // 99%
const double ESPECIFICIDAD = 0.95;   // 95% (Tasa error sanos = 5%)

// ======================================================================================
// UTILIDADES TUI
// ======================================================================================
void imprimirLinea() { cout << string(70, '-') << endl; }

void imprimirCalculo(string descripcion, string operacion, double resultado) {
    cout << "| " << left << setw(28) << descripcion 
         << " | " << setw(25) << operacion 
         << " = " << right << setw(8) << fixed << setprecision(1) << resultado << " |" << endl;
}

// ======================================================================================
// MAIN
// ======================================================================================
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    // Semilla aleatoria
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // ==================================================================================
    // PARTE 1: DESGLOSE TEÓRICO (EXPLICANDO LOS NÚMEROS)
    // ==================================================================================
    cout << "\n";
    cout << "======================================================================" << endl;
    cout << "       PARTE 1: LA MATEMATICA (EL ARBOL DE PROBABILIDAD)" << endl;
    cout << "======================================================================" << endl;
    cout << "Imaginemos una poblacion exacta de " << POBLACION << " personas.\n" << endl;

    // 1. Desglose de Enfermos vs Sanos
    double teorico_enfermos = POBLACION * PREVALENCIA;
    double teorico_sanos = POBLACION * (1.0 - PREVALENCIA);

    imprimirLinea();
    cout << "| PASO 1: SEPARAR POBLACION (Segun Prevalencia 1%)                   |" << endl;
    imprimirLinea();
    imprimirCalculo("Enfermos Reales", "1000 * 0.01", teorico_enfermos);
    imprimirCalculo("Sanos Reales", "1000 * 0.99", teorico_sanos);
    imprimirLinea();
    cout << "\n";

    // 2. Desglose de los Tests (Verdaderos y Falsos Positivos)
    // Verdaderos Positivos: Enfermos detectados (99% de 10)
    double teorico_verdaderos_pos = teorico_enfermos * SENSIBILIDAD;
    
    // Falsos Positivos: Sanos que dieron error (5% de 990)
    double tasa_falso_positivo = 1.0 - ESPECIFICIDAD;
    double teorico_falsos_pos = teorico_sanos * tasa_falso_positivo;

    double total_positivos_teorico = teorico_verdaderos_pos + teorico_falsos_pos;

    imprimirLinea();
    cout << "| PASO 2: APLICAR EL TEST (Generar Positivos)                        |" << endl;
    imprimirLinea();
    imprimirCalculo("Verdaderos Positivos (VP)", to_string((int)teorico_enfermos) + " * 0.99", teorico_verdaderos_pos);
    imprimirCalculo("Falsos Positivos (FP)", to_string((int)teorico_sanos) + " * 0.05", teorico_falsos_pos);
    imprimirLinea();
    imprimirCalculo("TOTAL POSITIVOS (+)", to_string(teorico_verdaderos_pos).substr(0,3) + " + " + to_string(teorico_falsos_pos).substr(0,4), total_positivos_teorico);
    imprimirLinea();

    // 3. La Fórmula de Bayes Visualizada
    double bayes_resultado = (teorico_verdaderos_pos / total_positivos_teorico) * 100.0;

    cout << "\n";
    cout << "======================================================================" << endl;
    cout << "       PARTE 2: LA FORMULA DE BAYES (EL RESULTADO)" << endl;
    cout << "======================================================================" << endl;
    cout << "Si tu test sale POSITIVO, tu no sabes si eres del grupo VP o FP." << endl;
    cout << "Solo sabes que estas en el grupo de 'TOTAL POSITIVOS'.\n" << endl;

    cout << "Probabilidad = (Casos Favorables) / (Casos Posibles Totales)" << endl;
    cout << "             = (Verdaderos Positivos) / (Verdaderos Pos + Falsos Pos)" << endl;
    
    cout << "\n      " << teorico_verdaderos_pos << endl;
    cout << "P = -----------  =  " << fixed << setprecision(2) << bayes_resultado << "%" << endl;
    cout << "      " << total_positivos_teorico << endl; 
    
    cout << "\nCONCLUSION TEORICA: De cada 100 positivos, solo ~16 estan enfermos." << endl;

    // ==================================================================================
    // PARTE 3: SIMULACIÓN MONTE CARLO (LA PRUEBA DE FUEGO)
    // ==================================================================================
    cout << "\n\n";
    cout << "======================================================================" << endl;
    cout << "       PARTE 3: SIMULACION ESTOCASTICA (Monte Carlo)" << endl;
    cout << "       Generando 1000 pacientes uno por uno..." << endl;
    cout << "======================================================================" << endl;

    int sim_enfermos = 0;
    int sim_sanos = 0;
    int sim_vp = 0; // Verdaderos Positivos
    int sim_fp = 0; // Falsos Positivos

    for(int i=0; i<POBLACION; i++) {
        // A. Estado Real
        bool es_enfermo = dis(gen) < PREVALENCIA;
        
        if (es_enfermo) {
            sim_enfermos++;
            // B. Test (si es enfermo)
            if (dis(gen) < SENSIBILIDAD) sim_vp++;
        } else {
            sim_sanos++;
            // B. Test (si es sano - Error del 5%)
            if (dis(gen) < tasa_falso_positivo) sim_fp++;
        }
    }

    int sim_total_pos = sim_vp + sim_fp;
    double sim_bayes = 0.0;
    if (sim_total_pos > 0) sim_bayes = ((double)sim_vp / sim_total_pos) * 100.0;

    cout << "RESULTADOS OBTENIDOS DEL RANDOM:" << endl;
    imprimirLinea();
    cout << "| METRICA                    | TEORIA (Esperado) | SIMULACION (Real) |" << endl;
    imprimirLinea();
    
    cout << "| Total Enfermos             | " << setw(17) << (int)teorico_enfermos << " | " << setw(17) << sim_enfermos << " |" << endl;
    cout << "| Total Sanos                | " << setw(17) << (int)teorico_sanos << " | " << setw(17) << sim_sanos << " |" << endl;
    imprimirLinea();
    cout << "| Verdaderos Positivos (VP)  | " << setw(17) << fixed << setprecision(1) << teorico_verdaderos_pos << " | " << setw(17) << sim_vp << " |" << endl;
    cout << "| Falsos Positivos (FP)      | " << setw(17) << teorico_falsos_pos << " | " << setw(17) << sim_fp << " |" << endl;
    imprimirLinea();
    cout << "| PROBABILIDAD (BAYES)       | " << setw(16) << bayes_resultado << "% | " << setw(16) << sim_bayes << "% |" << endl;
    imprimirLinea();

    return 0;
}
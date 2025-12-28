#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <cmath>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ======================================================================================
// CONFIGURACIÓN (CONSTANTES)
// ======================================================================================
const double PREVALENCIA = 0.01;     // 1%
const double SENSIBILIDAD = 0.99;    // 99%
const double ESPECIFICIDAD = 0.95;   // 95%
// Tasa de Falso Positivo = 1 - 0.95 = 0.05

// ======================================================================================
// UTILIDADES TUI
// ======================================================================================
void imprimirLinea() { cout << string(100, '-') << endl; }

// --- NUEVA FUNCIÓN: TABLA DE DEFINICIONES ---
void imprimirGlosario(double prev, double sens, double espec) {
    double tasa_fp = 1.0 - espec;
    
    cout << "\n";
    imprimirLinea();
    cout << " 1. DEFINICION DE VARIABLES DEL ESCENARIO" << endl;
    imprimirLinea();
    
    cout << "| " << left << setw(20) << "TERMINO" 
         << " | " << setw(8) << "VALOR" 
         << " | " << "SIGNIFICADO EN LENGUAJE NATURAL" << endl;
    
    imprimirLinea();

    // Fila 1: Prevalencia
    cout << "| " << left << setw(20) << "Prevalencia" 
         << " | " << right << setw(7) << (prev*100) << "%" 
         << " | " << left << "Probabilidad base de tener la enfermedad (1 de cada 100)." << endl;

    // Fila 2: Sensibilidad
    cout << "| " << left << setw(20) << "Sensibilidad" 
         << " | " << right << setw(7) << (sens*100) << "%" 
         << " | " << left << "Si ESTAS ENFERMO, el test te detecta el 99% de las veces." << endl;

    // Fila 3: Especificidad
    cout << "| " << left << setw(20) << "Especificidad" 
         << " | " << right << setw(7) << (espec*100) << "%" 
         << " | " << left << "Si ESTAS SANO, el test dice que estas sano el 95% de las veces." << endl;

    // Fila 4: Falsos Positivos (El dato critico)
    cout << "| " << left << setw(20) << "Falso Positivo" 
         << " | " << right << setw(7) << (tasa_fp*100) << "%" 
         << " | " << left << "Si ESTAS SANO, el test SE EQUIVOCA y da positivo el 5% de veces." << endl;
         
    imprimirLinea();
    cout << "\n";
}

void imprimirFormulaBayes(double prev, double sens, double espec) {
    double tasa_fp = 1.0 - espec;
    
    stringstream ss_num_izq, ss_num_der;
    ss_num_izq << fixed << setprecision(2) << sens;
    ss_num_der << fixed << setprecision(2) << prev;

    stringstream ss_den_izq1, ss_den_der1, ss_den_izq2, ss_den_der2;
    ss_den_izq1 << fixed << setprecision(2) << sens;
    ss_den_der1 << fixed << setprecision(2) << prev;
    ss_den_izq2 << fixed << setprecision(2) << tasa_fp;
    ss_den_der2 << fixed << setprecision(2) << (1.0 - prev);

    string numerador = ss_num_izq.str() + " * " + ss_num_der.str();
    string denominador = "(" + ss_den_izq1.str() + " * " + ss_den_der1.str() + ") + (" + ss_den_izq2.str() + " * " + ss_den_der2.str() + ")";
    
    string parte_izq = "P(E|+) = ";
    string barra = string(denominador.length(), '-');
    int padding_numerador = (denominador.length() - numerador.length()) / 2;
    
    cout << "\n 2. ECUACION DEL TEOREMA DE BAYES" << endl;
    cout << " (Probabilidad de estar Enfermo dado un Test Positivo)\n" << endl;

    cout << string(parte_izq.length() + 3, ' ') << string(padding_numerador, ' ') << "\033[1;36m" << numerador << "\033[0m" << endl;
    cout << "   " << parte_izq << barra << endl;
    cout << string(parte_izq.length() + 3, ' ') << denominador << endl;
    cout << "\n";
}

// ======================================================================================
// MAIN
// ======================================================================================
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    long long POBLACION;

    // 1. INPUT DE USUARIO
    cout << "=== SIMULADOR DE DIAGNOSTICO MEDICO (Monte Carlo vs Bayes) ===" << endl;
    
    do {
        cout << "Ingrese tamano de la poblacion a simular (n): ";
        cin >> POBLACION;
        if (POBLACION <= 0) cout << "Error: Ingrese un numero mayor a 0." << endl;
    } while (POBLACION <= 0);


    // PARTE 1: VISUALIZACIÓN DE DEFINICIONES Y FÓRMULA
    imprimirGlosario(PREVALENCIA, SENSIBILIDAD, ESPECIFICIDAD);
    imprimirFormulaBayes(PREVALENCIA, SENSIBILIDAD, ESPECIFICIDAD);

    // Cálculos Teóricos
    double teorico_enfermos = POBLACION * PREVALENCIA;
    double teorico_sanos = POBLACION * (1.0 - PREVALENCIA);
    double teorico_verdaderos_pos = teorico_enfermos * SENSIBILIDAD;
    double tasa_falso_positivo = 1.0 - ESPECIFICIDAD;
    double teorico_falsos_pos = teorico_sanos * tasa_falso_positivo;
    double total_positivos_teorico = teorico_verdaderos_pos + teorico_falsos_pos;
    double bayes_resultado = (teorico_verdaderos_pos / total_positivos_teorico) * 100.0;
    
    cout << " RESULTADO MATEMATICO (TEORICO): " << fixed << setprecision(4) << bayes_resultado << "%" << endl;

    // PARTE 2: SIMULACIÓN MONTE CARLO
    cout << "\n\n";
    imprimirLinea();
    cout << " 3. EJECUTANDO SIMULACION CON " << POBLACION << " PACIENTES..." << endl;
    imprimirLinea();

    long long sim_enfermos = 0;
    long long sim_sanos = 0;
    long long sim_vp = 0; 
    long long sim_fp = 0; 

    for(long long i=0; i<POBLACION; i++) {
        bool es_enfermo = dis(gen) < PREVALENCIA;
        
        if (es_enfermo) {
            sim_enfermos++;
            if (dis(gen) < SENSIBILIDAD) sim_vp++;
        } else {
            sim_sanos++;
            if (dis(gen) < tasa_falso_positivo) sim_fp++;
        }
    }

    long long sim_total_pos = sim_vp + sim_fp;
    double sim_bayes = 0.0;
    if (sim_total_pos > 0) sim_bayes = ((double)sim_vp / sim_total_pos) * 100.0;

    // TABLA DE RESULTADOS
    cout << " COMPARATIVA FINAL:" << endl;
    imprimirLinea();
    
    cout << "| " << left << setw(28) << "METRICA" 
         << " | " << setw(34) << "ORIGEN (N * Prob)" 
         << " | " << setw(12) << "TEORICO" 
         << " | " << setw(12) << "SIMULADO" << " |" << endl;
    imprimirLinea();
    
    cout << "| " << left << setw(28) << "Total Enfermos" 
         << " | " << right << setw(12) << POBLACION << " * " << left << setw(19) << PREVALENCIA
         << " | " << right << setw(12) << (long long)teorico_enfermos 
         << " | " << right << setw(12) << sim_enfermos << " |" << endl;

    cout << "| " << left << setw(28) << "Total Sanos" 
         << " | " << right << setw(12) << POBLACION << " * " << left << setw(19) << (1.0 - PREVALENCIA)
         << " | " << right << setw(12) << (long long)teorico_sanos 
         << " | " << right << setw(12) << sim_sanos << " |" << endl;

    imprimirLinea();

    cout << "| " << left << setw(28) << "Verdaderos Positivos (VP)" 
         << " | " << right << setw(12) << (long long)teorico_enfermos << " * " << left << setw(19) << SENSIBILIDAD
         << " | " << right << setw(12) << fixed << setprecision(1) << teorico_verdaderos_pos 
         << " | " << right << setw(12) << sim_vp << " |" << endl;

    cout << "| " << left << setw(28) << "Falsos Positivos (FP)" 
         << " | " << right << setw(12) << (long long)teorico_sanos << " * " << left << setw(19) << tasa_falso_positivo
         << " | " << right << setw(12) << fixed << setprecision(1) << teorico_falsos_pos 
         << " | " << right << setw(12) << sim_fp << " |" << endl;

    imprimirLinea();
    
    cout << "| " << left << setw(28) << "PROBABILIDAD (BAYES)" 
         << " | " << right << setw(34) << "VP / (VP + FP)   " 
         << " | " << right << setw(11) << bayes_resultado << "%" 
         << " | " << right << setw(11) << sim_bayes << "%" << " |" << endl;
    
    imprimirLinea();
    
    double error = abs(bayes_resultado - sim_bayes);
    cout << "\nDiferencia (Error Estocastico): " << error << "%" << endl;

    return 0;
}
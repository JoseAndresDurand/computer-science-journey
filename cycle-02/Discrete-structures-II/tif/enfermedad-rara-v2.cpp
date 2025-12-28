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
// CONFIGURACIÓN DEL ESCENARIO (CONSTANTES)
// ======================================================================================
// Prevalencia del 1% (0.01)
const double PROB_ENFERMEDAD = 0.01; 
// Sensibilidad del 99% (Si tienes la enfermedad, da positivo)
const double SENSIBILIDAD = 0.99;    
// Especificidad del 95% (Si estás sano, da negativo) -> Falsos Positivos = 5%
const double ESPECIFICIDAD = 0.95;   

// ======================================================================================
// HERRAMIENTAS DE TUI (INTERFAZ VISUAL)
// ======================================================================================
void imprimirSeparador() {
    cout << "+--------------------------------------------------------------+" << endl;
}

void imprimirEncabezado(string titulo) {
    imprimirSeparador();
    int espacios = (62 - titulo.length()) / 2;
    cout << "|" << string(espacios, ' ') << titulo << string(62 - espacios - titulo.length(), ' ') << "|" << endl;
    imprimirSeparador();
}

void imprimirFila(string etiqueta, double valor, string unidad = "") {
    cout << "| " << left << setw(35) << etiqueta 
         << " | " << right << setw(15) << fixed << setprecision(2) << valor << unidad << "    |" << endl;
}

void imprimirFilaEntera(string etiqueta, int valor) {
    cout << "| " << left << setw(35) << etiqueta 
         << " | " << right << setw(15) << valor << "        |" << endl;
}

// ======================================================================================
// MAIN
// ======================================================================================
int main() {
    // Configurar UTF-8 para Windows (para ver acentos si es necesario)
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    // 1. CÁLCULO DE BAYES (TEÓRICO)
    // Desglosamos la fórmula P(Enfermo|Positivo)
    double p_enfermo = PROB_ENFERMEDAD;                 // 0.01
    double p_sano = 1.0 - PROB_ENFERMEDAD;              // 0.99
    
    double p_pos_dado_enfermo = SENSIBILIDAD;           // 0.99
    double p_pos_dado_sano = 1.0 - ESPECIFICIDAD;       // 0.05 (Falso Positivo)

    // Numerador: Probabilidad de ser un Verdadero Positivo
    double numerador = p_pos_dado_enfermo * p_enfermo;

    // Denominador: Probabilidad Total de dar Positivo (Verdaderos + Falsos)
    double denominador = (p_pos_dado_enfermo * p_enfermo) + (p_pos_dado_sano * p_sano);

    double probabilidad_bayesiana = (numerador / denominador) * 100.0;

    // 2. VISUALIZACIÓN DE "FRECUENCIAS NATURALES"
    // Para entenderlo mejor, proyectamos esto a una población hipotética de 10,000 personas
    int poblacion_hipotetica = 10000;
    int total_enfermos = poblacion_hipotetica * p_enfermo;          // 100 personas
    int total_sanos = poblacion_hipotetica * p_sano;                // 9900 personas
    
    int verdaderos_positivos = total_enfermos * SENSIBILIDAD;       // ~99 personas
    int falsos_positivos = total_sanos * (1.0 - ESPECIFICIDAD);     // ~495 personas !!!
    int total_positivos = verdaderos_positivos + falsos_positivos;  // ~594 personas

    // ----------------------------------------------------------------------------------
    // FASE 1: MOSTRAR LA MATEMÁTICA DETRÁS DEL ESCENARIO
    // ----------------------------------------------------------------------------------
    cout << "\n";
    imprimirEncabezado("ANALISIS MATEMATICO DEL TEST");
    cout << "| Contexto: Prevalencia baja (1%) y Tasa de Falsos Pos (5%)    |" << endl;
    imprimirSeparador();
    imprimirFila("Probabilidad de estar Enfermo", p_enfermo * 100, "%");
    imprimirFila("Probabilidad de estar Sano", p_sano * 100, "%");
    imprimirSeparador();
    
    cout << "\nIMAGINEMOS UNA POBLACION DE " << poblacion_hipotetica << " PERSONAS:" << endl;
    imprimirSeparador();
    imprimirFilaEntera("1. Total de Enfermos (1%)", total_enfermos);
    imprimirFilaEntera("2. Total de Sanos (99%)", total_sanos);
    imprimirSeparador();
    cout << "| APLICANDO EL TEST A TODOS:                                   |" << endl;
    imprimirFilaEntera("3. Enfermos con Test POSITIVO", verdaderos_positivos);
    imprimirFilaEntera("4. Sanos con Test POSITIVO (Error)", falsos_positivos);
    imprimirSeparador();
    imprimirFilaEntera("TOTAL DE GENTE CON TEST POSITIVO", total_positivos);
    imprimirSeparador();
    
    cout << "\n>>> ANALISIS: De las " << total_positivos << " personas con el papel 'POSITIVO' en la mano," << endl;
    cout << ">>> SOLO " << verdaderos_positivos << " estan realmente enfermas." << endl;
    cout << ">>> " << falsos_positivos << " estan sanas y asustadas por error." << endl;

    // ----------------------------------------------------------------------------------
    // FASE 2: SIMULACIÓN DE TU PACIENTE ÚNICO
    // ----------------------------------------------------------------------------------
    cout << "\n\n";
    imprimirEncabezado("SIMULACION DE UN PACIENTE REAL");
    cout << "| Generando estado aleatorio del paciente...                   |" << endl;
    
    // A. Generar Estado Real
    bool paciente_esta_enfermo = dis(gen) < PROB_ENFERMEDAD;
    string estado_real_str = paciente_esta_enfermo ? "ENFERMO (REAL)" : "SANO (REAL)";

    // B. Generar Resultado del Test
    bool test_positivo = false;
    if (paciente_esta_enfermo) {
        test_positivo = dis(gen) < SENSIBILIDAD;
    } else {
        test_positivo = dis(gen) < (1.0 - ESPECIFICIDAD); // 5% chance de error
    }

    string resultado_test_str = test_positivo ? "[ + ] POSITIVO" : "[ - ] NEGATIVO";

    // C. Mostrar Resultado
    imprimirSeparador();
    cout << "| EL PACIENTE RECIBE SU SOBRE...                               |" << endl;
    cout << "| Resultado del Test : " << left << setw(38) << resultado_test_str << "|" << endl;
    imprimirSeparador();

    if (test_positivo) {
        cout << "\n[!] ALERTA: El test dio POSITIVO." << endl;
        cout << "Segun el Teorema de Bayes calculado arriba, la probabilidad" << endl;
        cout << "de que este paciente tenga la enfermedad es:" << endl;
        
        cout << "\n   " << fixed << setprecision(2) << probabilidad_bayesiana << "%" << endl;
        
        cout << "\n(Aunque el test es 99% preciso, es mas probable que sea Falso Positivo)" << endl;
    } else {
        cout << "\n[OK] El test dio NEGATIVO." << endl;
        cout << "La probabilidad de estar sano es extremadamente alta (>99.9%)." << endl;
    }

    // D. Revelación (La Verdad)
    cout << "\n" << string(64, '=') << endl;
    cout << " REVELACION DE LA VERDAD (GOD MODE)" << endl;
    cout << " Estado Real del Paciente: " << estado_real_str << endl;
    
    if (test_positivo && !paciente_esta_enfermo) {
        cout << " DIAGNOSTICO: FALSO POSITIVO (El caso mas comun en Bayes)" << endl;
    } else if (test_positivo && paciente_esta_enfermo) {
        cout << " DIAGNOSTICO: VERDADERO POSITIVO (Detectado correctamente)" << endl;
    } else if (!test_positivo && paciente_esta_enfermo) {
        cout << " DIAGNOSTICO: FALSO NEGATIVO (Peligroso, pero raro)" << endl;
    } else {
        cout << " DIAGNOSTICO: VERDADERO NEGATIVO (Sano y tranquilo)" << endl;
    }
    cout << string(64, '=') << endl;

    return 0;
}
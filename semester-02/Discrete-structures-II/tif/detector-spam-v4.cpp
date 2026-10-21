#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Configuración para Windows
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class NaiveBayesClassifier {
private:
    map<string, int> mapaSpam; 
    map<string, int> mapaHam;
    set<string> vocabulario;

    int totalPalabrasSpam = 0;
    int totalPalabrasHam = 0;
    int totalMensajesSpam = 0;
    int totalMensajesHam = 0;

    // --- CORRECCIÓN CRÍTICA DE LA Ñ ---
    string limpiarPalabra(string palabra) {
        string limpia = "";
        for (unsigned char c : palabra) { // <--- CLAVE: USAR UNSIGNED CHAR
            // 1. Si es alfanumérico estándar (a-z, 0-9)
            // 2. O SI ES UN BYTE EXTENDIDO (> 127): Esto captura las partes de la ñ, á, é, etc. en UTF-8
            if (isalnum(c) || c > 127) { 
                // Solo aplicamos tolower a los caracteres ASCII estándar
                if (c < 128) {
                    limpia += tolower(c);
                } else {
                    limpia += c; // Los caracteres especiales se agregan tal cual
                }
            }
        }
        return limpia;
    }

    void dibujarBarra(double score, double maxScore, double minScore) {
        int bloques = 0;
        double rango = maxScore - minScore;
        if (rango < 0.1) rango = 1.0; 
        
        double normalizado = (score - minScore) / rango; 
        bloques = (int)(normalizado * 30);
        
        if (bloques > 30) bloques = 30;
        if (bloques < 1) bloques = 1;

        cout << "[";
        for(int i=0; i<bloques; i++) cout << "#";
        for(int i=bloques; i<30; i++) cout << " ";
        cout << "] " << fixed << setprecision(4) << score;
    }

public:
    void train(string texto, bool esSpam) {
        if (esSpam) totalMensajesSpam++;
        else totalMensajesHam++;

        stringstream ss(texto);
        string palabra;
        while (ss >> palabra) {
            string word = limpiarPalabra(palabra);
            if (word.length() > 0) {
                vocabulario.insert(word);
                if (esSpam) {
                    mapaSpam[word]++;
                    totalPalabrasSpam++;
                } else {
                    mapaHam[word]++;
                    totalPalabrasHam++;
                }
            }
        }
    }

    string predict(string texto) {
        int totalMensajes = totalMensajesSpam + totalMensajesHam;
        double logPriorSpam = log((double)totalMensajesSpam / totalMensajes);
        double logPriorHam = log((double)totalMensajesHam / totalMensajes);

        double scoreSpam = logPriorSpam;
        double scoreHam = logPriorHam;

        string formulaSpamStr = "Score(Spam) = " + to_string(logPriorSpam).substr(0,6);
        string formulaHamStr =  "Score(Ham)  = " + to_string(logPriorHam).substr(0,6);

        stringstream ss(texto);
        string palabra;

        cout << "\n" << string(100, '=') << endl;
        cout << "  ANALISIS DETALLADO (Tokens identificados)" << endl;
        cout << string(100, '-') << endl;
        
        cout << left << setw(20) << "TOKEN" 
             << " | " << setw(12) << "Log(P|Spam)" 
             << " | " << setw(12) << "Log(P|Ham)" << endl;
        cout << string(100, '-') << endl;

        cout << left << setw(20) << "[PRIOR]" 
             << " | " << setw(12) << setprecision(4) << logPriorSpam
             << " | " << setw(12) << setprecision(4) << logPriorHam << endl;

        while (ss >> palabra) {
            string word = limpiarPalabra(palabra);
            if (word.length() == 0) continue;

            long vocabSize = vocabulario.size();
            // Suavizado de Laplace: (conteo + 1) / (total + vocabulario)
            double probSpam = (double)(mapaSpam[word] + 1) / (totalPalabrasSpam + vocabSize);
            double probHam = (double)(mapaHam[word] + 1) / (totalPalabrasHam + vocabSize);

            double logSpam = log(probSpam);
            double logHam = log(probHam);

            scoreSpam += logSpam;
            scoreHam += logHam;

            formulaSpamStr += " + (" + to_string(logSpam).substr(0,6) + ")";
            formulaHamStr  += " + (" + to_string(logHam).substr(0,6) + ")";

            cout << left << setw(20) << word 
                 << " | " << setw(12) << setprecision(4) << logSpam
                 << " | " << setw(12) << setprecision(4) << logHam << endl;
        }

        cout << string(100, '=') << endl;
        
        cout << "\n[FORMULA MATEMATICA APLICADA]" << endl;
        cout << formulaSpamStr << "\n   = " << scoreSpam << endl << endl;
        cout << formulaHamStr << "\n   = " << scoreHam << endl;

        cout << "\n[BENCHMARK]" << endl;
        cout << "SPAM : "; 
        dibujarBarra(scoreSpam, max(scoreSpam, scoreHam), min(scoreSpam, scoreHam));
        cout << endl;
        
        cout << "HAM  : ";
        dibujarBarra(scoreHam, max(scoreSpam, scoreHam), min(scoreSpam, scoreHam));
        cout << endl;
        
        cout << "\n>>> VEREDICTO FINAL: ";
        
        // Umbral de diferencia para evitar empates técnicos
        double diferencia = abs(scoreSpam - scoreHam);
        
        if (diferencia < 0.0001) {
             cout << "INCIERTO (Empate tecnico - Faltan datos)" << endl;
             return "INCIERTO";
        } else if (scoreSpam > scoreHam) {
            cout << "ES SPAM !!!" << endl;
            return "SPAM";
        } else {
            cout << "ES LEGITIMO (HAM)" << endl;
            return "HAM";
        }
    }
};

int main() {
    // Configuración UTF-8 para consola Windows
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001); 
    #endif

    NaiveBayesClassifier clasificador;

    cout << "Cargando cerebro artificial (Entrenando)..." << endl;
    
    // --- DATASET REFORZADO (Para corregir tu caso de "viaje descuento") ---
    
    // 1. SPAM CLÁSICO (Estafas)
    clasificador.train("oferta increíble gana dinero rápido gratis", true);
    clasificador.train("premio urgente click aquí dinero fácil", true);
    clasificador.train("compra ahora descuento exclusivo bitcoin", true);
    clasificador.train("felicidades ganaste lotería reclama premio", true);
    
    // 2. SPAM TURÍSTICO / COMERCIAL (Lo que falló antes)
    // Aquí enseñamos que "viaja", "descuento", "paquete", "increíble" son malos
    clasificador.train("viaja gratis descuento increíble crucero", true);
    clasificador.train("paquete turístico todo incluido oferta limitada", true);
    clasificador.train("vuelo barato promoción única 50% descuento", true);
    clasificador.train("vacaciones soñadas precio regalo reserva ya", true);

    // 3. HAM (Legítimo)
    clasificador.train("reunión de proyecto mañana en la oficina", false);
    clasificador.train("hola mamá cómo estás te extraño", false);
    clasificador.train("invitación a la cena de graduación", false);
    clasificador.train("documentos adjuntos para el reporte mensual", false);
    clasificador.train("recordatorio cita dentista martes", false);
    clasificador.train("confirmación de pago de servicios luz agua", false);
    clasificador.train("planificación viaje familiar verano", false); // Un "viaje" legítimo para dar contexto

    string entrada;
    cout << "--- CLASIFICADOR BAYESIANO V3.0 (Dataset Reforzado) ---" << endl;
    
    while(true){
        cout << "\nIngrese asunto (o 'salir'): ";
        getline(cin, entrada);
        if(entrada == "salir") break;
        clasificador.predict(entrada);
    }

    return 0;
}
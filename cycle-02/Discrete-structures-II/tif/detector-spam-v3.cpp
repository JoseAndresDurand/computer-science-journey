#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Bloque específico para configurar la consola de Windows a UTF-8
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

    // --- CORRECCIÓN CRÍTICA PARA Ñ Y TILDES ---
    // El problema anterior era que borrábamos bytes desconocidos.
    // Ahora aceptamos alfanuméricos Y cualquier byte "extraño" (mayor a 127)
    // que suelen ser partes de la ñ o tildes en UTF-8.
    string limpiarPalabra(string palabra) {
        string limpia = "";
        for (unsigned char c : palabra) { // Usamos unsigned char para evaluar valor numérico
            // Si es letra/número O es un caracter especial (ñ, tildes tienen valores altos > 127)
            // Y NO es un signo de puntuación básico que queramos borrar
            if (isalnum(c) || c > 127) { 
                // tolower de C++ estándar no baja tildes, pero al menos no las borra.
                // Para ñ minúscula/mayúscula perfecto se requiere librerías externas,
                // pero esto mantendrá la palabra legible.
                limpia += tolower(c); 
            }
        }
        return limpia;
    }

    void dibujarBarra(double score, double maxScore, double minScore) {
        // Ajuste visual para normalizar barras de logaritmos negativos
        int bloques = 0;
        double rango = maxScore - minScore;
        if (rango < 0.1) rango = 1.0; // Evitar division por cero si son iguales
        
        // Mapear el score a una escala de 0 a 30 caracteres
        // Score más alto (menos negativo) = Barra más larga
        double normalizado = (score - minScore) / rango; 
        bloques = (int)(normalizado * 30);
        
        // Corrección visual: si es el ganador, asegurar que se vea lleno
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

        // Strings para construir la visualización de la fórmula
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
            double probSpam = (double)(mapaSpam[word] + 1) / (totalPalabrasSpam + vocabSize);
            double probHam = (double)(mapaHam[word] + 1) / (totalPalabrasHam + vocabSize);

            double logSpam = log(probSpam);
            double logHam = log(probHam);

            scoreSpam += logSpam;
            scoreHam += logHam;

            // Agregamos el valor a la cadena de texto de la fórmula
            // Usamos concatenación simple para mostrar la suma
            formulaSpamStr += " + (" + to_string(logSpam).substr(0,6) + ")";
            formulaHamStr  += " + (" + to_string(logHam).substr(0,6) + ")";

            cout << left << setw(20) << word 
                 << " | " << setw(12) << setprecision(4) << logSpam
                 << " | " << setw(12) << setprecision(4) << logHam << endl;
        }

        cout << string(100, '=') << endl;
        
        // --- VISUALIZACIÓN DE LA FÓRMULA ---
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
        if (scoreSpam > scoreHam) {
            cout << "ES SPAM !!!" << endl;
            return "SPAM";
        } else {
            cout << "ES LEGITIMO (HAM)" << endl;
            return "HAM";
        }
    }
};

int main() {
    // --- CONFIGURACIÓN CRÍTICA PARA WINDOWS ---
    // Esto fuerza a la consola a usar la página de códigos UTF-8 (CP 65001)
    // Sin esto, la ñ y tildes se ven mal o se borran.
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001); 
    #endif

    NaiveBayesClassifier clasificador;

    // Entrenamos con tildes y ñ para probar el soporte
    clasificador.train("reunión mañana urgente oficina", false); // Ham
    clasificador.train("ganar dinero rápido oferta", true);      // Spam
    clasificador.train("proyecto pendiente revisar", false);     // Ham
    clasificador.train("lotería premio exclusivo", true);        // Spam
    
    // Frase para forzar conflicto
    // "reunión" y "mañana" son Ham. "urgente" y "dinero" son Spam (pero no entrené dinero en este mini set)
    // Vamos a ver qué pasa.
    
    string entrada;
    cout << "--- CLASIFICADOR BAYESIANO (Soporte UTF-8) ---" << endl;
    
    while(true){
        cout << "\nIngrese texto (o 'salir'): ";
        getline(cin, entrada);
        if(entrada == "salir") break;
        clasificador.predict(entrada);
    }

    return 0;
}
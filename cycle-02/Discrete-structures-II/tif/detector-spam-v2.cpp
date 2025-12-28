#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip> // CRUCIAL: Para el diseño de tablas (TUI)

using namespace std;

// ======================================================================================
// CLASE: NaiveBayesClassifier
// ======================================================================================
class NaiveBayesClassifier {
private:
    map<string, int> mapaSpam; 
    map<string, int> mapaHam;
    set<string> vocabulario;

    int totalPalabrasSpam = 0;
    int totalPalabrasHam = 0;
    int totalMensajesSpam = 0;
    int totalMensajesHam = 0;

    // --- MEJORA 1: LIMPIEZA COMPATIBLE CON Ñ Y TILDES ---
    // En lugar de isalnum(), definimos qué borrar manualmente.
    // Esto permite que caracteres UTF-8 (como ñ, á, é) pasen el filtro.
    string limpiarPalabra(string palabra) {
        string limpia = "";
        string prohibidos = ".,;:'\"!¡?¿()[]{}*-+"; // Signos a eliminar
        
        for (char c : palabra) {
            // Si el caracter NO está en la lista de prohibidos, lo guardamos
            if (prohibidos.find(c) == string::npos) {
                // tolower funciona bien con ASCII, con ñ a veces falla en windows 
                // pero al menos no borrará la letra.
                limpia += tolower(c); 
            }
        }
        return limpia;
    }

    // Función auxiliar para dibujar barras de carga en consola
    void dibujarBarra(double score, double maxScore, double minScore, string color) {
        // Normalizamos el score negativo a una escala positiva visual (0 a 20 bloques)
        // Logaritmos: -50 es "peor" que -10. 
        // Esta lógica es solo para fines visuales aproximados en consola.
        int ancho = 50;
        double rango = maxScore - minScore;
        if (rango == 0) rango = 1; // Evitar división por cero
        
        double porcentaje = 1.0 - ((maxScore - score) / abs(minScore)); 
        // Simplificación visual: Solo mostramos longitud relativa
        
        cout << "[";
        int bloques = 20; 
        if (score > -1000) bloques = 20 + (int)(score/5); // Ajuste visual rápido para logs negativos
        if (bloques < 0) bloques = 1;
        if (bloques > 30) bloques = 30;

        for(int i=0; i<bloques; i++) cout << "#";
        for(int i=bloques; i<30; i++) cout << " ";
        cout << "] " << fixed << setprecision(4) << score << endl;
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

        stringstream ss(texto);
        string palabra;
        vector<string> palabrasProcesadas;

        // --- MEJORA 2: TUI VISUALIZACIÓN DE FÓRMULA ---
        cout << "\n" << string(90, '=') << endl;
        cout << "  DESGLOSE MATEMATICO (Teorema de Bayes: Suma de Logaritmos)" << endl;
        cout << string(90, '-') << endl;
        
        // Encabezados de la Tabla
        cout << left << setw(15) << "TOKEN (Palabra)" 
             << " | " << setw(12) << "P(w|Spam)" << setw(12) << "Log(Spam)" 
             << " | " << setw(12) << "P(w|Ham)" << setw(12) << "Log(Ham)" << endl;
        cout << string(90, '-') << endl;

        // Imprimir los Priors (Probabilidad inicial antes de leer palabras)
        cout << left << setw(15) << "[PRIOR PROB]" 
             << " | " << setw(12) << "---" << setw(12) << setprecision(4) << logPriorSpam
             << " | " << setw(12) << "---" << setw(12) << setprecision(4) << logPriorHam << endl;

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

            // Imprimir Fila de la Tabla
            cout << left << setw(15) << word.substr(0,14) // Cortar palabra si es muy larga
                 << " | " << setw(12) << setprecision(6) << probSpam << setw(12) << setprecision(4) << logSpam
                 << " | " << setw(12) << setprecision(6) << probHam << setw(12) << setprecision(4) << logHam << endl;
        }
        cout << string(90, '=') << endl;

        // --- MEJORA 3: BENCHMARK Y RESULTADO FINAL ---
        cout << "\n   RESULTADO DEL BENCHMARK (Score mas cercano a 0 gana)" << endl;
        cout << "   ----------------------------------------------------" << endl;
        
        cout << "   SPAM : "; 
        dibujarBarra(scoreSpam, max(scoreSpam, scoreHam), min(scoreSpam, scoreHam), "RED");
        
        cout << "   HAM  : ";
        dibujarBarra(scoreHam, max(scoreSpam, scoreHam), min(scoreSpam, scoreHam), "GREEN");
        
        cout << "\n   >>> VEREDICTO FINAL: ";
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
    // Configurar locale para intentar imprimir caracteres especiales (depende de la consola)
    setlocale(LC_ALL, ""); 

    NaiveBayesClassifier clasificador;

    cout << "Entrenando modelo..." << endl;
    // Datos de entrenamiento incluyendo tildes y ñ para probar
    clasificador.train("Oferta increíble gana dinero rápido gratis", true);
    clasificador.train("premio urgente click aquí dinero fácil", true);
    clasificador.train("compra ahora descuento exclusivo bitcoin", true);
    clasificador.train("Reunión de proyecto mañana en la oficina", false); // "mañana" incluido
    clasificador.train("Hola mamá cómo estás te extraño", false);
    clasificador.train("invitación a la cena de graduación año nuevo", false); // "año" incluido

    string entrada;
    while (true) {
        cout << "\n\nIngrese asunto (ej: 'reunión mañana urgente') o 'salir': ";
        getline(cin, entrada);
        if (entrada == "salir") break;
        clasificador.predict(entrada);
    }

    return 0;
}
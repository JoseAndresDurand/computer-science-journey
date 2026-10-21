#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>  // Para separar palabras (tokenizar)
#include <cmath>    // Para funciones matemáticas (log)
#include <algorithm>// Para transform (minúsculas)

using namespace std;

// ======================================================================================
// CLASE: NaiveBayesClassifier
// ======================================================================================
class NaiveBayesClassifier {
private:
    // STL MAP: Diccionario clave-valor.
    // Clave: La palabra (string)
    // Valor: Cuántas veces aparece (int)
    map<string, int> mapaSpam; 
    map<string, int> mapaHam;  // Ham = Correo Legítimo

    // STL SET: Conjunto de elementos únicos.
    // Lo usamos para saber cuántas palabras ÚNICAS existen en total (Vocabulario |V|)
    set<string> vocabulario;

    // Contadores generales para las probabilidades a priori P(Clase)
    int totalPalabrasSpam = 0;
    int totalPalabrasHam = 0;
    int totalMensajesSpam = 0;
    int totalMensajesHam = 0;

    // --- MÉTODO PRIVADO: LIMPIEZA DE TEXTO ---
    // Convierte a minúsculas y quita puntuación básica (.,¡!)
    string limpiarPalabra(string palabra) {
        string limpia = "";
        for (char c : palabra) {
            // Si es letra o número, lo pasamos a minúscula y lo guardamos
            if (isalnum(c)) {
                limpia += tolower(c);
            }
        }
        return limpia;
    }

public:
    // --- MÉTODO PÚBLICO: ENTRENAMIENTO (TRAIN) ---
    // Alimenta al modelo con ejemplos conocidos
    void train(string texto, bool esSpam) {
        if (esSpam) totalMensajesSpam++;
        else totalMensajesHam++;

        stringstream ss(texto); // Stream para romper el texto en palabras
        string palabra;

        while (ss >> palabra) {
            string word = limpiarPalabra(palabra);
            
            if (word.length() > 0) { // Ignorar cadenas vacías
                vocabulario.insert(word); // Se añade al vocabulario global (Set no permite duplicados)

                if (esSpam) {
                    mapaSpam[word]++; // Aumenta frecuencia en mapa Spam
                    totalPalabrasSpam++;
                } else {
                    mapaHam[word]++;  // Aumenta frecuencia en mapa Ham
                    totalPalabrasHam++;
                }
            }
        }
    }

    // --- MÉTODO PÚBLICO: PREDICCIÓN (PREDICT) ---
    // Aplica el Teorema de Bayes con Logaritmos y Laplace
    string predict(string texto) {
        // 1. Probabilidad A Priori (Prior Probability)
        // P(Spam) = TotalSpam / TotalMensajes
        // Usamos logaritmos: log(A/B) = log(A) - log(B)
        int totalMensajes = totalMensajesSpam + totalMensajesHam;
        
        double scoreSpam = log((double)totalMensajesSpam / totalMensajes);
        double scoreHam = log((double)totalMensajesHam / totalMensajes);

        // Tokenizamos el texto nuevo para analizar palabra por palabra
        stringstream ss(texto);
        string palabra;

        cout << "\n--- DESGLOSE MATEMATICO (Debug) ---" << endl;
        
        while (ss >> palabra) {
            string word = limpiarPalabra(palabra);
            if (word.length() == 0) continue;

            // 2. Verosimilitud (Likelihood) con SUAVIZADO DE LAPLACE
            // Fórmula: P(w|Clase) = (Conteo(w) + 1) / (TotalPalabrasClase + |Vocabulario|)
            // El "+1" en el numerador y "+|V|" en el denominador es el Suavizado.
            
            long vocabSize = vocabulario.size();

            // Para SPAM
            // Si la palabra no existe en el mapa, el operador [] devuelve 0 por defecto. Útil.
            double probPalabraSpam = (double)(mapaSpam[word] + 1) / (totalPalabrasSpam + vocabSize);
            
            // Para HAM
            double probPalabraHam = (double)(mapaHam[word] + 1) / (totalPalabrasHam + vocabSize);

            // 3. Suma de Logaritmos (Evita Underflow)
            // Score = log(P_Prior) + log(P_w1) + log(P_w2) ...
            scoreSpam += log(probPalabraSpam);
            scoreHam += log(probPalabraHam);

            // Imprimimos detalle para entender qué pasa
            cout << "Palabra: '" << word << "'" << endl;
            cout << "   -> P('" << word << "'|Spam) = " << probPalabraSpam << " (Log: " << log(probPalabraSpam) << ")" << endl;
            cout << "   -> P('" << word << "'|Ham)  = " << probPalabraHam << " (Log: " << log(probPalabraHam) << ")" << endl;
        }

        cout << "-----------------------------------" << endl;
        cout << "SCORE FINAL SPAM: " << scoreSpam << endl;
        cout << "SCORE FINAL HAM:  " << scoreHam << endl;

        // 4. Regla de Decisión (MAP - Maximum A Posteriori)
        // Quien tenga el score más alto (menos negativo), gana.
        if (scoreSpam > scoreHam) {
            return "ES SPAM (Correo Basura)";
        } else {
            return "ES LEGITIMO (Correo Normal)";
        }
    }
};

// ======================================================================================
// MAIN: Flujo de Ejecución
// ======================================================================================
int main() {
    NaiveBayesClassifier clasificador;

    cout << "Inicializando Sistema de Inteligencia Artificial..." << endl;
    cout << "Entrenando modelo Naive Bayes..." << endl;

    // --- FASE 1: ENTRENAMIENTO (Datos Quemados) ---
    // Enseñamos al modelo qué es Spam
    clasificador.train("Oferta increible gana dinero rapido gratis", true);
    clasificador.train("premio urgente click aqui dinero facil", true);
    clasificador.train("compra ahora descuento exclusivo bitcoin", true);
    clasificador.train("felicidades ganaste loteria reclama premio", true);

    // Enseñamos al modelo qué es Ham (Legítimo)
    clasificador.train("Reunion de proyecto mañana en la oficina", false);
    clasificador.train("Hola mama como estas te extraño", false);
    clasificador.train("invitacion a la cena de graduacion de la universidad", false);
    clasificador.train("documentos adjuntos para el reporte mensual", false);
    clasificador.train("recordatorio cita dentista", false);

    cout << "Entrenamiento completado." << endl;
    cout << "=========================================" << endl;

    // --- FASE 2: PRUEBA (Interacción con Usuario) ---
    string entradaUsuario;
    
    while (true) {
        cout << "\nIngrese el ASUNTO del correo para analizar (o 'salir'): ";
        getline(cin, entradaUsuario);

        if (entradaUsuario == "salir") break;

        string resultado = clasificador.predict(entradaUsuario);
        
        cout << "\n>>> CLASIFICACION DEL MODELO: " << resultado << " <<<" << endl;
        cout << "=========================================" << endl;
    }

    return 0;
}
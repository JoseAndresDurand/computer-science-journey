#include <iostream>
using namespace std;

// 1. ALIAS DE TIPO (Para no escribir punteros feos)
// -----------------------------------------------------------
// RETO 1: Define 'FiltroAudio' como un puntero a función que recibe int y devuelve int.
// Usa la sintaxis moderna 'using' o la clásica 'typedef'.

// TU CÓDIGO AQUÍ:
// using FiltroAudio = _________________________; 
using FiltroAudio = int (*)(int);

// Funciones de audio
int subirVolumen(int n) { return n + 10; }
int bajarVolumen(int n) { return n - 5; }
int duplicar(int n) { return n * 2; }


// 2. ESTRUCTURA
// -----------------------------------------------------------
struct Modulo {
    const char* nombre;
    
    // RETO 2: Usa el alias 'FiltroAudio' para declarar el miembro 'accion'.
    // Mira qué limpio queda comparado con el reto anterior.
    
    // TU CÓDIGO AQUÍ:
    // ____________ accion;
    FiltroAudio accion;
};


int main() {
    // 3. CREANDO EL RACK (Array de Objetos)
    // -----------------------------------------------------------
    // Vamos a crear una cadena de 3 efectos
    const int NUM_EFECTOS = 3;
    Modulo rack[NUM_EFECTOS];

    // Configuración manual del rack
    rack[0].nombre = "Pre-Amplificador";
    rack[0].accion = subirVolumen; // +10

    rack[1].nombre = "Potencia";
    // RETO 3: Asigna la función 'duplicar' al segundo módulo
    // TU CÓDIGO AQUÍ:
    // rack[1].accion = ____________;
    rack[1].accion = duplicar;

    rack[2].nombre = "Atenuador";
    // RETO 4: Asigna la función 'bajarVolumen' al tercer módulo
    // TU CÓDIGO AQUÍ:
    // rack[2].accion = ____________;
    rack[2].accion = bajarVolumen;

    // 4. PROCESAMIENTO EN CADENA (El Bucle Principal)
    // -----------------------------------------------------------
    int senial = 50;
    cout << "Senial Inicial: " << senial << endl;
    cout << "------------------------" << endl;

    // RETO 5: Crea un bucle 'for' que recorra el rack del 0 al 2.
    // En cada vuelta:
    //    a) Imprime qué módulo está actuando.
    //    b) Actualiza la variable 'senial' pasando su valor actual por la función del módulo.
    //       Ejemplo conceptual: senial = modulo.accion(senial);
    
    for(int i = 0; i < NUM_EFECTOS; i++) {
        // TU CÓDIGO AQUÍ:
        // ______________________________________________________
        // ______________________________________________________
        // ______________________________________________________
        cout<<rack[i].nombre<<endl;
        senial = rack[i].accion(senial);
        cout << " -> Nueva senial: " << senial << endl;
    }

    cout << "------------------------" << endl;
    cout << "Resultado Final: " << senial << endl;
    
    return 0;
}
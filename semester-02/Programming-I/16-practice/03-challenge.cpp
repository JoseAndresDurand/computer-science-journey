#include <iostream>
using namespace std;

// 1. FUNCIONES DE TRANSFORMACIÓN
// -----------------------------------------------------------
// Esta función recibe un entero y devuelve el doble
int amplificar(int n) {
    return n * 2;
}

// Esta función recibe un entero y devuelve el valor negativo
int invertir(int n) {
    return n * -1;
}

// 2. LA ESTRUCTURA DEL CHIP
// -----------------------------------------------------------
struct Procesador {
    int id;
    
    // --- RETO 1: Declara el puntero a función aquí ---
    // Nombre del puntero: 'filtro'
    // IMPORTANTE: Fíjate en el tipo de retorno de las funciones de arriba.
    // Ya no es void.
    
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________; 
    int (*filtro)(int);
};

int main() {
    int senial_entrada = 10;
    
    // 3. CONFIGURACIÓN
    // -----------------------------------------------------------
    Procesador chipA;
    chipA.id = 1;
    
    // --- RETO 2: Configura el chipA para que AMPLIFIQUE la señal ---
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________;
    chipA.filtro = amplificar;

    Procesador chipB;
    chipB.id = 2;
    
    // --- RETO 3: Configura el chipB para que INVIERTA la señal ---
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________;
    chipB.filtro = invertir;

    // 4. PROCESAMIENTO (El momento de la verdad)
    // -----------------------------------------------------------
    cout << "Señal Original: " << senial_entrada << endl;

    // --- RETO 4: Usa el puntero de chipA para transformar la señal ---
    // Debes guardar el resultado en la variable 'salidaA'
    int salidaA = 0; 
    
    // TU CÓDIGO AQUÍ (Reemplaza el 0 con la llamada al puntero):
    // salidaA = ____________________________________________;
    salidaA = chipA.filtro(senial_entrada);
    cout << "Salida Chip A (Amplificada): " << salidaA << endl;

    // --- RETO 5: Usa el puntero de chipB para transformar la señal ---
    int salidaB = 0;
    
    // TU CÓDIGO AQUÍ:
    // salidaB = ____________________________________________;
    salidaB = chipB.filtro(senial_entrada);
    cout << "Salida Chip B (Invertida): " << salidaB << endl;

    return 0;
}
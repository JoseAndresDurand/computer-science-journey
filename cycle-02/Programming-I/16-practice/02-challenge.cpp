#include <iostream>
#include <string>
using namespace std;

// 1. DEFINICIÓN DE COMPORTAMIENTOS (Las funciones de ataque)
// -----------------------------------------------------------
// Esta función simula un ataque físico
void mordisco(int danio) {
    cout << "¡GRRR! Te muerde brutalmente causando " << danio << " de daño." << endl;
}

// Esta función simula un ataque mágico
void bolaFuego(int danio) {
    cout << "¡WOOSH! Lanza una bola de fuego por " << danio << " de daño." << endl;
}

// 2. LA ESTRUCTURA DEL ENEMIGO
// -----------------------------------------------------------
struct Enemigo {
    string nombre;
    int poder;
    
    // --- RETO 1: Declara el puntero a función aquí ---
    // Nombre del puntero: 'atacar'
    // Debe apuntar a funciones como 'mordisco' o 'bolaFuego' (reciben int, devuelven void)
    
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________; 
    void (*atacar)(int);
};

int main() {
    // 3. CREACIÓN DE LA HORDA
    // -----------------------------------------------------------
    // Vamos a crear 2 enemigos con comportamientos diferentes
    Enemigo orco;
    orco.nombre = "Orco Berserker";
    orco.poder = 15;
    
    // --- RETO 2: Asigna la función 'mordisco' al puntero del orco ---
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________;
    orco.atacar = mordisco;

    Enemigo mago;
    mago.nombre = "Mago Oscuro";
    mago.poder = 40;
    
    // --- RETO 3: Asigna la función 'bolaFuego' al puntero del mago ---
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________;
    mago.atacar = bolaFuego;

    // 4. EL BUCLE DE BATALLA (Polimorfismo manual)
    // -----------------------------------------------------------
    cout << "--- COMIENZA LA BATALLA ---" << endl;
    
    // Orco ataca
    cout << orco.nombre << " se acerca..." << endl;
    // --- RETO 4: Ejecuta el ataque del orco usando su puntero ---
    // Pista: Usa orco.poder como argumento
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________;
    cout<< "Orco ataca" <<endl;
    orco.atacar(orco.poder);
    // Mago ataca
    cout << mago.nombre << " prepara un hechizo..." << endl;
    // --- RETO 5: Ejecuta el ataque del mago usando su puntero ---
    // TU CÓDIGO AQUÍ:
    // ______________________________________________________;
    cout<<"Mago ataca"<<endl;
    mago.atacar(mago.poder);
    return 0;
}
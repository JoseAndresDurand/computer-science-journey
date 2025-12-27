#include <iostream>
#include <vector>
using namespace std;

// 1. Clase Base (Contrato)
class Animal {
public:
    // "virtual" significa: "Mis hijos pueden cambiar cómo funciona esto"
    virtual void hacerSonido() { 
        cout << "..." << endl; 
    }
};

// 2. Clases Derivadas (Implementaciones concretas)
class Perro : public Animal {
public:
    void hacerSonido() override { cout << "Guau!" << endl; }
};

class Gato : public Animal {
public:
    void hacerSonido() override { cout << "Miau!" << endl; }
};

class Vaca : public Animal { // ¡Puedo agregar esto sin tocar la función principal!
public:
    void hacerSonido() override { cout << "Muuu!" << endl; }
};

// 3. El poder del Polimorfismo
// Esta función recibe un "Animal". No sabe si es perro o gato, ni le importa.
void hacerCantar(Animal* a) {
    a->hacerSonido(); // <--- AQUÍ OCURRE LA MAGIA
}

int main() {
    Perro miPerro;
    Gato miGato;
    Vaca miVaca;

    // Trato a todos como "Animales" genéricos
    hacerCantar(&miPerro); // Salida: Guau!
    hacerCantar(&miGato);  // Salida: Miau!
    hacerCantar(&miVaca);  // Salida: Muuu!

    return 0;
}
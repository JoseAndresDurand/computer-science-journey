#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <string>

// Clase Abstracta Pura: Nadie puede instanciar un "GameObject" directamente.
class GameObject {
protected:
    // Atributos comunes para TODOS los juegos (Herencia de Datos)
    std::string idName;   // Nombre de la entidad (ej: "Nave Jugador", "Orco 1")
    bool active;          // ¿Sigue vivo en el juego?
    float x, y;           // Posición en el mundo (incluso en juegos de texto pueden usarse o ignorarse)

public:
    // Constructor Base
    GameObject(std::string name, float startX = 0, float startY = 0) 
        : idName(name), x(startX), y(startY), active(true) {
    }

    // 🛡️ SEGURIDAD CRÍTICA: Destructor Virtual
    // Si esto no es virtual, al hacer 'delete' de un puntero GameObject,
    // NO se llamará al destructor del hijo (Fuga de Memoria / Memory Leak).
    virtual ~GameObject() {
        std::cout << "[MEMORIA] Destruyendo base GameObject: " << idName << std::endl;
    }

    // ---------------------------------------------------------
    // 🧬 EL NÚCLEO POLIMÓRFICO (Funciones Virtuales Puras)
    // ---------------------------------------------------------
    
    // update(): Aquí va la lógica (Matemáticas, IA, Movimiento)
    // El "= 0" obliga a que el hijo IMPLEMENTE esta función sí o sí.
    virtual void update() = 0; 

    // render(): Aquí va el dibujo (cout, gráficos, etc.)
    virtual void render() = 0;

    // Métodos concretos (Getters/Setters comunes) que se heredan tal cual
    bool isActive() const { return active; }
    void destroy() { active = false; }
    std::string getName() const { return idName; }
};

#endif // GAMEOBJECT_H
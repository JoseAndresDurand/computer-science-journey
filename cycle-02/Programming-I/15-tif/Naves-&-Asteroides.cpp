#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <chrono>
#include <cstdlib>

using namespace std;

// =========================================================
// ⚙️ CONFIGURACIÓN GLOBAL (Modifica esto para el tamaño)
// =========================================================
int nScreenWidth = 120;  // ANCHO: 120 columnas (Pantalla ancha)
int nScreenHeight = 40;  // ALTO: 40 filas

// Función de Ingeniería para forzar el tamaño de la ventana
void ConfigurarConsola() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. Definir el tamaño del buffer (Memoria lógica)
    COORD bufferSize;
    bufferSize.X = (SHORT)nScreenWidth;
    bufferSize.Y = (SHORT)nScreenHeight;
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // 2. Definir el tamaño de la ventana (Lo que ves físicamente)
    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = (SHORT)(nScreenWidth - 1);
    windowSize.Bottom = (SHORT)(nScreenHeight - 1);
    
    // Aplicar cambios (El TRUE es vital para que Windows obedezca)
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    
    // 3. Ocultar el cursor parpadeante (Estética)
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// ==========================================
// 🏗️ CLASE BASE
// ==========================================
class GameObject {
protected:
    float x, y;

public:
    GameObject(float startX, float startY) : x(startX), y(startY) {}
    virtual ~GameObject() {}
    virtual void update(float fElapsedTime, float difficulty) = 0;
    virtual void draw(wchar_t* screen) = 0;
    float getX() const { return x; }
    float getY() const { return y; }
};

// ==========================================
// 🚀 CLASE NAVE
// ==========================================
class Nave : public GameObject {
    wstring sprite[3];
    int width = 5;
    int height = 3;
    int vidas;

public:
    Nave() : GameObject((float)(nScreenWidth / 2), (float)(nScreenHeight - 5)) {
        vidas = 3;
        // Arte ASCII mejorado
        sprite[0] = L"  ^  ";
        sprite[1] = L" <A> ";
        sprite[2] = L"{|||}"; // Propulsores
    }

    void update(float fElapsedTime, float difficulty) override {
        // La nave se mueve a velocidad constante, no afectada por dificultad
        float speed = 50.0f * fElapsedTime;

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) x -= speed;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x += speed;
        
        // Clamp (Límites)
        if (x < 0) x = 0;
        if (x > nScreenWidth - width) x = nScreenWidth - width;
    }

    void draw(wchar_t* screen) override {
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                wchar_t pixel = sprite[row][col];
                if (pixel != L' ') {
                    int drawX = (int)x + col;
                    int drawY = (int)y + row;
                    if (drawX >= 0 && drawX < nScreenWidth && drawY >= 0 && drawY < nScreenHeight) {
                        screen[drawY * nScreenWidth + drawX] = pixel;
                    }
                }
            }
        }
    }

    // Lógica de daño
    bool checkCollision(int astX, int astY) {
        if (astX >= (int)x && astX <= (int)x + 4 &&
            astY >= (int)y && astY <= (int)y + 2) {
            return true;
        }
        return false;
    }

    void perderVida() { vidas--; }
    int getVidas() const { return vidas; }
};

// ==========================================
// ☄️ CLASE ASTEROIDE
// ==========================================
class Asteroide : public GameObject {
    float baseSpeed;
    float currentSpeed;
    int tailLength;

public:
    Asteroide() : GameObject(0, 0) {
        reset();
    }

    // Reiniciar posición arriba
    void reset() {
        x = (float)(rand() % nScreenWidth);
        y = (float)((rand() % 20) * -1); // Spawn escalonado negativo
        baseSpeed = 5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10.0f));
        tailLength = 4 + (rand() % 5);
    }

    void update(float fElapsedTime, float difficulty) override {
        // AQUÍ OCURRE LA MAGIA DE LA DIFICULTAD
        // La velocidad base se multiplica por el factor de dificultad
        currentSpeed = baseSpeed * difficulty;
        y += currentSpeed * fElapsedTime;
    }

    void draw(wchar_t* screen) override {
        // Dibujar Estela
        for (int i = 0; i < tailLength; i++) {
            int drawY = (int)y - i;
            if (drawY >= 0 && drawY < nScreenHeight && x >= 0 && x < nScreenWidth) {
                if (i == 0) screen[drawY * nScreenWidth + (int)x] = L'O'; // Cabeza
                else if (i < 3) screen[drawY * nScreenWidth + (int)x] = L'o'; // Cuerpo
                else screen[drawY * nScreenWidth + (int)x] = L'.'; // Cola
            }
        }
    }
};

// ==========================================
// 🎮 MAIN ENGINE
// ==========================================
int main() {
    ConfigurarConsola(); // <--- Paso 1: Configurar la ventana ancha
    srand((unsigned int)time(NULL));

    // Crear Buffer de Pantalla
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hBuffer);
    DWORD dwBytesWritten = 0;

    // Instanciar Objetos
    Nave* player = new Nave();
    vector<Asteroide*> asteroides;
    for(int i=0; i<30; i++) asteroides.push_back(new Asteroide()); // 30 Asteroides

    // Variables de Estado del Juego
    auto tp1 = chrono::system_clock::now();
    float totalGameTime = 0.0f;
    float difficultyMultiplier = 1.0f;
    int score = 0;
    bool gameOver = false;

    // --- GAME LOOP ---
    while (!gameOver) {
        // Delta Time
        auto tp2 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();
        
        totalGameTime += fElapsedTime;

        // --- SISTEMA DE DIFICULTAD ---
        // Si pasamos el minuto (60s), aumentamos la velocidad un 50%
        if (totalGameTime > 60.0f) {
            difficultyMultiplier = 1.5f + ((totalGameTime - 60.
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <chrono>
#include <cstdlib>

using namespace std;

// ==========================================
// 🔧 CONFIGURACIÓN DE PANTALLA
// ==========================================
int nScreenWidth = 80;
int nScreenHeight = 30;

// ==========================================
// 🏗️ CLASE BASE
// ==========================================
class GameObject {
protected:
    float x, y;

public:
    GameObject(float startX, float startY) : x(startX), y(startY) {}
    virtual ~GameObject() {}

    virtual void update(float fElapsedTime) = 0;
    virtual void draw(wchar_t* screen) = 0;

    float getX() const { return x; }
    float getY() const { return y; }
};

// ==========================================
// 🚀 CLASE NAVE (ASCII ART SEGURO)
// ==========================================
class Nave : public GameObject {
    wstring sprite[3];
    int width = 5;
    int height = 3;

public:
    Nave() : GameObject(40, 25) {
        sprite[0] = L"  ^  ";
        sprite[1] = L" <H> ";
        sprite[2] = L"/ | \\";
    }

    void update(float fElapsedTime) override {
        float speed = 40.0f * fElapsedTime;

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) x -= speed;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x += speed;
        
        // CORRECCIÓN DE BORDES: Clamp estricto para evitar que se parta
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

                    // 🛡️ SECURITY CHECK: Evita escribir fuera del array (Crash o Glitch visual)
                    if (drawX >= 0 && drawX < nScreenWidth && drawY >= 0 && drawY < nScreenHeight) {
                        screen[drawY * nScreenWidth + drawX] = pixel;
                    }
                }
            }
        }
    }

    // Colisión más precisa
    bool checkCollision(int astX, int astY) {
        // Caja de colisión centrada (hitbox)
        if (astX >= (int)x + 1 && astX <= (int)x + 3 &&
            astY >= (int)y && astY <= (int)y + 2) {
            return true;
        }
        return false;
    }
};

// ==========================================
// ☄️ CLASE ASTEROIDE (CON ESTELA DE VELOCIDAD)
// ==========================================
class Asteroide : public GameObject {
    float speedY;
    int tailLength; // Longitud de la estela

public:
    Asteroide(float startX, float difficulty) : GameObject(startX, 0) {
        // Velocidad base + dificultad
        speedY = (5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/8.0f))) * difficulty;
        tailLength = 8; // Largo de la cola
        y = (float)(rand() % nScreenHeight) * -1; // Empiezan fuera de pantalla para caer escalonados
    }

    void update(float fElapsedTime) override {
        y += speedY * fElapsedTime;
    }

    void draw(wchar_t* screen) override {
        // 1. Dibujar la CABEZA (El meteoro real)
        if (y >= 0 && y < nScreenHeight && x >= 0 && x < nScreenWidth) {
            screen[(int)y * nScreenWidth + (int)x] = L'O'; // Cabeza grande
        }

        // 2. Dibujar la ESTELA (El rastro de velocidad)
        for (int i = 1; i <= tailLength; i++) {
            int tailY = (int)y - i; // Posiciones anteriores (arriba)

            // Solo dibujamos si está dentro de la pantalla
            if (tailY >= 0 && tailY < nScreenHeight && x >= 0 && x < nScreenWidth) {
                // Efecto visual: La cola se ve diferente
                if (i < 3) screen[tailY * nScreenWidth + (int)x] = L'o'; // Parte cercana
                else screen[tailY * nScreenWidth + (int)x] = L'.';      // Parte lejana
            }
        }
    }

    void reset() {
        y = -10; // Reiniciar arriba fuera de pantalla
        x = rand() % nScreenWidth;
        speedY = 5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5.0f));
    }
};

// ==========================================
// 🎮 MAIN ENGINE
// ==========================================
int main() {
    srand((unsigned int)time(NULL));

    // --- MAGIA DE CONSOLA: Forzar tamaño de ventana ---
    // Esto arregla el glitch de la nave partida.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, (SHORT)(nScreenWidth - 1), (SHORT)(nScreenHeight - 1)};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    
    // Crear Buffer
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hBuffer);
    DWORD dwBytesWritten = 0;

    // --- OBJETOS ---
    Nave* player = new Nave();
    vector<Asteroide*> asteroides;
    
    // Crear 20 asteroides con dificultad inicial
    for(int i=0; i<20; i++) asteroides.push_back(new Asteroide((float)(rand() % nScreenWidth), 1.0f));

    auto tp1 = chrono::system_clock::now();
    int score = 0;
    bool gameOver = false;

    while (!gameOver) {
        // Tiempo
        auto tp2 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        // Limpiar
        for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

        // Update y Draw JUGADOR
        player->update(fElapsedTime);
        player->draw(screen);

        // Update y Draw ASTEROIDES
        for (auto ast : asteroides) {
            ast->update(fElapsedTime);
            ast->draw(screen);

            // Colisión con la CABEZA del asteroide
            if (player->checkCollision((int)ast->getX(), (int)ast->getY())) {
                gameOver = true;
            }

            // Respawn al salir por abajo
            if (ast->getY() >= nScreenHeight) {
                score += 10;
                ast->reset();
            }
        }

        // GUI
        swprintf_s(&screen[2 * nScreenWidth + 2], 40, L"SCORE: %d", score);

        // Render Final
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacterW(hBuffer, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }

    // Mensaje final simple
    system("cls");
    cout << "GAME OVER - SCORE: " << score << endl;
    system("pause");

    return 0;
}
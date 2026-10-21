#include <raylib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>

// --- PARCHES PARA CONFLICTOS DE NOMBRES ---
// Le cambiamos el nombre a TODO lo que Windows comparte con Raylib
#define CloseWindow WinCloseWindow
#define ShowCursor WinShowCursor
#define DrawText WinDrawText
#define Rectangle WinRectangle      // <--- ¡NUEVO AGREGADO!

#include <windows.h>
#include <mmsystem.h>

// Devolvemos los nombres a la normalidad para Raylib
#undef CloseWindow
#undef ShowCursor
#undef DrawText
#undef Rectangle                    // <--- Liberamos el nombre
// ------------------------------------------

using namespace std;

// Enum de Estados
enum GameScreen { MENU_CALIBRACION, JUEGO, FINAL };

// Interfaz
class InputStrategy {
public:
    virtual void update() = 0;
    virtual float getFuerzaSalto() = 0;
    virtual string getNombre() = 0;
    virtual void dibujarCalibracion(int x, int y) = 0;
    virtual ~InputStrategy() {}
};

// --- ESTRATEGIA 1: TECLADO ---
class TecladoInput : public InputStrategy {
public:
    void update() override {} 
    float getFuerzaSalto() override {
        if (IsKeyPressed(KEY_SPACE)) return 8.0f; 
        return 0.0f;
    }
    string getNombre() override { return "MODO: TECLADO"; }
    void dibujarCalibracion(int x, int y) override {
        DrawText("Prueba presionar [ESPACIO]", x, y, 20, DARKGRAY);
        if (IsKeyDown(KEY_SPACE)) DrawText("¡DETECTADO!", x + 250, y, 20, GREEN);
    }
};

// --- ESTRATEGIA 2: MICRÓFONO PROFESIONAL (DOBLE BUFFER) ---
class MicInput : public InputStrategy {
private:
    HWAVEIN hWaveIn;
    // Usamos 2 buffers para que nunca se corte el audio
    static const int NUM_BUFFERS = 2;
    static const int BUFFER_SIZE = 1024; // Más pequeño = Más rápido (Menos lag)
    
    WAVEHDR waveHeaders[NUM_BUFFERS];
    short buffers[NUM_BUFFERS][BUFFER_SIZE];
    
    float volumenActual;
    float umbral; 
    bool calibrando;
    double tiempoInicioCalibracion;
    float maxRuidoDetectado;

public:
    MicInput() {
        volumenActual = 0.0f;
        umbral = 3000.0f; 
        calibrando = false;
        maxRuidoDetectado = 0.0f;

        // 1. Configuración para CONDENSADORES (48000 Hz es estándar en video/interfaces)
        WAVEFORMATEX wfx;
        wfx.wFormatTag = WAVE_FORMAT_PCM;
        wfx.nChannels = 1;      
        wfx.nSamplesPerSec = 48000; // <--- CAMBIO IMPORTANTE: 48kHz
        wfx.nAvgBytesPerSec = 48000 * 2;
        wfx.nBlockAlign = 2;
        wfx.wBitsPerSample = 16; 
        wfx.cbSize = 0;

        // 2. Abrir Dispositivo
        if (waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
            // Si falla 48k, intentamos 44.1k como respaldo
            wfx.nSamplesPerSec = 44100;
            wfx.nAvgBytesPerSec = 44100 * 2;
            waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        }

        // 3. Preparar los DOS buffers
        for (int i = 0; i < NUM_BUFFERS; ++i) {
            ZeroMemory(&waveHeaders[i], sizeof(WAVEHDR));
            waveHeaders[i].lpData = (LPSTR)buffers[i];
            waveHeaders[i].dwBufferLength = BUFFER_SIZE * 2; // bytes
            
            waveInPrepareHeader(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
            waveInAddBuffer(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
        }

        waveInStart(hWaveIn);
    }

    ~MicInput() {
        waveInStop(hWaveIn);
        for (int i = 0; i < NUM_BUFFERS; ++i) {
            waveInUnprepareHeader(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
        }
        waveInClose(hWaveIn);
    }

    void update() override {
        // Revisamos AMBOS buffers
        for (int i = 0; i < NUM_BUFFERS; ++i) {
            if (waveHeaders[i].dwFlags & WHDR_DONE) {
                
                // Procesar Audio
                double suma = 0;
                for (int j = 0; j < BUFFER_SIZE; j++) {
                    suma += abs(buffers[i][j]); 
                }
                
                // Promedio suavizado
                float lecturaInstantanea = (float)(suma / BUFFER_SIZE) * 10.0f; // Ganancia x10 para micros suaves
                
                // Suavizado visual (Lerp) para que no parpadee tan feo
                volumenActual = volumenActual * 0.7f + lecturaInstantanea * 0.3f;

                // Devolver el buffer a Windows para que lo llene otra vez
                waveInAddBuffer(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
            }
        }

        // Lógica de Calibración
        if (calibrando) {
            if (volumenActual > maxRuidoDetectado) maxRuidoDetectado = volumenActual;
            if (GetTime() - tiempoInicioCalibracion > 3.0) {
                calibrando = false;
                umbral = maxRuidoDetectado * 1.5f; 
                if (umbral < 2000) umbral = 2000;
            }
        } else {
            // Ajuste manual
            float velocidad = 50.0f;
            if (IsKeyDown(KEY_LEFT_SHIFT)) velocidad = 500.0f;
            if (IsKeyDown(KEY_UP)) umbral += velocidad;
            if (IsKeyDown(KEY_DOWN) && umbral > velocidad) umbral -= velocidad;

            if (IsKeyPressed(KEY_C)) {
                calibrando = true;
                maxRuidoDetectado = 0;
                tiempoInicioCalibracion = GetTime();
            }
        }
    }

    float getFuerzaSalto() override {
        if (!calibrando && volumenActual > umbral) return 8.0f;
        return 0.0f;
    }

    string getNombre() override { return "MODO: CONDENSADOR (48kHz)"; }

    void dibujarCalibracion(int x, int y) override {
        if (calibrando) {
            DrawText("CALIBRANDO... SHHHH...", x, y, 25, ORANGE);
            DrawRectangle(x, y + 40, (int)(GetTime() * 100) % 300, 20, ORANGE);
            return;
        }

        DrawText("PANEL DE CONTROL DE AUDIO", x, y - 20, 20, DARKGRAY);
        
        Color colorEstado = (volumenActual > umbral) ? GREEN : RED;
        const char* textoEstado = (volumenActual > umbral) ? "¡SALTA!" : "ESPERANDO...";
        
        DrawText(TextFormat("VOLUMEN: %.0f", volumenActual), x, y + 20, 30, DARKGRAY);
        DrawText(TextFormat("ESTADO: %s", textoEstado), x + 250, y + 20, 30, colorEstado);

        // VÚMETRO
        int anchoTotal = 500;
        int altoBarra = 40;
        int yBarra = y + 80;
        int segmentos = 50; 
        float anchoSegmento = (float)anchoTotal / segmentos;
        
        // Ajustado para micros sensibles
        float escalaMaxima = 30000.0f; 

        DrawRectangle(x - 5, yBarra - 5, anchoTotal + 10, altoBarra + 10, BLACK);

        float porcentajeVolumen = volumenActual / escalaMaxima;
        int segmentosEncendidos = (int)(porcentajeVolumen * segmentos);

        for (int i = 0; i < segmentos; i++) {
            Color colorLed = DARKGRAY;
            if (i < segmentosEncendidos) {
                if (i < segmentos * 0.6) colorLed = GREEN;
                else if (i < segmentos * 0.85) colorLed = YELLOW;
                else colorLed = RED;
            }
            DrawRectangle(x + (int)(i * anchoSegmento), yBarra, (int)anchoSegmento - 2, altoBarra, colorLed);
        }

        // UMBRAL
        float porcentajeUmbral = umbral / escalaMaxima;
        int xUmbral = x + (int)(anchoTotal * porcentajeUmbral);
        
        DrawRectangle(xUmbral, yBarra - 10, 4, altoBarra + 20, SKYBLUE);
        DrawText("UMBRAL", xUmbral - 20, yBarra - 30, 10, SKYBLUE);
        DrawText(TextFormat("%.0f", umbral), xUmbral - 10, yBarra + 55, 10, SKYBLUE);

        DrawText("[C] Auto-Calibrar  |  [Flechas] Ajustar Manual", x, y + 150, 20, DARKGRAY);
    }
};

// --- MAIN LOOP ---
int main() {
    InitWindow(800, 600, "TIF: Clap Bird - Pro Audio");
    InitAudioDevice(); 
    SetTargetFPS(60);

    GameScreen pantallaActual = MENU_CALIBRACION;
    InputStrategy* control = new TecladoInput();
    bool modoMicrofono = false;

    float birdY = 300.0f;
    float velocity = 0.0f;
    float gravity = 0.25f;
    double tiempoInicio = 0, tiempoJugado = 0;

    while (!WindowShouldClose()) {
        if (pantallaActual == MENU_CALIBRACION) {
            if (IsKeyPressed(KEY_M)) {
                delete control;
                modoMicrofono = !modoMicrofono;
                control = modoMicrofono ? (InputStrategy*)new MicInput() : (InputStrategy*)new TecladoInput();
            }
            if (IsKeyPressed(KEY_RIGHT)) gravity += 0.05f;
            if (IsKeyPressed(KEY_LEFT) && gravity > 0.05f) gravity -= 0.05f;

            if (IsKeyPressed(KEY_R)) {
                birdY = 300.0f;
                velocity = 0.0f;
                tiempoInicio = GetTime();
                pantallaActual = JUEGO;
            }
        }

        control->update();

        // LÓGICA DE JUEGO
        if (pantallaActual == JUEGO) {
            tiempoJugado = GetTime() - tiempoInicio;
            if (control->getFuerzaSalto() > 0) velocity = -8.0f;
            velocity += gravity;
            birdY += velocity;
            if (birdY > 580 || birdY < 20) pantallaActual = FINAL;
        } else if (pantallaActual == FINAL) {
            if (IsKeyPressed(KEY_R)) pantallaActual = MENU_CALIBRACION;
        } else {
            // Animación Menú
            birdY = 300 + sin(GetTime()*5) * 10;
        }

        // DIBUJADO
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (pantallaActual == MENU_CALIBRACION) {
            DrawText("MENÚ DE CALIBRACIÓN", 260, 20, 30, DARKBLUE);
            DrawText(control->getNombre().c_str(), 260, 60, 20, BLACK);
            control->dibujarCalibracion(150, 150);
            DrawCircle(100, (int)birdY, 20, MAROON);
        } else if (pantallaActual == JUEGO) {
            DrawText(TextFormat("%.2f s", tiempoJugado), 350, 20, 40, BLUE);
            DrawCircle(400, (int)birdY, 20, MAROON);
        } else {
            DrawText("GAME OVER", 280, 200, 50, RED);
            DrawText(TextFormat("Tiempo: %.2f s", tiempoJugado), 300, 280, 20, BLACK);
            DrawText("[R] VOLVER AL MENÚ", 300, 350, 20, DARKGRAY);
        }

        EndDrawing();
    }

    delete control;
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
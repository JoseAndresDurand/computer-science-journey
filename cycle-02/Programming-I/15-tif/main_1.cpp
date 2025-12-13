#include <raylib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>

// 1. Antes de llamar a Windows, renombramos sus funciones conflictivas
//    (Le decimos: "Cuando digas CloseWindow, en realidad es WinCloseWindow")
#define CloseWindow WinCloseWindow
#define ShowCursor WinShowCursor


// --- AQUÍ ESTÁ EL TRUCO PARA QUE NO FALLE ---
#include <windows.h>
#include <mmsystem.h>

// Le decimos a Windows: "Suelta esos nombres, son de Raylib"
#undef DrawText      // Soluciona el error de texto
#undef CloseWindow   // Soluciona posible error al cerrar
#undef ShowCursor    // Soluciona posible error con el mouse
// --------------------------------------------

using namespace std;

// ... A partir de aquí sigue tu código normal (enums, clases, etc.) ...

// ----------------------------------------------------------------------------------
// ENUMS Y ESTADOS
// ----------------------------------------------------------------------------------
enum GameScreen { MENU_CALIBRACION, JUEGO, FINAL };

// ----------------------------------------------------------------------------------
// CLASE BASE ABSTRACTA
// ----------------------------------------------------------------------------------
class InputStrategy {
public:
    virtual void update() = 0;
    virtual float getFuerzaSalto() = 0;
    virtual string getNombre() = 0;
    virtual void dibujarCalibracion(int x, int y) = 0;
    virtual ~InputStrategy() {}
};

// ----------------------------------------------------------------------------------
// ESTRATEGIA 1: TECLADO (UI Mejorada)
// ----------------------------------------------------------------------------------
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
        if (IsKeyDown(KEY_SPACE)) {
             DrawRectangle(x, y + 30, 300, 40, GREEN);
             DrawText("¡DETECTADO!", x + 80, y + 40, 20, WHITE);
        }
    }
};

// ----------------------------------------------------------------------------------
// --- ESTRATEGIA 2: MICRÓFONO REAL (USANDO WINDOWS API) ---
class MicInput : public InputStrategy {
private:
    // Variables de la API de Windows
    HWAVEIN hWaveIn;
    WAVEHDR waveHdr;
    static const int BUFFER_SIZE = 2048; // Tamaño del bloque de audio
    short buffer[BUFFER_SIZE];          // Buffer de datos crudos (16-bit)
    
    // Variables del Juego
    float volumenActual;
    float umbral; 
    bool calibrando;
    double tiempoInicioCalibracion;
    float maxRuidoDetectado;

public:
    MicInput() {
        volumenActual = 0.0f;
        umbral = 5000.0f; // Valor inicial razonable para 16-bit
        calibrando = false;
        maxRuidoDetectado = 0.0f;

        // 1. Configurar formato de audio (Calidad CD Mono)
        WAVEFORMATEX wfx;
        wfx.wFormatTag = WAVE_FORMAT_PCM;
        wfx.nChannels = 1;      // Mono
        wfx.nSamplesPerSec = 44100;
        wfx.nAvgBytesPerSec = 44100 * 2;
        wfx.nBlockAlign = 2;
        wfx.wBitsPerSample = 16; // 16 bits de profundidad
        wfx.cbSize = 0;

        // 2. Abrir el Micrófono (WAVE_MAPPER elige el predeterminado de Windows)
        // Usamos CALLBACK_NULL para no complicarnos con hilos, haremos "polling" en el update
        if (waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
            printf("ERROR: No se pudo abrir el microfono.\n");
        }

        // 3. Preparar el Buffer
        ZeroMemory(&waveHdr, sizeof(WAVEHDR));
        waveHdr.lpData = (LPSTR)buffer;
        waveHdr.dwBufferLength = BUFFER_SIZE * 2; // En bytes (short = 2 bytes)

        waveInPrepareHeader(hWaveIn, &waveHdr, sizeof(WAVEHDR));
        waveInAddBuffer(hWaveIn, &waveHdr, sizeof(WAVEHDR));

        // 4. ¡Empezar a Grabar!
        waveInStart(hWaveIn);
    }

    ~MicInput() {
        // Limpieza correcta del hardware
        waveInStop(hWaveIn);
        waveInUnprepareHeader(hWaveIn, &waveHdr, sizeof(WAVEHDR));
        waveInClose(hWaveIn);
    }

    void update() override {
        // "POLLING": Preguntamos a Windows si ya llenó el buffer
        if (waveHdr.dwFlags & WHDR_DONE) {
            
            // 1. CALCULAR VOLUMEN REAL (RMS)
            double suma = 0;
            for (int i = 0; i < BUFFER_SIZE; i++) {
                // buffer[i] es un entero con signo (-32768 a 32767)
                // Tomamos valor absoluto para sumar "energía"
                suma += abs(buffer[i]); 
            }
            // Promedio simple (más estable que RMS para aplausos secos)
            volumenActual = (float)(suma / BUFFER_SIZE) * 5.0f; // x5 Ganancia

            // 2. RECICLAR BUFFER (Devolverlo a Windows para que lo llene de nuevo)
            waveInAddBuffer(hWaveIn, &waveHdr, sizeof(WAVEHDR));
        }

        // --- LÓGICA DE CALIBRACIÓN (Igual que antes) ---
        if (calibrando) {
            if (volumenActual > maxRuidoDetectado) maxRuidoDetectado = volumenActual;
            
            if (GetTime() - tiempoInicioCalibracion > 3.0) {
                calibrando = false;
                umbral = maxRuidoDetectado * 1.5f; // Margen de seguridad x1.5
                if (umbral < 1500) umbral = 1500; // Mínimo absoluto
            }
        } else {
            // Ajuste Manual
            float velocidad = 50.0f;
            if (IsKeyDown(KEY_LEFT_SHIFT)) velocidad = 500.0f;
            if (IsKeyDown(KEY_UP)) umbral += velocidad;
            if (IsKeyDown(KEY_DOWN) && umbral > velocidad) umbral -= velocidad;
            
            // Activar Auto-Calibración
            if (IsKeyPressed(KEY_C)) {
                calibrando = true;
                maxRuidoDetectado = 0;
                tiempoInicioCalibracion = GetTime();
            }
        }
    }

    float getFuerzaSalto() override {
        if (!calibrando && volumenActual > umbral) {
            return 8.0f; 
        }
        return 0.0f;
    }

    string getNombre() override { return "MODO: MICROFONO (WINDOWS API)"; }

    // --- VISUALIZACIÓN (La misma bonita de antes, ajustada a nueva escala) ---
    void dibujarCalibracion(int x, int y) override {
        if (calibrando) {
            DrawText("CALIBRANDO... GUARDAR SILENCIO", x, y, 25, ORANGE);
            DrawRectangle(x, y + 40, (int)(GetTime() * 100) % 300, 20, ORANGE);
            DrawText(TextFormat("Ruido Máx: %.0f", maxRuidoDetectado), x, y + 70, 20, DARKGRAY);
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
        
        // ESCALA MÁXIMA AJUSTADA PARA 16-BIT (32000 es el tope teórico aprox)
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

        // UMBRAL DESLIZANTE
        float porcentajeUmbral = umbral / escalaMaxima;
        int xUmbral = x + (int)(anchoTotal * porcentajeUmbral);
        
        DrawRectangle(xUmbral, yBarra - 10, 4, altoBarra + 20, SKYBLUE);
        DrawText("UMBRAL", xUmbral - 20, yBarra - 30, 10, SKYBLUE);
        DrawText(TextFormat("%.0f", umbral), xUmbral - 10, yBarra + 55, 10, SKYBLUE);

        DrawText("[C] Auto-Calibrar (3 seg)  |  [Flechas] Mover Umbral Manualmente", x, y + 150, 20, DARKGRAY);
    }
};

// ----------------------------------------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------------------------------------
int main() {
    InitWindow(800, 600, "TIF: Clap Bird - AutoCalibration");
    InitAudioDevice(); 
    SetTargetFPS(60);

    GameScreen pantallaActual = MENU_CALIBRACION;
    InputStrategy* control = new TecladoInput();
    bool modoMicrofono = false;

    // Físicas
    float birdY = 300.0f;
    float velocity = 0.0f;
    float gravity = 0.25f;
    double tiempoInicio = 0, tiempoJugado = 0;

    while (!WindowShouldClose()) {
        // --- LÓGICA GLOBAL ---
        if (pantallaActual == MENU_CALIBRACION) {
            if (IsKeyPressed(KEY_M)) {
                delete control;
                modoMicrofono = !modoMicrofono;
                if (modoMicrofono) control = new MicInput();
                else control = new TecladoInput();
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

        control->update(); // Siempre actualizamos sensores

        // --- LÓGICA DE ESTADOS ---
        switch (pantallaActual) {
            case MENU_CALIBRACION:
                birdY = 300 + sin(GetTime()*5) * 10; 
                break;

            case JUEGO:
                tiempoJugado = GetTime() - tiempoInicio;
                if (control->getFuerzaSalto() > 0) velocity = -8.0f; // Salto fijo
                velocity += gravity;
                birdY += velocity;

                if (birdY > 580 || birdY < 20) pantallaActual = FINAL;
                break;

            case FINAL:
                if (IsKeyPressed(KEY_R)) pantallaActual = MENU_CALIBRACION;
                break;
        }

        // --- DIBUJADO ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (pantallaActual) {
            case MENU_CALIBRACION:
                DrawText("MENÚ DE CALIBRACIÓN", 260, 20, 30, DARKBLUE);
                DrawText(control->getNombre().c_str(), 260, 60, 20, BLACK);
                DrawText("[M] Cambiar Entrada  |  [R] Jugar", 230, 550, 20, DARKGREEN);
                DrawText(TextFormat("Gravedad: %.2f (Izquierda/Derecha)", gravity), 260, 520, 20, GRAY);
                
                control->dibujarCalibracion(180, 150);
                DrawCircle(100, (int)birdY, 20, MAROON);
                break;

            case JUEGO:
                DrawText(TextFormat("%.2f s", tiempoJugado), 350, 20, 40, BLUE);
                DrawCircle(400, (int)birdY, 20, MAROON);
                if (velocity < 0) DrawEllipse(390, (int)birdY+2, 10, 5, MAROON);
                else DrawEllipse(390, (int)birdY+5, 10, 5, MAROON);
                break;

            case FINAL:
                DrawText("GAME OVER", 280, 200, 50, RED);
                DrawText(TextFormat("Sobreviviste: %.2f segundos", tiempoJugado), 240, 280, 20, BLACK);
                DrawText("[R] VOLVER AL MENÚ", 300, 350, 20, DARKGRAY);
                break;
        }

        EndDrawing();
    }

    delete control;
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
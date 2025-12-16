#include <raylib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>

// --- PARCHES PARA WINDOWS VS RAYLIB ---
#define CloseWindow WinCloseWindow
#define ShowCursor WinShowCursor
#define DrawText WinDrawText
#define Rectangle WinRectangle

#include <windows.h>
#include <mmsystem.h>

#undef CloseWindow
#undef ShowCursor
#undef DrawText
#undef Rectangle
// --------------------------------------

using namespace std;

// ----------------------------------------------------------------------------------
// 1. GEOLOGÍA COMPUTACIONAL (Datos del Informe Técnico)
// ----------------------------------------------------------------------------------

// Tipos morfológicos para el "Renderizado Polimórfico"
enum TipoMorfologia { 
    CONO_PERFECTO,      // Triángulo simétrico (Misti)
    ESTRATO_COMPLEJO,   // Irregular/Dentado (Chachani)
    MESETA_DOMICA,      // Ancho y plano arriba (Coropuna)
    CONO_COLAPSADO,     // Asimétrico (Hualca Hualca)
    PARED_VERTICAL,     // Bloque rectangular (Solimana)
    CONO_MONOGENETICO   // Pequeño y perfecto (Nicholson)
};

struct DatosVolcan {
    string id;
    string nombre;
    string clasificacion; // Ej: "Estratovolcán Activo"
    int alturaReal;       // m.s.n.m
    
    // Datos Visuales
    float anchoBasePx;
    float altoVisualPx;
    Color colorCuerpo;
    
    TipoMorfologia tipo;
    bool tieneNieve;
    bool esActivo;        // Si es true, emite humo
};

// --- BASE DE DATOS GEOLÓGICA (Traducida del JSON del Informe) ---
// Nota: Hemos ajustado la escala vertical para que quepan en la pantalla de 600px
const vector<DatosVolcan> CATALOGO_AREQUIPA = {
    // --- LOS GIGANTES ---
    { "volcan_misti", "Misti", "Estratovolcan Activo", 5822, 260, 400, {110, 105, 100, 255}, CONO_PERFECTO, true, false }, // Gris Andesítico
    { "volcan_chachani", "Chachani", "Complejo Volcanico", 6057, 350, 420, {140, 110, 90, 255}, ESTRATO_COMPLEJO, true, false }, // Marrón Rojizo
    { "volcan_pichu", "Pichu Pichu", "Volcan Extinto", 5664, 450, 300, {80, 70, 90, 255}, ESTRATO_COMPLEJO, false, false }, // Violeta Oscuro
    { "volcan_sabancaya", "Sabancaya", "ACTIVO (Peligro)", 5976, 200, 410, {192, 192, 192, 255}, CONO_PERFECTO, true, true },  // Gris Ceniza + HUMO
    { "volcan_coropuna", "Coropuna", "Complejo Glaciar", 6425, 480, 450, {255, 255, 250, 255}, MESETA_DOMICA, true, false }, // Blanco Puro
    { "volcan_hualca", "Hualca Hualca", "Colapso Sectorial", 6025, 300, 415, {160, 82, 45, 255}, CONO_COLAPSADO, true, false }, // Sienna
    { "volcan_solimana", "Solimana", "Pared Vertical", 6093, 310, 420, {47, 47, 47, 255}, PARED_VERTICAL, true, false }, // Gris Oscuro
    
    // --- EL ENJAMBRE MONOGENÉTICO (Pequeños) ---
    { "volcan_nicholson", "Nicholson", "Cono de Escoria", 2533, 100, 150, {20, 20, 20, 255}, CONO_MONOGENETICO, false, false }, // Negro Puro
    { "volcan_puca", "Puca Mauras", "Cono Oxidado", 4262, 120, 200, {165, 42, 42, 255}, CONO_MONOGENETICO, false, false }, // Rojo Oxido
    { "volcan_chilcayoc", "Chilcayoc", "Cono Aportillado", 3347, 110, 180, {50, 50, 50, 255}, CONO_COLAPSADO, false, false } // Gris Oscuro
};

// Objeto dinámico en juego
struct VolcanActivo {
    DatosVolcan datos;
    float x; 
    // Sistema de partículas simple para volcanes activos
    float humoOffset[5]; // Variación para animar el humo
};

// ----------------------------------------------------------------------------------
// 2. MOTOR DE AUDIO (MicInput Pro)
// ----------------------------------------------------------------------------------
enum GameScreen { MENU_CALIBRACION, JUEGO, FINAL };

class InputStrategy {
public:
    virtual void update() = 0;
    virtual float getFuerzaSalto() = 0;
    virtual string getNombre() = 0;
    virtual void dibujarCalibracion(int x, int y) = 0;
    virtual ~InputStrategy() {}
};

class TecladoInput : public InputStrategy {
public:
    void update() override {} 
    float getFuerzaSalto() override {
        if (IsKeyPressed(KEY_SPACE)) return 10.0f;
        return 0.0f;
    }
    string getNombre() override { return "MODO: TECLADO"; }
    void dibujarCalibracion(int x, int y) override {
        DrawText("Prueba presionar [ESPACIO]", x, y, 20, DARKGRAY);
        if (IsKeyDown(KEY_SPACE)) DrawText("¡DETECTADO!", x + 280, y, 20, GREEN);
    }
};

class MicInput : public InputStrategy {
private:
    HWAVEIN hWaveIn;
    static const int NUM_BUFFERS = 2;
    static const int BUFFER_SIZE = 1024;
    WAVEHDR waveHeaders[NUM_BUFFERS];
    short buffers[NUM_BUFFERS][BUFFER_SIZE];
    float volumenActual, umbral, maxRuidoDetectado;
    bool calibrando;
    double tiempoInicioCalibracion;

public:
    MicInput() {
        volumenActual = 0.0f; umbral = 3000.0f; calibrando = false; maxRuidoDetectado = 0.0f;
        WAVEFORMATEX wfx; wfx.wFormatTag = WAVE_FORMAT_PCM; wfx.nChannels = 1; wfx.nSamplesPerSec = 48000; wfx.nAvgBytesPerSec = 48000 * 2; wfx.nBlockAlign = 2; wfx.wBitsPerSample = 16; wfx.cbSize = 0;
        if (waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
            wfx.nSamplesPerSec = 44100; wfx.nAvgBytesPerSec = 44100 * 2; waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
        }
        for (int i = 0; i < NUM_BUFFERS; ++i) {
            ZeroMemory(&waveHeaders[i], sizeof(WAVEHDR)); waveHeaders[i].lpData = (LPSTR)buffers[i]; waveHeaders[i].dwBufferLength = BUFFER_SIZE * 2;
            waveInPrepareHeader(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR)); waveInAddBuffer(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
        }
        waveInStart(hWaveIn);
    }
    ~MicInput() { waveInStop(hWaveIn); for (int i = 0; i < NUM_BUFFERS; ++i) waveInUnprepareHeader(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR)); waveInClose(hWaveIn); }
    
    void update() override {
        for (int i = 0; i < NUM_BUFFERS; ++i) {
            if (waveHeaders[i].dwFlags & WHDR_DONE) {
                double suma = 0; for (int j = 0; j < BUFFER_SIZE; j++) suma += abs(buffers[i][j]); 
                float lectura = (float)(suma / BUFFER_SIZE) * 30.0f;
                volumenActual = volumenActual * 0.7f + lectura * 0.3f;
                waveInAddBuffer(hWaveIn, &waveHeaders[i], sizeof(WAVEHDR));
            }
        }
        if (calibrando) {
            if (volumenActual > maxRuidoDetectado) maxRuidoDetectado = volumenActual;
            if (GetTime() - tiempoInicioCalibracion > 3.0) { calibrando = false; umbral = maxRuidoDetectado * 1.5f; if (umbral < 2000) umbral = 2000; }
        } else {
            float vel = 50.0f; if (IsKeyDown(KEY_LEFT_SHIFT)) vel = 500.0f;
            if (IsKeyDown(KEY_UP)) umbral += vel; if (IsKeyDown(KEY_DOWN) && umbral > vel) umbral -= vel;
            if (IsKeyPressed(KEY_C)) { calibrando = true; maxRuidoDetectado = 0; tiempoInicioCalibracion = GetTime(); }
        }
    }
    float getFuerzaSalto() override { if (!calibrando && volumenActual > umbral) return 10.0f; return 0.0f; }
    string getNombre() override { return "MODO: MICROFONO PRO"; }
    void dibujarCalibracion(int x, int y) override {
        if (calibrando) { DrawText("CALIBRANDO...", x, y, 25, ORANGE); DrawRectangle(x, y + 40, (int)(GetTime() * 100) % 300, 20, ORANGE); return; }
        DrawText("PANEL DE AUDIO", x, y - 20, 20, DARKGRAY);
        Color col = (volumenActual > umbral) ? GREEN : RED;
        DrawText(TextFormat("VOL: %.0f", volumenActual), x, y + 20, 30, DARKGRAY);
        DrawText((volumenActual > umbral) ? "¡SALTA!" : "...", x + 250, y + 20, 30, col);
        int w = 500; DrawRectangle(x - 5, y + 75, w + 10, 50, BLACK);
        float pct = volumenActual / 30000.0f;
        DrawRectangle(x, y + 80, (int)(w * pct), 40, (pct > 0.8) ? RED : GREEN);
        int xUmb = x + (int)(w * (umbral / 30000.0f));
        DrawRectangle(xUmb, y + 70, 4, 60, SKYBLUE);
        DrawText("UMBRAL", xUmb - 20, y + 50, 10, SKYBLUE);
        DrawText("[C] Calibrar  |  [Flechas] Ajustar", x, y + 140, 20, DARKGRAY);
    }
};

// ----------------------------------------------------------------------------------
// 3. MAIN LOOP
// ----------------------------------------------------------------------------------
int main() {
    InitWindow(1000, 600, "Andesite Engine: Arequipa Geology"); 
    InitAudioDevice(); 
    SetTargetFPS(60);

    GameScreen pantallaActual = MENU_CALIBRACION;
    InputStrategy* control = new TecladoInput();
    bool modoMicrofono = false;

    float birdY = 300.0f;
    float velocity = 0.0f;
    float gravity = 0.35f; 
    
    vector<VolcanActivo> volcanes;
    double ultimoSpawn = 0;
    float velocidadJuego = 3.0f; 
    int volcanesEsquivados = 0;

    while (!WindowShouldClose()) {
        control->update();

        switch (pantallaActual) {
            case MENU_CALIBRACION:
                if (IsKeyPressed(KEY_M)) {
                    delete control;
                    modoMicrofono = !modoMicrofono;
                    control = modoMicrofono ? (InputStrategy*)new MicInput() : (InputStrategy*)new TecladoInput();
                }
                if (IsKeyPressed(KEY_R)) {
                    birdY = 300.0f; velocity = 0.0f; volcanes.clear();
                    volcanesEsquivados = 0; velocidadJuego = 3.0f; pantallaActual = JUEGO;
                }
                birdY = 300 + sin(GetTime()*5) * 10; 
                break;

            case JUEGO:
                // --- FÍSICAS MEJORADAS (Con rebote en techo) ---
                if (control->getFuerzaSalto() > 0) velocity = -8.0f;
                velocity += gravity;
                birdY += velocity;

                // 1. REBOTE EN TECHO (No muere, solo choca)
                if (birdY < -20) { birdY = -20; velocity = 0; }
                
                // 2. MUERTE SOLO EN SUELO
                if (birdY > 600) pantallaActual = FINAL;

                // --- GENERACIÓN PROCEDURAL DE VOLCANES ---
                if (GetTime() - ultimoSpawn > 2.5) {
                    int index = GetRandomValue(0, CATALOGO_AREQUIPA.size() - 1);
                    VolcanActivo nuevo;
                    nuevo.datos = CATALOGO_AREQUIPA[index];
                    nuevo.x = 1050; 
                    // Inicializar partículas de humo random
                    for(int k=0; k<5; k++) nuevo.humoOffset[k] = (float)GetRandomValue(0, 20);
                    volcanes.push_back(nuevo);
                    ultimoSpawn = GetTime();
                    if (velocidadJuego < 7.0f) velocidadJuego += 0.05f;
                }

                for (int i = 0; i < volcanes.size(); i++) {
                    volcanes[i].x -= velocidadJuego;

                    // --- HITBOXES SEGÚN MORFOLOGÍA ---
                    // Simplificamos las colisiones a Rectángulos ajustados por ahora
                    Rectangle hitbox;
                    hitbox.x = volcanes[i].x - (volcanes[i].datos.anchoBasePx / 4);
                    hitbox.y = 600 - volcanes[i].datos.altoVisualPx;
                    hitbox.width = volcanes[i].datos.anchoBasePx / 2;
                    hitbox.height = volcanes[i].datos.altoVisualPx;
                    
                    // Ajuste para Mesetas (Coropuna es más ancho arriba)
                    if (volcanes[i].datos.tipo == MESETA_DOMICA) {
                        hitbox.width = volcanes[i].datos.anchoBasePx * 0.7f;
                        hitbox.x = volcanes[i].x - (hitbox.width / 2);
                    }

                    Vector2 centroPajaro = { 200, birdY };
                    if (CheckCollisionCircleRec(centroPajaro, 15, hitbox)) pantallaActual = FINAL;

                    if (volcanes[i].x < 180 && volcanes[i].x > 180 - velocidadJuego) volcanesEsquivados++;
                }
                if (!volcanes.empty() && volcanes[0].x < -500) volcanes.erase(volcanes.begin());
                break;

            case FINAL:
                if (IsKeyPressed(KEY_R)) pantallaActual = MENU_CALIBRACION;
                break;
        }

        // --- DIBUJADO (RENDERER) ---
        BeginDrawing();
        ClearBackground(SKYBLUE); 

        if (pantallaActual == MENU_CALIBRACION) {
            DrawText("ANDESITE ENGINE: CONFIG", 320, 20, 30, DARKBLUE);
            DrawText(control->getNombre().c_str(), 350, 60, 20, BLACK);
            control->dibujarCalibracion(250, 150);
            DrawCircle(150, (int)birdY, 20, MAROON);
            DrawText("[M] Micrófono/Teclado  |  [R] Iniciar Misión", 280, 500, 20, DARKGRAY);
        }
        else if (pantallaActual == JUEGO) {
            DrawCircle(900, 80, 40, GOLD);

            // DIBUJAR VOLCANES (Polimorfismo Visual)
            for (auto &v : volcanes) {
                Vector2 baseCenter = { v.x, 600 };
                float h = v.datos.altoVisualPx;
                float w = v.datos.anchoBasePx;

                // 1. DIBUJAR CUERPO SEGÚN TIPO
                if (v.datos.tipo == MESETA_DOMICA || v.datos.tipo == PARED_VERTICAL) {
                    // Trapecio / Bloque (Coropuna, Solimana)
                    float topWidth = (v.datos.tipo == PARED_VERTICAL) ? w : w * 0.6f;
                    Vector2 p1 = { v.x - topWidth/2, 600 - h }; // Top Izq
                    Vector2 p2 = { v.x - w/2, 600 };            // Base Izq
                    Vector2 p3 = { v.x + w/2, 600 };            // Base Der
                    Vector2 p4 = { v.x + topWidth/2, 600 - h }; // Top Der
                    DrawTriangle(p1, p2, p3, v.datos.colorCuerpo);
                    DrawTriangle(p1, p3, p4, v.datos.colorCuerpo);
                    
                    // Nieve plana arriba
                    if (v.datos.tieneNieve) {
                        DrawRectangle(v.x - topWidth/2, 600 - h, topWidth, 40, WHITE);
                    }
                } 
                else if (v.datos.tipo == CONO_COLAPSADO) {
                     // Asimétrico (Hualca Hualca)
                    Vector2 p1 = { v.x + w/4, 600 - h }; // Punta desplazada
                    Vector2 p2 = { v.x - w/2, 600 };
                    Vector2 p3 = { v.x + w/2, 600 };
                    DrawTriangle(p1, p2, p3, v.datos.colorCuerpo);
                }
                else {
                    // Conos Estándar (Misti, Nicholson, etc)
                    Vector2 p1 = { v.x, 600 - h };
                    Vector2 p2 = { v.x - w/2, 600 };
                    Vector2 p3 = { v.x + w/2, 600 };
                    DrawTriangle(p1, p2, p3, v.datos.colorCuerpo);

                    // Nieve en la punta
                    if (v.datos.tieneNieve) {
                        Vector2 n2 = { v.x - w/6, 600 - h * 0.75f };
                        Vector2 n3 = { v.x + w/6, 600 - h * 0.75f };
                        DrawTriangle(p1, n2, n3, RAYWHITE);
                    }
                }

                // 2. EFECTOS ACTIVOS (Humo Sabancaya)
                if (v.datos.esActivo) {
                    for(int k=0; k<5; k++) {
                        float time = GetTime() * 2 + k;
                        float ySmoke = (600 - h) - (int)(time * 50) % 150; 
                        float xSmoke = v.x + sin(time) * 20;
                        DrawCircle(xSmoke, ySmoke, 10 + k*2, {100, 100, 100, 150}); // Gris transparente
                    }
                }

                // 3. ETIQUETAS EDUCATIVAS
                DrawText(v.datos.nombre.c_str(), v.x - 40, 600 - 40, 20, WHITE);
                DrawText(v.datos.clasificacion.c_str(), v.x - 50, 600 - 20, 10, LIGHTGRAY);
                DrawText(TextFormat("%d m", v.datos.alturaReal), v.x - 30, 600 - 60, 10, YELLOW);
            }

            // Pájaro
            DrawCircle(200, (int)birdY, 15, MAROON);
            DrawCircle(205, (int)birdY-5, 5, WHITE);
            if (velocity < 0) DrawEllipse(190, (int)birdY+2, 8, 4, BLACK);

            // HUD
            DrawText(TextFormat("Hitos Geológicos: %d", volcanesEsquivados), 20, 20, 25, DARKBLUE);
        } 
        else if (pantallaActual == FINAL) {
            ClearBackground(BLACK); 
            DrawText("MISIÓN ABORTADA", 300, 200, 50, RED);
            DrawText(TextFormat("Muestras recolectadas: %d", volcanesEsquivados), 320, 280, 20, WHITE);
            DrawText("[R] REINICIAR EXPEDICIÓN", 350, 400, 20, GRAY);
            DrawCircle(500, 500, 20, MAROON);
        }

        EndDrawing();
    }

    delete control;
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
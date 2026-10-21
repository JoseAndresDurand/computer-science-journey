#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map> // <--- NUEVO: Para gestionar el diccionario de texturas

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

// ==================================================================================
// 1. GEOLOGÍA COMPUTACIONAL
// ==================================================================================
enum TipoMorfologia { 
    CONO_PERFECTO, ESTRATO_COMPLEJO, MESETA_DOMICA, CONO_COLAPSADO, PARED_VERTICAL, CONO_MONOGENETICO 
};

struct DatosVolcan {
    string id; string nombre; string clasificacion;
    int alturaReal; float anchoBasePx; float altoVisualPx;
    Color colorCuerpo; TipoMorfologia tipo; bool tieneNieve; bool esActivo;
};

// IDs deben coincidir con los nombres de tus archivos .png (sin la extensión)
const vector<DatosVolcan> CATALOGO_AREQUIPA = {
    { "volcan_misti", "Misti", "Estratovolcan Activo", 5822, 260, 400, {110, 105, 100, 255}, CONO_PERFECTO, true, false },
    { "volcan_chachani", "Chachani", "Complejo Volcanico", 6057, 350, 420, {140, 110, 90, 255}, ESTRATO_COMPLEJO, true, false },
    { "volcan_pichu", "Pichu Pichu", "Volcan Extinto", 5664, 450, 300, {80, 70, 90, 255}, ESTRATO_COMPLEJO, false, false },
    { "volcan_sabancaya", "Sabancaya", "ACTIVO (Peligro)", 5976, 200, 410, {192, 192, 192, 255}, CONO_PERFECTO, true, true },
    { "volcan_coropuna", "Coropuna", "Complejo Glaciar", 6425, 480, 450, {255, 255, 250, 255}, MESETA_DOMICA, true, false },
    { "volcan_hualca", "Hualca Hualca", "Colapso Sectorial", 6025, 300, 415, {160, 82, 45, 255}, CONO_COLAPSADO, true, false },
    { "volcan_solimana", "Solimana", "Pared Vertical", 6093, 310, 420, {47, 47, 47, 255}, PARED_VERTICAL, true, false },
    { "volcan_nicholson", "Nicholson", "Cono de Escoria", 2533, 100, 150, {20, 20, 20, 255}, CONO_MONOGENETICO, false, false },
    { "volcan_puca", "Puca Mauras", "Cono Oxidado", 4262, 120, 200, {165, 42, 42, 255}, CONO_MONOGENETICO, false, false },
    { "volcan_chilcayoc", "Chilcayoc", "Cono Aportillado", 3347, 110, 180, {50, 50, 50, 255}, CONO_COLAPSADO, false, false }
};

struct VolcanActivo {
    DatosVolcan datos;
    float x; 
    float humoOffset[5];
    bool yaContado;
};

// ==================================================================================
// 2. PERSONAJE: CÓNDOR
// ==================================================================================
struct Condor {
    Texture2D textura;
    Rectangle frameRec;
    int currentFrame;
    float frameCounter, frameSpeed, rotation;

    void Init() {
        textura = LoadTexture("condor_spritesheet.png");
        frameRec = { 0.0f, 0.0f, (float)textura.width/4, (float)textura.height };
        currentFrame = 0; frameCounter = 0.0f; frameSpeed = 8.0f; rotation = 0.0f;
    }

    void Update(float velocity) {
        frameCounter += GetFrameTime();
        if (velocity < -2.0f) { 
            rotation = -25.0f; frameSpeed = 12.0f;
            if (frameCounter >= (1.0f/frameSpeed)) { frameCounter = 0.0f; currentFrame = (currentFrame == 0) ? 1 : 0; }
        } else if (velocity > 2.0f) { 
            rotation = 35.0f; currentFrame = 3;
        } else { 
            rotation = velocity * 5.0f; currentFrame = 2;
        }
        frameRec.x = (float)currentFrame * frameRec.width;
    }

    void Draw(Vector2 position) {
        float targetWidth = 90.0f; 
        float scaleFactor = targetWidth / frameRec.width;
        float targetHeight = frameRec.height * scaleFactor;
        Rectangle destRec = { position.x - (targetWidth / 2.0f), position.y - (targetHeight / 2.0f), targetWidth, targetHeight };
        Vector2 origin = { targetWidth / 2.0f, targetHeight / 2.0f };
        DrawTexturePro(textura, frameRec, destRec, origin, rotation, WHITE);
    }
    void Unload() { UnloadTexture(textura); }
};

// ==================================================================================
// 3. MOTOR DE AUDIO & INPUT
// ==================================================================================
enum GameScreen { MENU_CALIBRACION, JUEGO, FINAL };

class InputStrategy {
public:
    virtual void update() = 0;
    virtual float getFuerzaSalto() = 0;
    virtual string getNombre() = 0;
    virtual void dibujarCalibracion(int x, int y, float gravedadActual) = 0;
    virtual ~InputStrategy() {}
};

class TecladoInput : public InputStrategy {
public:
    void update() override {} 
    float getFuerzaSalto() override {
        if (IsKeyPressed(KEY_SPACE)) return 12.0f;
        return 0.0f;
    }
    string getNombre() override { return "MODO: TECLADO"; }
    
    void dibujarCalibracion(int x, int y, float gravedadActual) override {
        DrawText("PANEL DE TECLADO", x + 40, y - 30, 20, DARKGRAY);
        DrawText("Prueba presionar [ESPACIO] para saltar", x, y, 20, DARKGRAY);
        if (IsKeyDown(KEY_SPACE)) {
            const char* texto = "¡DETECTADO!";
            int ancho = MeasureText(texto, 20);
            DrawText(texto, x + (MeasureText("Prueba presionar [ESPACIO] para saltar", 20)/2) - (ancho/2), y + 30, 20, GREEN);
        }
        DrawText(TextFormat("[W/S] Ajustar Gravedad: %.2f", gravedadActual), x + 30, y + 80, 15, DARKBLUE);
    }
};

class MicInput : public InputStrategy {
private:
    HWAVEIN hWaveIn;
    static const int NUM_BUFFERS = 2; static const int BUFFER_SIZE = 1024;
    WAVEHDR waveHeaders[NUM_BUFFERS]; short buffers[NUM_BUFFERS][BUFFER_SIZE];
    float volumenActual, umbral, maxRuidoDetectado;
    bool calibrando; double tiempoInicioCalibracion;

public:
    MicInput() {
        volumenActual = 0.0f; umbral = 3000.0f; calibrando = false; maxRuidoDetectado = 0.0f;
        WAVEFORMATEX wfx; wfx.wFormatTag = WAVE_FORMAT_PCM; wfx.nChannels = 1; wfx.nSamplesPerSec = 48000; wfx.nAvgBytesPerSec = 48000 * 2; wfx.nBlockAlign = 2; wfx.wBitsPerSample = 16; wfx.cbSize = 0;
        if (waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) { wfx.nSamplesPerSec = 44100; wfx.nAvgBytesPerSec = 44100 * 2; waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL); }
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
    float getFuerzaSalto() override { if (!calibrando && volumenActual > umbral) return 12.0f; return 0.0f; }
    string getNombre() override { return "MODO: MICROFONO PRO"; }
    
    void dibujarCalibracion(int x, int y, float gravedadActual) override {
        int anchoPanel = 500;
        int centroPanelX = x + anchoPanel / 2;
        if (calibrando) { 
            const char* txtCal = "CALIBRANDO RUIDO DE FONDO...";
            DrawText(txtCal, centroPanelX - MeasureText(txtCal, 25)/2, y, 25, ORANGE); 
            DrawRectangle(x, y + 40, (int)(GetTime() * 200) % anchoPanel, 20, ORANGE); 
            return; 
        }
        DrawText("PANEL DE AUDIO", centroPanelX - MeasureText("PANEL DE AUDIO", 20)/2, y - 30, 20, DARKGRAY);
        Color col = (volumenActual > umbral) ? GREEN : RED;
        DrawText(TextFormat("VOL: %.0f", volumenActual), x + 20, y + 20, 30, DARKGRAY);
        DrawText((volumenActual > umbral) ? "¡SALTA!" : "...", x + 350, y + 20, 30, col);
        DrawRectangle(x, y + 75, anchoPanel, 50, BLACK);
        float pct = volumenActual / 30000.0f; 
        DrawRectangle(x + 5, y + 80, (int)((anchoPanel-10) * pct), 40, (pct > 0.8) ? RED : GREEN);
        int xUmb = x + (int)(anchoPanel * (umbral / 30000.0f)); 
        DrawRectangle(xUmb, y + 70, 4, 60, SKYBLUE);
        DrawText("UMBRAL", xUmb - 20, y + 50, 10, SKYBLUE);
        const char* txtFlechas = "[FLECHAS ARRIBA/ABAJO] Ajustar Umbral Manualmente";
        DrawText(txtFlechas, centroPanelX - MeasureText(txtFlechas, 15)/2, y + 140, 15, DARKGRAY);
        const char* txtCalib = "[C] Calibrar Automatico (3 seg)";
        DrawText(txtCalib, centroPanelX - MeasureText(txtCalib, 15)/2, y + 165, 15, DARKGRAY);
        const char* txtGrav = TextFormat("[W/S] Ajustar Gravedad General: %.2f", gravedadActual);
        DrawText(txtGrav, centroPanelX - MeasureText(txtGrav, 15)/2, y + 200, 15, DARKBLUE);
    }
};

// ==================================================================================
// 4. MAIN LOOP
// ==================================================================================
int main() {
    InitWindow(1000, 600, "Flappy Condor [Arequipa Edition]"); 
    InitAudioDevice(); 
    SetTargetFPS(60);

    Condor condor; condor.Init();

    // --- NUEVO: GESTOR DE TEXTURAS DE VOLCANES ---
    map<string, Texture2D> texturasVolcanes;
    
    // Cargar texturas (El nombre del archivo debe coincidir con el ID + .png)
    // Si no encuentra la imagen, usará el color por defecto (Fallback)
    for (const auto& v : CATALOGO_AREQUIPA) {
        string filename = v.id + ".png"; 
        texturasVolcanes[v.id] = LoadTexture(filename.c_str());
    }

    GameScreen pantallaActual = MENU_CALIBRACION;
    InputStrategy* control = new TecladoInput();
    bool modoMicrofono = false;

    float birdY = 300.0f; float velocity = 0.0f; 
    float gravity = 0.4f; 
    
    vector<VolcanActivo> volcanes;
    double ultimoSpawn = 0; float velocidadJuego = 3.0f; 
    int volcanesEsquivados = 0;

    VolcanActivo mistiMenu;
    mistiMenu.datos = CATALOGO_AREQUIPA[0];
    mistiMenu.x = 750; 

    while (!WindowShouldClose()) {
        control->update();

        if (IsKeyPressed(KEY_W)) gravity -= 0.05f;
        if (IsKeyPressed(KEY_S)) gravity += 0.05f;
        if (gravity < 0.1f) gravity = 0.1f;
        if (gravity > 0.8f) gravity = 0.8f;

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
                birdY = 300 + sin(GetTime()*3) * 20; 
                condor.Update(sin(GetTime()*3)*2); 
                break;

            case JUEGO: {
                if (control->getFuerzaSalto() > 0) velocity = -10.0f;
                velocity += gravity; birdY += velocity;

                if (birdY < -20) { birdY = -20; velocity = 0; }
                condor.Update(velocity);

                if (GetTime() - ultimoSpawn > 2.5) {
                    int index = GetRandomValue(0, CATALOGO_AREQUIPA.size() - 1);
                    VolcanActivo nuevo; nuevo.datos = CATALOGO_AREQUIPA[index]; nuevo.x = 1050; 
                    for(int k=0; k<5; k++) nuevo.humoOffset[k] = (float)GetRandomValue(0, 20);
                    nuevo.yaContado = false;
                    volcanes.push_back(nuevo);
                    ultimoSpawn = GetTime(); if (velocidadJuego < 7.0f) velocidadJuego += 0.05f;
                }

                Vector2 picoCondor, patasCondor;
                Vector2 centroPajaro = { 200, birdY };

                if (velocity > 2.0f) { 
                    picoCondor = { centroPajaro.x - 20, centroPajaro.y - 20 }; 
                    patasCondor = { centroPajaro.x - 20, centroPajaro.y - 20 };
                } else { 
                    picoCondor = { centroPajaro.x - 60, centroPajaro.y - 60 }; 
                    patasCondor = { centroPajaro.x - 60, centroPajaro.y - 60 }; 
                }

                if (picoCondor.y >= 625 || patasCondor.y >= 625) pantallaActual = FINAL;

                for (int i = 0; i < volcanes.size(); i++) {
                    volcanes[i].x -= velocidadJuego;

                    if (!volcanes[i].yaContado && volcanes[i].x < 200) {
                        volcanesEsquivados++;
                        volcanes[i].yaContado = true;
                    }

                    float h = volcanes[i].datos.altoVisualPx; float w = volcanes[i].datos.anchoBasePx;
                    bool huboColision = false;

                    // Colisión física (Siempre geométrica para precisión)
                    if (volcanes[i].datos.tipo == PARED_VERTICAL || volcanes[i].datos.tipo == MESETA_DOMICA) {
                        Rectangle hitboxRect = { volcanes[i].x - (w * 0.7f) / 2, 600 - h, w * 0.5f, h };
                        if (CheckCollisionPointRec(picoCondor, hitboxRect) || CheckCollisionPointRec(patasCondor, hitboxRect)) huboColision = true;
                    } else {
                        Vector2 p1 = { volcanes[i].x, 600 - h }; Vector2 p2 = { volcanes[i].x - w/2, 600 }; Vector2 p3 = { volcanes[i].x + w/2, 600 };
                        if (CheckCollisionPointTriangle(picoCondor, p1, p2, p3) || CheckCollisionPointTriangle(patasCondor, p1, p2, p3)) huboColision = true;
                    }
                    if (huboColision) pantallaActual = FINAL;
                }
                if (!volcanes.empty() && volcanes[0].x < -500) volcanes.erase(volcanes.begin());
                break;
            }
            case FINAL:
                if (IsKeyPressed(KEY_R)) pantallaActual = MENU_CALIBRACION;
                break;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE); 

        if (pantallaActual == MENU_CALIBRACION) {
            DrawText("FLAPPY CONDOR", 220, 50, 60, DARKBLUE);
            DrawText("[ AREQUIPA EDITION ]", 340, 110, 30, RED);

            // MISTI DECORATIVO (Usamos la textura si existe, si no, fallback geométrico)
            Texture2D texMisti = texturasVolcanes["volcan_misti"];
            if (texMisti.id > 0) { // ¿Se cargó la textura?
                Rectangle dest = { mistiMenu.x - 130, 600 - 400, 260, 400 }; // Dimensiones del Misti
                DrawTexturePro(texMisti, {0,0,(float)texMisti.width,(float)texMisti.height}, dest, {0,0}, 0, WHITE);
            } else {
                // Fallback antiguo
                Vector2 p1 = { mistiMenu.x, 200 }; Vector2 p2 = { mistiMenu.x - 130, 600 }; Vector2 p3 = { mistiMenu.x + 130, 600 };
                DrawTriangle(p1, p2, p3, mistiMenu.datos.colorCuerpo);
            }
            
            DrawRectangle(mistiMenu.x - 60, 540, 120, 50, ColorAlpha(BLACK, 0.6f));
            DrawText("Misti", mistiMenu.x - 20, 545, 20, WHITE);
            DrawText("5822 m", mistiMenu.x - 20, 565, 10, YELLOW);

            condor.Draw({350, birdY});
            control->dibujarCalibracion(250, 250, gravity);

            DrawRectangle(100, 480, 450, 30, LIGHTGRAY);
            DrawText("Presiona [M] para cambiar entre MICROFONO y TECLADO", 110, 487, 10, BLACK);
            DrawText("[R] INICIAR JUEGO", 380, 530, 20, DARKGREEN);
            DrawText("EP Ciencia de la Computacion - UNSA - Programacion I - 2025", 220, 580, 15, BLACK);
        }
        else if (pantallaActual == JUEGO) {
            DrawCircle(900, 80, 40, GOLD); 
            for (auto &v : volcanes) {
                float h = v.datos.altoVisualPx; float w = v.datos.anchoBasePx;
                
                // --- RENDERIZADO DE VOLCANES (PIXEL ART vs GEOMETRÍA) ---
                Texture2D tex = texturasVolcanes[v.datos.id];
                
                if (tex.id > 0) {
                    // ¡SI TENEMOS IMAGEN, LA DIBUJAMOS!
                    // Calculamos el rectángulo destino para que coincida con la Hitbox física
                    Rectangle dest = { v.x - w/2, 600 - h, w, h };
                    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
                    DrawTexturePro(tex, source, dest, {0,0}, 0, WHITE);
                } 
                else {
                    // SI NO HAY IMAGEN, DIBUJAMOS LA GEOMETRÍA ORIGINAL (FALLBACK)
                    // (Esto evita que el juego se vea vacío si borras un archivo)
                    Vector2 p1, p2, p3;
                    if (v.datos.tipo == MESETA_DOMICA || v.datos.tipo == PARED_VERTICAL) {
                        float topWidth = (v.datos.tipo == PARED_VERTICAL) ? w : w * 0.6f;
                        p1 = { v.x - topWidth/2, 600 - h }; p2 = { v.x - w/2, 600 }; p3 = { v.x + w/2, 600 }; Vector2 p4 = { v.x + topWidth/2, 600 - h };
                        DrawTriangle(p1, p2, p3, v.datos.colorCuerpo); DrawTriangle(p1, p3, p4, v.datos.colorCuerpo);
                        if (v.datos.tieneNieve) DrawRectangle(v.x - topWidth/2, 600 - h, topWidth, 40, WHITE);
                    } else if (v.datos.tipo == CONO_COLAPSADO) {
                        p1 = { v.x + w/4, 600 - h }; p2 = { v.x - w/2, 600 }; p3 = { v.x + w/2, 600 };
                        DrawTriangle(p1, p2, p3, v.datos.colorCuerpo);
                    } else {
                        p1 = { v.x, 600 - h }; p2 = { v.x - w/2, 600 }; p3 = { v.x + w/2, 600 };
                        DrawTriangle(p1, p2, p3, v.datos.colorCuerpo);
                        if (v.datos.tieneNieve) { Vector2 n2 = Vector2Lerp(p1, p2, 0.25f); Vector2 n3 = Vector2Lerp(p1, p3, 0.25f); DrawTriangle(p1, n2, n3, RAYWHITE); }
                    }
                }

                // Partículas (Humo) - Se dibujan siempre, encima de la imagen
                if (v.datos.esActivo) {
                    for(int k=0; k<5; k++) {
                        float time = GetTime() * 2 + k; float ySmoke = (600 - h) - (int)(time * 50) % 150; float xSmoke = v.x + sin(time) * 20;
                        DrawCircle(xSmoke, ySmoke, 10 + k*2, {100, 100, 100, 150});
                    }
                }
                int anchoNombre = MeasureText(v.datos.nombre.c_str(), 20); int anchoClasif = MeasureText(v.datos.clasificacion.c_str(), 10); int anchoAltura = MeasureText(TextFormat("%d m", v.datos.alturaReal), 10);
                int xNombre = v.x - anchoNombre / 2; int xClasif = v.x - anchoClasif / 2; int xAltura = v.x - anchoAltura / 2; int yBaseTexto = 600 - 60;
                int anchoCaja = max(anchoNombre, max(anchoClasif, anchoAltura)) + 20;
                DrawRectangle(v.x - anchoCaja / 2, yBaseTexto - 5, anchoCaja, 55, ColorAlpha(BLACK, 0.6f));
                DrawText(v.datos.nombre.c_str(), xNombre, yBaseTexto, 20, WHITE); DrawText(v.datos.clasificacion.c_str(), xClasif, yBaseTexto + 22, 10, LIGHTGRAY); DrawText(TextFormat("%d m", v.datos.alturaReal), xAltura, yBaseTexto + 34, 10, YELLOW);
            }
            condor.Draw({200, birdY});
            DrawText(TextFormat("Hitos Geologicos: %d", volcanesEsquivados), 20, 20, 25, DARKBLUE);
            DrawText(TextFormat("Gravedad: %.2f [W/S]", gravity), 20, 50, 15, DARKGRAY);
        } 
        else if (pantallaActual == FINAL) {
            ClearBackground(BLACK); 
            DrawText("VUELO TERMINADO", 300, 200, 50, RED);
            DrawText(TextFormat("Muestras recolectadas: %d", volcanesEsquivados), 320, 280, 20, WHITE);
            DrawText("[R] NUEVA EXPEDICION", 350, 400, 20, GRAY);
            condor.Draw({500, 500});
        }
        EndDrawing();
    }
    
    // --- IMPORTANTE: Descargar texturas de memoria ---
    for (auto& pair : texturasVolcanes) {
        UnloadTexture(pair.second);
    }
    
    condor.Unload(); delete control; CloseAudioDevice(); CloseWindow(); return 0;
}
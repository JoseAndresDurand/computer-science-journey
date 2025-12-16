# 🦅 Flappy Condor [Arequipa Edition]

**Curso:** Programación I - Ciencia de la Computación (UNSA)  
**Año:** 2025  
**Tecnología:** C++ / Raylib  

## 🌋 Descripción
Un videojuego de plataformas y habilidad desarrollado en C++ utilizando la librería gráfica **Raylib**. El jugador controla un **Cóndor Andino** que debe sobrevolar la geografía real de la región de Arequipa.

El proyecto destaca por su integración de conceptos físicos, generación procedural de terreno basada en datos geográficos reales y múltiples métodos de entrada.

## 🎮 Características Principales

* **Motor "Andesite Engine":** Sistema personalizado de físicas y colisiones.
* **Geografía Realista:** Los obstáculos no son aleatorios; son representaciones geométricas basadas en la altura y morfología real de volcanes arequipeños (Misti, Chachani, Coropuna, Sabancaya, etc.).
* **Dual Input System (Strategy Pattern):**
    * ⌨️ **Modo Teclado:** Control clásico con barra espaciadora.
    * 🎤 **Modo Voz (DSP):** Control por amplitud de sonido (soplidos/gritos/aplausos) procesando el buffer de audio en tiempo real.
* **Físicas Ajustables:** Control de gravedad en tiempo real mediante teclas `W` / `S`.
* **Arte Híbrido:** Integración de sprites pixel-art animados (Cóndor) con renderizado geométrico vectorial (Volcanes). En la siguiente versión los volcanes serán en pixel art.

## 🛠️ Controles

| Acción | Tecla / Input |
| :--- | :--- |
| **Volar** | `Espacio` o `Micrófono` (según modo) |
| **Cambiar Input** | Tecla `M` |
| **Aumentar Gravedad** | Tecla `S` |
| **Disminuir Gravedad** | Tecla `W` |
| **Reiniciar** | Tecla `R` |

## 🌋 Volcanes Incluidos
El juego utiliza un catálogo de datos (`struct`) con información real:
* **Misti:** Cono perfecto (5822 m)
* **Chachani:** Complejo volcánico (6057 m)
* **Coropuna:** Meseta glaciar (6425 m)
* **Sabancaya:** Volcán activo con partículas de humo.
* *Y muchos más (Pichu Pichu, Solimana, Nicholson, etc.)*

## 📦 Instalación y Ejecución

1. Descarga la última versión desde la sección **[Releases](https://github.com/JoseAndresDurand/computer-science-journey/releases/latest)**.
2.  Asegúrate de que el archivo `condor_spritesheet.png` esté en la misma carpeta que el `.exe`.
3.  Ejecuta `main.exe`.

## 👨‍💻 Créditos
Desarrollado como proyecto final de investigación formativa (TIF).
**Escuela Profesional de Ciencia de la Computación - UNSA.**

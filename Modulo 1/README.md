# Módulo 1: Primeros Pasos con el LED RGB (NeoPixel)

## Objetivo

Este proyecto es la primera toma de contacto con el entorno de desarrollo PlatformIO y el microcontrolador ESP32-S3. El objetivo es aprender a compilar y subir un programa básico que manipula el hardware de la placa, en este caso, el LED RGB integrado.

## Hardware Utilizado

*   Placa de desarrollo basada en ESP32-S3-N16R8.

## Software y Librerías

*   **Visual Studio Code** con la extensión **PlatformIO IDE**.
*   **Librería `Adafruit NeoPixel`**: Esta librería es necesaria para controlar el LED RGB. PlatformIO la descarga y gestiona automáticamente gracias a la configuración en el archivo `platformio.ini`.

## Descripción del Ejemplo

El programa `src/main.cpp` inicializa el LED RGB integrado en la placa (conocido como NeoPixel) y lo hace cambiar de color en un ciclo infinito. La secuencia de colores es:

1.  **Rojo** (durante 1 segundo)
2.  **Verde** (durante 1 segundo)
3.  **Azul** (durante 1 segundo)

Este ciclo se repite indefinidamente.

## Instrucciones de Uso

1.  Abre esta carpeta de proyecto (`Modulo 1`) con Visual Studio Code.
2.  Conecta la placa ESP32-S3 a tu ordenador mediante un cable USB-C.
3.  Espera a que PlatformIO termine de analizar el proyecto y descargar las dependencias si es la primera vez que lo abres.
4.  En la barra de estado inferior de VSCode, haz clic en el botón **Upload** (el que tiene forma de flecha hacia la derecha).
5.  PlatformIO compilará el código y lo subirá a la placa.
6.  Si todo ha ido bien, verás cómo el LED integrado en la placa comienza a cambiar entre rojo, verde y azul.

---

### Reto para la Práctica: El Ciclo del Arcoíris

Modificar el código existente para que, en lugar de saltar bruscamente entre rojo, verde y azul, el LED transicione suavemente a través de todos los colores del arcoíris. El efecto debería ser un fundido continuo y cíclico de un color a otro (rojo -> naranja -> amarillo -> verde -> cian -> azul -> magenta -> y de vuelta al rojo).

**Pista para los alumnos:** "Para lograr un fundido suave, necesitarás usar bucles `for` para cambiar gradualmente el valor de cada componente de color (Rojo, Verde, Azul) de un estado a otro."

**Ejemplos de definición de colores:**
*   Rojo: `pixels.Color(255, 0, 0)`
*   Verde: `pixels.Color(0, 255, 0)`
*   Azul: `pixels.Color(0, 0, 255)`
*   Amarillo: `pixels.Color(255, 255, 0)`
*   Cian: `pixels.Color(0, 255, 255)`
*   Magenta: `pixels.Color(255, 0, 255)`
*   Blanco: `pixels.Color(255, 255, 255)`
*   Negro (apagado): `pixels.Color(0, 0, 0)`

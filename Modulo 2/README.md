# Módulo 2: Fundamentos de Programación Aplicada

## Objetivo

Este módulo introduce varios conceptos fundamentales de la programación utilizando el hardware de la placa ESP32-S3. A través de una práctica interactiva, el alumno aprenderá a estructurar un programa, manejar estados y responder a entradas del usuario (un botón).

## Hardware Utilizado

*   Placa de desarrollo basada en ESP32-S3-N16R8.
*   LED RGB (NeoPixel) integrado.
*   Botón "BOOT" (GPIO 0) integrado.

## Conceptos de Programación Cubiertos

*   **Variables**: Se usa una variable (`currentMode`) para guardar el estado o "modo" actual del programa.
*   **Entrada Digital (`digitalRead`)**: Leemos el estado del botón integrado para detectar cuándo el usuario lo presiona. Se incluye una técnica simple de antirrebote (debounce) para asegurar una lectura fiable.
*   **Condicionales (`if`, `switch`)**: Se utiliza un `switch` para decidir qué código ejecutar en función del valor de la variable `currentMode`.
*   **Bucles (`for`)**: Se usan bucles para crear secuencias repetitivas, como hacer parpadear un LED un número determinado de veces (Modo 2) o para incrementar/decrementar gradualmente el brillo y generar un efecto de fundido (Modo 3).
*   **Funciones**: El código está organizado en funciones (`changeMode`, `modeOff`, `modeBlink`, `modeFade`) para que sea más legible, reutilizable y fácil de entender.
*   **Comunicación Serie (`Serial.println`)**: Se envían mensajes al monitor serie del ordenador para dar información sobre lo que está ocurriendo en el programa (ej: "Cambiando a Modo 2").

## Descripción del Ejemplo

El programa implementa una "máquina de estados" simple con 3 modos. Se empieza en el Modo 1. Cada vez que se pulsa el botón "BOOT" (GPIO 0), el programa cambia al siguiente modo.

*   **Modo 1: Espera**. El LED está apagado. El programa espera a que se pulse el botón.
*   **Modo 2: Parpadeo Rojo**. Al entrar en este modo, el LED parpadea 3 veces en color rojo. Al terminar la secuencia, vuelve automáticamente al Modo 1.
*   **Modo 3: Fundido Azul**. Al entrar en este modo, el LED aumenta su brillo gradualmente hasta llegar a un punto medio y luego lo disminuye hasta apagarse, todo en color azul. Al terminar, vuelve automáticamente al Modo 1.

## Instrucciones de Uso

1.  Abre la carpeta `Modulo 2` con VSCode.
2.  Conecta la placa ESP32-S3 a tu ordenador.
3.  Haz clic en el botón **Upload** de PlatformIO.
4.  Abre el **Serial Monitor** (Monitor Serie) para ver los mensajes de estado.
5.  Pulsa el botón "BOOT" (etiquetado como "0" en algunas placas) para cambiar entre los modos.

---

### Reto para la Práctica: ¡Crea tu Propio Modo!

Añade un **Modo 4** al programa con un patrón de luz de tu propia creación.

**Pasos sugeridos:**

1.  **Incrementa la variable `totalModes` a 4.**
2.  **Añade un `case 4:`** en la estructura `switch` del `loop()` que llame a una nueva función, por ejemplo, `modeCustom()`.
3.  **Crea la nueva función `void modeCustom()`**. Dentro de esta función, programa el comportamiento del LED que desees.
4.  **¡Sé creativo!** Algunas ideas:
    *   Un parpadeo rápido en color amarillo.
    *   Un ciclo que alterna entre dos colores (ej: magenta y cian).
    *   Un "latido" (dos parpadeos rápidos y una pausa).
    *   Intenta crear un color naranja o morado.

Recuerda hacer que tu función, al igual que las otras, vuelva al `currentMode = 1` al finalizar para que el ciclo pueda empezar de nuevo.

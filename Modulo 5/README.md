# Modulo 5: Anillo LED RGB (WS2812B)

Este módulo contiene el código para controlar un anillo LED RGB de 32 píxeles, comúnmente conocido como NeoPixel.

## Funcionalidad

El código principal (`src/main.cpp`) inicializa el anillo de LEDs y ejecuta un efecto de arcoíris continuo.

## Conexiones

- **GPIO 2**: Conectar al pin de datos (DIN) del anillo LED.
- **5V**: Conectar al pin de alimentación (5V) del anillo.
- **GND**: Conectar al pin de tierra (GND) del anillo.

## Librerías

- `Adafruit NeoPixel`

Esta librería se instala automáticamente gracias al archivo `platformio.ini`.

## Reto/Práctica

Implementar el control del anillo LED RGB a través de una conexión Wi-Fi, permitiendo cambiar colores o efectos de forma remota.

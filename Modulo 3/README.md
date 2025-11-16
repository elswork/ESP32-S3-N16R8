
# Módulo 3: Interactuando con el Mundo Físico: Sensores y Entradas

¡Bienvenido al Módulo 3! Ya has aprendido a controlar un actuador (el LED NeoPixel) para que tu placa "hable" con el mundo. Ahora es el momento de enseñarle a "escuchar". En esta sección, exploraremos cómo leer información del entorno utilizando sensores y entradas, un paso fundamental para crear proyectos verdaderamente interactivos.

Conectaremos componentes que nos permitirán detectar acciones simples, como presionar un botón, y medir valores continuos, como la intensidad de la luz.

## 1. El Botón: Tu Primera Interacción (Entradas Digitales)

La forma más sencilla de entrada es una **entrada digital**. Piensa en ella como un interruptor de luz: solo tiene dos estados, encendido (HIGH) o apagado (LOW). Un botón es el ejemplo perfecto.

Para leer un botón con el ESP32, lo conectaremos a un pin GPIO y lo configuraremos como una entrada. Usaremos la resistencia `PULLUP` interna del ESP32, que simplifica enormemente el circuito. Cuando el botón no está presionado, el pin leerá `HIGH` (alto). Cuando lo presiones, conectarás el pin a tierra (GND), y leerá `LOW` (bajo).

### Vibe Coding Prompt: Controlar LED con Botón

> "Escribe un código para la ESP32-S3-N16R8 que configure el LED NeoPixel integrado y un botón en el pin GPIO 1. Usa la resistencia PULLUP interna para el botón. En el bucle principal, si se presiona el botón (el pin lee LOW), el LED debe encenderse en color verde. Si no está presionado (el pin lee HIGH), el LED debe estar apagado."

### Proyecto: Encender el LED con un Botón

Este código implementa la lógica de nuestro prompt. Necesitarás un botón pulsador simple, con una pata conectada al pin 1 y la otra a cualquier pin GND de tu placa.

```cpp
#include <Adafruit_NeoPixel.h>

// Configuración del LED NeoPixel
#define PIN_NEOPIXEL 48
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Configuración del botón
#define BUTTON_PIN 1

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.clear(); // Apaga el pixel al iniciar

  // Configura el pin del botón como una entrada con resistencia PULLUP interna
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Lee el estado del botón.
  // Será LOW si está presionado y HIGH si no lo está.
  int buttonState = digitalRead(BUTTON_PIN);

  // Imprime el estado en el monitor serie para depuración
  Serial.print("Estado del botón: ");
  Serial.println(buttonState);

  if (buttonState == LOW) {
    // Botón presionado: enciende el LED en verde
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
  } else {
    // Botón no presionado: apaga el LED
    pixels.clear();
    pixels.show();
  }

  // Una pequeña pausa para evitar el "rebote" del botón (debouncing)
  delay(50);
}
```

**Nota sobre el "Debouncing":** Los botones mecánicos, al presionarse, pueden rebotar y generar múltiples señales rápidas. El `delay(50)` es una forma simple de mitigar esto. En proyectos más complejos, se usan técnicas más avanzadas.

## 2. El Potenciómetro: Control Fino (Entradas Analógicas)

A diferencia de las entradas digitales, las **entradas analógicas** pueden leer un rango de valores. Piensa en un regulador de volumen en lugar de un interruptor. Un potenciómetro es un componente perfecto para esto.

El ESP32-S3 tiene un Convertidor Analógico-Digital (ADC) que puede leer un voltaje y convertirlo en un número. Por defecto, este número va de **0** (para 0 voltios) a **4095** (para 3.3 voltios).

### Vibe Coding Prompt: Controlar Brillo con Potenciómetro

> "Crea un código para la ESP32-S3 que lea el valor de un potenciómetro conectado al pin 2. Usa ese valor para controlar el brillo del LED NeoPixel integrado. Como el valor del potenciómetro va de 0 a 4095 y el brillo del LED va de 0 a 255, mapea el rango del potenciómetro al rango del brillo."

### Proyecto: Regular el Brillo del LED

Para este proyecto, conecta la pata central de un potenciómetro al pin 2, y las otras dos patas a 3.3V y GND respectivamente.

```cpp
#include <Adafruit_NeoPixel.h>

// Configuración del LED NeoPixel
#define PIN_NEOPIXEL 48
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Configuración del potenciómetro
#define POT_PIN 2

void setup() {
  Serial.begin(115200);
  pixels.begin();
  // No es necesario configurar el pin para entrada analógica
}

void loop() {
  // Lee el valor analógico del potenciómetro (0-4095)
  int potValue = analogRead(POT_PIN);

  // Mapea el valor del potenciómetro al rango de brillo del LED (0-255)
  int brightness = map(potValue, 0, 4095, 0, 255);

  Serial.print("Valor Pot: ");
  Serial.print(potValue);
  Serial.print(" -> Brillo: ");
  Serial.println(brightness);

  // Establece el color del LED (ej. blanco) con el brillo calculado
  pixels.setPixelColor(0, pixels.Color(brightness, brightness, brightness));
  pixels.show();

  delay(100);
}
```

La función `map()` es increíblemente útil. Toma un valor de un rango de entrada y lo convierte a un rango de salida. ¡La usarás a menudo!

## Resumen del Módulo

¡Felicidades! Tu placa ahora puede percibir y reaccionar a su entorno. Has aprendido a:

1.  **Leer entradas digitales** usando un botón y la configuración `INPUT_PULLUP`.
2.  **Leer entradas analógicas** con `analogRead()` para obtener un rango de valores.
3.  **Usar la función `map()`** para escalar valores de un rango a otro.

Ahora tienes las herramientas para crear proyectos mucho más dinámicos, como luces que se encienden con un botón, controladores personalizados o sistemas que reaccionan a mediciones del mundo real.

## Próximos Pasos

En el próximo módulo, daremos un salto gigante y conectaremos nuestro ESP32 a redes Wi-Fi. ¡Prepárate para entrar de lleno en el **Internet de las Cosas (IoT)**!

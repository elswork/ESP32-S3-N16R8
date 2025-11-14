#include <Adafruit_NeoPixel.h>

// El pin donde está conectado el LED Neopixel. En muchas placas ESP32-S3
// es el pin 48. Si no funciona, otros comunes son 2 o 18.
#define NEOPIXEL_PIN 48

// Número de LEDs en la tira (para el LED integrado, es 1).
#define NUM_PIXELS 1

// Inicializa la librería NeoPixel.
// Parámetros: (número de píxeles, pin, tipo de píxel + velocidad)
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Inicializa la comunicación con el Neopixel.
  pixels.setBrightness(20); // Ajusta el brillo (0-255). Un valor bajo es bueno para empezar.
}

void loop() {

  // Color Rojo
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show(); // Envía el color al LED.
  delay(1000);

  // Color Verde
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
  delay(1000);

  // Color Azul
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  delay(1000);

}
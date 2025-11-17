#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Pin donde se conecta la entrada de datos del anillo LED
#define LED_PIN 2

// Número de LEDs en el anillo
#define LED_COUNT 32

// Declaración del objeto NeoPixel
// Argumento 1: Número de píxeles en la tira
// Argumento 2: Pin de Arduino donde se conecta (la mayoría de las veces llamado DIN)
// Argumento 3: Banderas de tipo de píxel:
//   NEO_GRB     - Píxeles cableados para GRB (la mayoría de los NeoPixels WS2812)
//   NEO_KHZ800  - Flujo de 800 KHz (la mayoría de los NeoPixels basados en WS2811, WS2812)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void rainbow(int wait);
uint32_t Wheel(byte WheelPos);

void setup() {
  // Inicializa la comunicación serial para depuración
  Serial.begin(115200);
  
  // Inicializa la librería NeoPixel
  strip.begin();
  strip.show(); // Inicializa todos los píxeles a 'off'
  strip.setBrightness(50); // Ajusta el brillo a un valor seguro (0-255)
}

void loop() {
  // Ejecuta un ciclo de arcoíris
  rainbow(10);
}

// Llena la tira de LEDs con colores de un arcoíris
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

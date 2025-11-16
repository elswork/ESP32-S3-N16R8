
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
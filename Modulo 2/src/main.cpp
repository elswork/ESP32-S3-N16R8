#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// --- Pines y Constantes ---
#define NEOPIXEL_PIN 48 // Pin del LED RGB integrado
#define BUTTON_PIN 0    // Pin del botón "BOOT" integrado
#define NUM_PIXELS 1    // Número de LEDs

// --- Instancia de NeoPixel ---
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// --- Variables Globales (Estado) ---
int currentMode = 1; // Variable para almacenar el modo actual
int totalModes = 3;  // Número total de modos

// Variables para el antirrebote (debounce) del botón
long lastDebounceTime = 0;
long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState;

// Variables para el temporizador de inactividad
unsigned long lastActivityTime = 0;
const long idleTimeout = 5000; // 5 segundos para volver al modo reposo

// Variables para modeBlink no bloqueante
int blinkCount = 0;
int ledState = LOW;
unsigned long previousMillisBlink = 0;
const long intervalBlink = 250;

// Variables para modeFade no bloqueante
int fadeBrightness = 0;
int fadeAmount = 5;
unsigned long previousMillisFade = 0;
const long intervalFade = 50;
int fadeCycleCount = 0;

// --- Prototipos de Funciones ---
void changeMode();
void modeOff();
void modeBlink();
void modeFade();

// --- Configuración Inicial ---
void setup() {
  Serial.begin(115200); // Iniciar comunicación serie
  Serial.println("Módulo 2: Fundamentos de Programación");

  pixels.begin();           // Iniciar el LED RGB
  pixels.setBrightness(20); // Ajustar brillo

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configurar el pin del botón como entrada con resistencia pull-up

  Serial.println("Modo 1: LED Apagado. Pulsa el botón para cambiar.");
  lastActivityTime = millis(); // Iniciar temporizador de actividad
}

// --- Bucle Principal ---
void loop() {
  // 1. Comprobar si debe volver al modo de reposo por inactividad
  if (currentMode != 1 && (millis() - lastActivityTime > idleTimeout)) {
    Serial.println("Volviendo a modo de reposo por inactividad.");
    currentMode = 1;
    pixels.clear();
    pixels.show();
  }

  // 2. Leer el estado del botón con antirrebote
  int reading = digitalRead(BUTTON_PIN);

  // Si el estado del botón ha cambiado, reiniciar el temporizador de antirrebote
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Si ha pasado suficiente tiempo desde el último cambio, procesar el estado
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si el estado del botón ha cambiado
    if (reading != buttonState) {
      buttonState = reading;

      // Si el botón ha sido PRESIONADO (LOW con PULLUP)
      if (buttonState == LOW) {
        changeMode(); // Cambiar de modo
      }
    }
  }

  lastButtonState = reading;

  // 3. Ejecutar el código del modo actual
  switch (currentMode) {
    case 1:
      modeOff();
      break;
    case 2:
      modeBlink();
      break;
    case 3:
      modeFade();
      break;
  }
}

// --- Definición de Funciones ---

/**
 * @brief Cambia al siguiente modo y lo imprime en el puerto serie.
 */
void changeMode() {
  currentMode++;
  if (currentMode > totalModes) {
    currentMode = 1; // Volver al primer modo
  }

  Serial.print("Cambiando a Modo ");
  Serial.println(currentMode);

  // Reset state for non-blocking modes
  if (currentMode == 2) {
    blinkCount = 0;
    ledState = LOW;
    previousMillisBlink = 0; // Reset timer
  } else if (currentMode == 3) {
    fadeBrightness = 0;
    fadeAmount = 5;
    previousMillisFade = 0;
    fadeCycleCount = 0; // Resetear el contador de ciclos del fade
  }

  // Apagar el LED al cambiar de modo para limpiar el estado anterior
  pixels.clear();
  pixels.show();

  lastActivityTime = millis(); // Reiniciar temporizador en cada cambio de modo
}

/**
 * @brief MODO 1: Mantiene el LED apagado.
 */
void modeOff() {
  // El LED ya se apaga en changeMode(), así que no es necesario hacer nada aquí.
  // Esta función se deja para claridad estructural.
}

/**
 * @brief MODO 2: Hace parpadear el LED en color rojo 3 veces.
 *        Usa un bucle 'for'.
 */
void modeBlink() {
  if (blinkCount < 6) { // 3 blinks (on/off is 6 states)
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisBlink >= intervalBlink) {
      previousMillisBlink = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;
        pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Rojo
        pixels.show();
      } else {
        ledState = LOW;
        pixels.clear();
        pixels.show();
      }
      blinkCount++;
      lastActivityTime = millis(); // Reiniciar temporizador mientras parpadea
    }
  }
  // After 3 blinks, the animation stops and the LED remains off.
  // The device will stay in mode 2 until the button is pressed again or timeout.
}

/**
 * @brief MODO 3: Realiza un efecto de fundido (fade in/out) con el color azul.
 *        Usa bucles 'for' para controlar el brillo.
 */
void modeFade() {
  // La animación solo se ejecuta si no ha completado un ciclo de fade-in/out
  if (fadeCycleCount < 2) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillisFade >= intervalFade) {
      previousMillisFade = currentMillis;
      pixels.setPixelColor(0, pixels.Color(0, 0, fadeBrightness));
      pixels.show();
      fadeBrightness = fadeBrightness + fadeAmount;
      if (fadeBrightness <= 0 || fadeBrightness >= 150) {
        fadeAmount = -fadeAmount; // Invertir la dirección del fade
        fadeCycleCount++;         // Incrementar el contador de ciclos
      }
      lastActivityTime = millis(); // Reiniciar temporizador mientras hace el fade
    }
  }
}

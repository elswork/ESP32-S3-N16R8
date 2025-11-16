// Archivo: src/main.cpp
#include <WiFi.h>
#include "secrets.h" // ¡Importante incluir nuestro archivo de secretos!

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Esperamos a que la conexión se establezca
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("¡Conexión Wi-Fi establecida!");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // No necesitamos hacer nada en el loop por ahora
}

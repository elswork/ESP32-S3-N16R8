# Módulo 4: Conectando tu Proyecto al Mundo con Wi-Fi

¡Este es el módulo donde todo se une! Has aprendido a controlar salidas y leer entradas. Ahora, vamos a darle a tu ESP32 el superpoder de la conectividad. En esta sección, conectarás tu placa a una red Wi-Fi y crearás un servidor web para controlar tu proyecto desde cualquier dispositivo en la misma red, como tu teléfono o tu ordenador.

¡Bienvenido al verdadero **Internet de las Cosas (IoT)**!

## 1. Conexión a una Red Wi-Fi

El primer paso para cualquier proyecto de IoT es conectarse a Internet. El ESP32 hace que este proceso sea muy sencillo.

**¡Importante! La seguridad de tus credenciales:** Nunca escribas el nombre y la contraseña de tu red Wi-Fi directamente en el código principal, especialmente si planeas compartirlo. Una práctica recomendada es guardar esta información sensible en un archivo separado (por ejemplo, `secrets.h`) y decirle a tu sistema de control de versiones (Git) que lo ignore.

### Vibe Coding Prompt: Conectar a Wi-Fi

> "Escribe un código para la ESP32-S3-N16R8 que se conecte a una red Wi-Fi. Las credenciales (SSID y contraseña) deben leerse desde un archivo `secrets.h`. Una vez conectado, el programa debe imprimir la dirección IP asignada en el Monitor Serie."

### Proyecto: Conectar el ESP32 a tu Red

1.  **Crea el archivo `secrets.h`:** Dentro de la carpeta `include` de tu proyecto, crea un archivo llamado `secrets.h` con el siguiente contenido, reemplazando los valores con los de tu propia red.

    ```h
    // Archivo: include/secrets.h
    #define SECRET_SSID "ElNombreDeTuRed"
    #define SECRET_PASS "LaContraseñaDeTuRed"
    ```

2.  **Actualiza `.gitignore`:** Asegúrate de que la línea `include/secrets.h` esté en tu archivo `.gitignore` para no subir tus credenciales a un repositorio público.

3.  **Carga el código principal:** Este código se conectará a la red usando las credenciales que definiste.

    ```cpp
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
    ```

## 2. Tu Primer Servidor Web

Una vez conectado, tu ESP32 puede actuar como un servidor web. Puede "escuchar" peticiones de navegadores web (clientes) y enviarles respuestas, como una página web en formato HTML.

### Vibe Coding Prompt: Crear un Servidor Web Básico

> "Crea un código para la ESP32-S3 que, después de conectarse a Wi-Fi, inicie un servidor web. Cuando un navegador acceda a la dirección IP del ESP32, el servidor debe responder con una página HTML que diga 'Hola desde mi ESP32'."

### Proyecto: Servidor "Hola Mundo"

Este código crea un servidor en el puerto 80 (el puerto estándar para HTTP) y responde a todas las peticiones a la ruta raíz (`/`).

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

// Creamos una instancia del servidor en el puerto 80
WebServer server(80);

void handleRoot() {
  String html = "<html><body><h1>Hola desde mi ESP32</h1></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a Wi-Fi.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Definimos la función que manejará las peticiones a la ruta raíz
  server.on("/", handleRoot);

  // Iniciamos el servidor
  server.begin();
  Serial.println("Servidor web iniciado.");
}

void loop() {
  // El servidor necesita procesar las peticiones entrantes
  server.handleClient();
}
```

Después de cargar este código, abre un navegador web en un dispositivo conectado a la misma red e introduce la dirección IP de tu ESP32. ¡Deberías ver tu mensaje!

## 3. Control Remoto del LED vía Web

Ahora, combinemos todo: usaremos el servidor web para controlar el hardware que ya conocemos, como el LED NeoPixel.

### Vibe Coding Prompt: Controlar LED desde el Navegador

> "Mejora el servidor web del ESP32-S3 para controlar el LED NeoPixel integrado. La página principal ('/') debe mostrar dos enlaces HTML: 'Encender LED' y 'Apagar LED'. El primer enlace debe ir a la ruta '/on', que encenderá el LED en color azul. El segundo debe ir a '/off', que apagará el LED."

### Proyecto: Interfaz Web para el LED

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "secrets.h"

// --- Configuración de Wi-Fi y Servidor ---
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
WebServer server(80);

// --- Configuración del LED NeoPixel ---
#define PIN_NEOPIXEL 48
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// --- Funciones del Servidor Web ---
void handleRoot() {
  String html = "<html><head><title>Control LED</title></head><body>";
  html += "<h1>Controlar LED del ESP32</h1>";
  html += "<p><a href='/on'><button>Encender LED</button></a></p>";
  html += "<p><a href='/off'><button>Apagar LED</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLedOn() {
  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // Azul
  pixels.show();
  server.send(200, "text/plain", "LED encendido!");
}

void handleLedOff() {
  pixels.clear();
  pixels.show();
  server.send(200, "text/plain", "LED apagado!");
}

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();

  // Conexión Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.print("IP: "); Serial.println(WiFi.localIP());

  // Rutas del servidor
  server.on("/", handleRoot);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
```

## Resumen del Módulo

¡Lo has logrado! Tu dispositivo ya no es una isla. Ahora puede conectarse a una red, alojar una interfaz de control y ser manejado de forma remota. En este módulo has aprendido a:

1.  **Conectar tu ESP32 a una red Wi-Fi** de forma segura.
2.  **Crear un servidor web** capaz de servir páginas HTML.
3.  **Definir rutas** para ejecutar diferentes funciones de tu código.
4.  **Controlar hardware** (el LED) a través de una interfaz web simple.

## Próximos Pasos

Has adquirido todas las habilidades fundamentales del curso. El siguiente y último paso es combinar todo lo que has aprendido (salidas, entradas y conectividad) para construir un **proyecto final** que resuelva un problema o cree algo único. ¡Es hora de ser creativo!

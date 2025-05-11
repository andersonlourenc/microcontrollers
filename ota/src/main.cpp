#include <WiFi.h>
#include <WebServer.h>
#include <Update.h>
#include "secrets.h"

WebServer server(80);

const int ledPin = 2;
bool ledState = false;

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <h1>Dispositivo atualizado com sucesso!</h1>
    <p>Este é o novo firmware OTA.</p>
    <form method='POST' action='/update' enctype='multipart/form-data'>
      <input type='file' name='update'>
      <input type='submit' value='Atualizar novamente'>
    </form>
  )rawliteral");
}

void handleUpdate() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.println("Iniciando atualização OTA...");
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) {
      Serial.println("Atualização concluída com sucesso!");
      server.send(200, "text/plain", "Atualização concluída!");
    } else {
      Update.printError(Serial);
      server.send(500, "text/plain", "Erro na atualização!");
    }
    delay(1000);
    ESP.restart();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Novo firmware rodando! IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/update", HTTP_POST, []() {
    server.send(200, "text/plain", "Atualizando...");
  }, handleUpdate);
  server.begin();
}

void loop() {
  server.handleClient();

  // Pisca o LED a cada segundo para indicar que está rodando o novo firmware
  static unsigned long lastToggle = 0;
  if (millis() - lastToggle > 1000) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    lastToggle = millis();
  }
}

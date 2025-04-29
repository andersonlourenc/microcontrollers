#include <WiFi.h>
#include <PubSubClient.h>
#include "secrets.h" 

// Configurações do broker MQTT
#define MQTT_SERVER "broker.mqtt.cool"
#define PORT 1883

WiFiClient espClient;
PubSubClient client(espClient);

// Definições dos pinos dos LEDs
#define RED 18
#define GREEN 19
#define BLUE 21

void callback(char* topic, byte* message, unsigned int length);

void setup() {
  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid); // Corrigido para minúsculo

  WiFi.begin(ssid, password); // Corrigido para minúsculo

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  client.setServer(MQTT_SERVER, PORT);
  client.setCallback(callback);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "led_algum") {
    Serial.print("Changing output to ");
    if (messageTemp == "red") {
      Serial.println("red");
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
    }
    else if (messageTemp == "green") {
      Serial.println("green");
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
    }
    else if (messageTemp == "blue") {
      Serial.println("blue");
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
    }
  }
  else if (String(topic) == "mensagem_mensagem") {
    Serial.print("Conteúdo da mensagem: ");
    Serial.println(messageTemp);
    Serial.println();
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Nome único para o cliente (não pode ter dois dispositivos com o mesmo nome conectando)
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("led_algum");
      client.subscribe("mensagem_mensagem"); // Corrigido aqui!
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(". Trying again in 5 seconds...");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

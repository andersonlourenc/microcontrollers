#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "secrets.h" 


#define BUTTON 34
#define CAR_LED_RED 2     
#define CAR_LED_GREEN 16  
#define PED_LED_RED 12    
#define PED_LED_GREEN 27  

#define CROSS_TIME 4000  
#define YELLOW_TIME 2000 
#define DEBOUNCE_TIME 200 

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

unsigned long lastPress = 0;

void carGo() {
  digitalWrite(CAR_LED_RED, LOW);
  digitalWrite(CAR_LED_GREEN, HIGH);
  delay(5000);
}

void carAttention() {
  digitalWrite(CAR_LED_GREEN, HIGH); 
  digitalWrite(CAR_LED_RED, HIGH);
  delay(YELLOW_TIME);
}

void carStop() {
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_RED, HIGH);
}

void pedestrianGo() {
  digitalWrite(PED_LED_RED, LOW);
  digitalWrite(PED_LED_GREEN, HIGH);
  delay(CROSS_TIME);
}

void pedestrianStop() {
  digitalWrite(PED_LED_GREEN, LOW);
  for (int i = 0; i < 3; i++) {
    digitalWrite(PED_LED_RED, LOW);
    delay(500);
    digitalWrite(PED_LED_RED, HIGH);
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(CAR_LED_RED, OUTPUT);
  pinMode(CAR_LED_GREEN, OUTPUT);
  pinMode(PED_LED_RED, OUTPUT);
  pinMode(PED_LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);  // Ativo em HIGH

  // 🟢 Inicializa semáforo logo de cara!
  digitalWrite(PED_LED_RED, HIGH);
  digitalWrite(PED_LED_GREEN, LOW);
  carGo();

  // 🌐 Conectar Wi-Fi depois dos LEDs
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setInsecure();

  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi conectado!");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "🤖 Semáforo iniciado com sucesso!", "");
}

void loop() {
  if (digitalRead(BUTTON) == HIGH && millis() - lastPress > DEBOUNCE_TIME) {
    lastPress = millis();

    Serial.println("🚨 Botão pressionado!");
    bot.sendMessage(CHAT_ID, "🚦 Botão de pedestre acionado! Iniciando travessia...", "");

    carAttention();
    carStop();
    pedestrianGo();
    pedestrianStop();

    // Volta ao estado inicial
    digitalWrite(PED_LED_RED, HIGH);
    carGo();
  }
}

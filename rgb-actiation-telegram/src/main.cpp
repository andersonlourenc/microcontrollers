#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include "secrets.h" // ssid, password, BOT_TOKEN, CHAT_ID

#define RED_PIN     14
#define GREEN_PIN   12
#define BLUE_PIN    27   

#define TELEGRAM_BOT_TOKEN BOT_TOKEN
#define WIFI_SSID ssid
#define WIFI_PASSWORD password

WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);
unsigned long last_check = 0;

void initWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(
    "\nWi-Fi connected. IP: " + WiFi.localIP().toString());
}



String handleMessage(String msg) {
  msg.toLowerCase();

  if (msg == "/red") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    return "🔴 LED: Red";
  } else if (msg == "/green") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    return "🟢 LED: Green";   

  } else if (msg == "/blue") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    return "🔵 LED: Blue";

  } else if (msg == "/white") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);

    return "⚪ LED: White";

  } else if (msg == "/off") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);  // All OFF
    return "LED Off";
  } else {
    return 
    "❌ Invalid command.\nUse: /red, /green, /blue, /white or /off";
    }
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);


  // Initially turned off
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW); 
  initWiFi();
  client.setInsecure(); 
}

void loop() {
  if (millis() - last_check > 1000) {
    int numMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numMessages) {
      for (int i = 0; i < numMessages; i++) {
        String response = handleMessage(bot.messages[i].text);
        bot.sendMessage(bot.messages[i].chat_id, response, "");
      }
      numMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    last_check = millis();
  }
}

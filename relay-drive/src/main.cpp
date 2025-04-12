#include <Arduino.h>
#include <Wifi.h>
#include <WifiClientSecure.h>
#include <UniversalTelegramBot.h>

#import "secrets.h"


#define RELE 23



WiFiClientSecure client;
UniversalTelegramBot bot(BOTTOKEN, client);


#define DELAY 1000
unsigned long lastTimeBotRan;


void handleNewMessages(int);

void setup() {


  Serial.begin(9600);

  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);

  // Connecting to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() > lastTimeBotRan + DELAY)  { // 1000 ms for delay
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}

// put function definitions here:
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i< numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHATID){
      bot.sendMessage(chat_id, "Usuário não autorizado.", "");
      continue;
    }
    
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Bem-vindo, " + from_name + ".\n";
      welcome += "Use os seguintes comandos para controlar o LED.\n\n";
      welcome += "/led_on para ligar o LED. \n";
      welcome += "/led_off para desligar o LED. \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, "O LED está ligado.", "");
      digitalWrite(RELE, HIGH);
    }
    
    if (text == "/led_off") {
      bot.sendMessage(chat_id, "O LED está desligado.", "");
      digitalWrite(RELE, LOW);
    }
  }
}
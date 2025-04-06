#include <Arduino.h>

#define BUTTON 35

#define CAR_LED_RED 2     
#define CAR_LED_GREEN 16  

#define PED_LED_RED 12    
#define PED_LED_GREEN 27  

#define CROSS_TIME 4000  
#define YELLOW_TIME 2000 
#define DEBOUNCE_TIME 200 

void carGo() {
  digitalWrite(CAR_LED_RED, LOW);
  digitalWrite(CAR_LED_GREEN, HIGH);
  delay(6000);
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
  pinMode(CAR_LED_RED, OUTPUT);
  pinMode(CAR_LED_GREEN, OUTPUT);
  pinMode(PED_LED_RED, OUTPUT);
  pinMode(PED_LED_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLDOWN);

  // Estado inicial correto: primeiro acende o vermelho do pedestre
  digitalWrite(PED_LED_RED, HIGH);
  digitalWrite(PED_LED_GREEN, LOW);
  
  carGo(); // Agora chamamos carGo() depois de garantir o vermelho do pedestre
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    delay(DEBOUNCE_TIME); // Debounce

    carAttention();
    carStop();
    pedestrianGo();
    pedestrianStop();

    // Volta ao estado inicial
    digitalWrite(PED_LED_RED, HIGH);
    carGo();
  }
}

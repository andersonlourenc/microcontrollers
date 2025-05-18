#include <Arduino.h>

#define RED 12
#define GREEN 27
#define BLUE 25



void setup() {

  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {

  
  // yellow
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 0);
  delay(3000);

  // purple
  analogWrite(RED, 158);
  analogWrite(GREEN, 10);
  analogWrite(BLUE, 149);
  delay(3000);

  // orange
  analogWrite(RED, 251);
  analogWrite(GREEN, 64);
  analogWrite(BLUE, 3);
  delay(3000);
}



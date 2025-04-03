#include <Arduino.h>

#define red   2  
#define green 16   


void setup() {
 pinMode(red, OUTPUT);
 pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(green, HIGH);
  delay(4000);

  digitalWrite(red, HIGH);
  delay(1500);
  digitalWrite(green, LOW);

  delay(4000);
  digitalWrite(red, LOW);
  
}

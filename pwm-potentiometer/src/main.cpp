#include <Arduino.h>

const int pinLed = 2; // Adjust if needed for your board
const int pinPotentiometer = 34; // ADC pin
const int channelPWM = 0;
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup started...");
  pinMode(pinLed, OUTPUT);
  ledcSetup(channelPWM, freq, resolution);
  ledcAttachPin(pinLed, channelPWM);
  Serial.println("Setup complete.");
}

void loop() {
  int valueAnalogic = analogRead(pinPotentiometer);
  int brightness = map(valueAnalogic, 0, 4095, 0, 255);
  ledcWrite(channelPWM, brightness);

  Serial.print("Potentiometer: ");
  Serial.print(valueAnalogic);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(100);
}
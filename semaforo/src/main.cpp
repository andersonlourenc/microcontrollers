#include <Arduino.h>
#define BUTTON 19
#define CAR_LED_RED 21
#define CAR_LED_GREEN 22
#define CAR_LED_BLUE 23
#define PEDESTRIAN_LED_RED 33
#define PEDESTRIAN_LED_GREEN 32
#define PEDESTRIAN_LED_BLUE 26
#define SLEEP 5000
#define ATTENTION 2000

// put function declarations here:
void carRun();
void carAttention();
void pedestrianRun();
void pedestrianAttention();

void setup() {
  // put your setup code here, to run once:
  pinMode(CAR_LED_RED, OUTPUT);
  pinMode(CAR_LED_GREEN, OUTPUT);
  pinMode(CAR_LED_BLUE, OUTPUT);
  pinMode(PEDESTRIAN_LED_RED, OUTPUT);
  pinMode(PEDESTRIAN_LED_GREEN, OUTPUT);
  pinMode(PEDESTRIAN_LED_BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON) == HIGH) {
    carAttention();
    pedestrianRun();
    pedestrianAttention();
  } else {
    carRun();
  }
}

// put function definitions here:
void carRun() {
  digitalWrite(CAR_LED_RED, LOW);
  digitalWrite(CAR_LED_GREEN, HIGH);
  digitalWrite(CAR_LED_BLUE, LOW);
  digitalWrite(PEDESTRIAN_LED_RED, HIGH);
  digitalWrite(PEDESTRIAN_LED_GREEN, LOW);
  digitalWrite(PEDESTRIAN_LED_BLUE, LOW);
}

void carAttention() {
  digitalWrite(CAR_LED_RED, LOW);
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_BLUE, HIGH);
  digitalWrite(PEDESTRIAN_LED_RED, HIGH);
  digitalWrite(PEDESTRIAN_LED_GREEN, LOW);
  digitalWrite(PEDESTRIAN_LED_BLUE, LOW);
  delay(ATTENTION);
};

void pedestrianRun() {
  digitalWrite(CAR_LED_RED, HIGH);
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_BLUE, LOW);
  digitalWrite(PEDESTRIAN_LED_RED, LOW);
  digitalWrite(PEDESTRIAN_LED_GREEN, HIGH);
  digitalWrite(PEDESTRIAN_LED_BLUE, LOW);
  delay(SLEEP);
};

void pedestrianAttention() {
  digitalWrite(CAR_LED_RED, HIGH);
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_BLUE, LOW);
  digitalWrite(PEDESTRIAN_LED_RED, LOW);
  digitalWrite(PEDESTRIAN_LED_GREEN, LOW);
  digitalWrite(PEDESTRIAN_LED_BLUE, HIGH);
  delay(ATTENTION);
};

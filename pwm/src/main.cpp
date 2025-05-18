#include <Arduino.h>


const int redPin = 21;  
const int greenPin = 22;  
const int bluePin = 23;  

const int freq = 5000;
const int resolution = 8;


void setup() {

  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop(){
  analogWrite(redPin, 234);
  analogWrite(greenPin, 234);
  analogWrite(bluePin, 50);


  for(int brightness = 0; brightness <= 255; brightness++){   

    analogWrite(redPin, brightness);
    analogWrite(greenPin, (brightness * 234) / 255);
    analogWrite(greenPin, (brightness * 234) / 255);
    delay(15);
  }


  for(int brightness = 255; brightness >= 0; brightness--){
  
    analogWrite(redPin, brightness);
    analogWrite(greenPin, (brightness * 234) / 255);
    analogWrite(greenPin, (brightness * 234) / 255);
    delay(15);
  }
}
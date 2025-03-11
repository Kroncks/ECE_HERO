#include <Arduino.h>

#define LED 13

void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("Hourah");
}

void loop() {
  digitalWrite(LED,HIGH);
}


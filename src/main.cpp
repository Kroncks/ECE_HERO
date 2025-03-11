#include <Arduino.h>

#define NOTE A5
int note;

void setup() {
  pinMode(NOTE,INPUT);
  Serial.begin(9600);
}

void loop() {
  note=analogRead(NOTE);
  Serial.println(note);
  delay(500);
}


#include <Arduino.h>
#include <MsTimer2.h>

int tempo=900; // (delay)

void bpm() {
  digitalWrite(8, HIGH); 
  delay(100); 
  digitalWrite(8, LOW); 
}

unsigned long prev_time = 0;

void rising();

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT); // metronome 
  MsTimer2::set(tempo, bpm); 
  MsTimer2::start();
  attachInterrupt(0, rising, RISING);
  delay(600);
}

void loop() {}

void rising() {
  Serial.println(micros()-prev_time);
  prev_time = micros();
}
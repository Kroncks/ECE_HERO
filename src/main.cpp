#include <Arduino.h>
#include <MsTimer2.h>

volatile unsigned long prevTime = 0;

static unsigned long lastInterruptTime;
unsigned long currentTime;
unsigned long lastSignalTime = 0;
volatile int period = -1;
float frequency = 0;
const unsigned long TIMEOUT = 100000;
volatile unsigned long buffer = 0;
unsigned int frequencies[8] = {258, 289, 330, 353, 392, 441, 495, 523};
volatile boolean firstRising = true;
int tempo=900; // (delay)
volatile int note;

void bpm() {
  digitalWrite(8, HIGH); 
  delay(100); 
  digitalWrite(8, LOW); 
}

int note();
void rising();
void checkFinNote();


void setup() {
  Serial.begin(9600);
  //*
  pinMode(8, OUTPUT); // metronome 
  MsTimer2::set(tempo, bpm); 
  MsTimer2::start();
  //*/
  attachInterrupt(0, rising, RISING);
  delay(600);
}


void loop() {
  checkFinNote();
  if(period!=-1){
    frequency =  1000000.0 / period;
    Serial.println(note());
  }
}

void rising() {
  lastInterruptTime = 0;
  currentTime = micros();
  
  if (currentTime - lastInterruptTime > 100) {
    lastSignalTime = currentTime;
    
    if (firstRising) {
      prevTime = lastSignalTime;
      firstRising = false;
    } else { 
      period = lastSignalTime - prevTime;
      prevTime = lastSignalTime;
    }
    
    lastInterruptTime = currentTime;
  }
}
void checkFinNote() {
  unsigned long currentTime = micros();
  if (currentTime < lastSignalTime) {
    lastSignalTime = currentTime;
  }
  if (currentTime - lastSignalTime > TIMEOUT) {
    period = -1;
    firstRising = true;
  }
}

int note() {
  if (period == -1) return -1; 
  float ecart;
  int num;
  for (int i = 0; i < 8; i++) { 
    if (abs(frequencies[i] - frequency) < ecart) {
      ecart = abs(frequencies[i] - frequency);
      num=i;
    }
  }
  if (ecart>30) return -1; 

  return num;
}
#include <Arduino.h>
#include <MsTimer2.h>
#define IN 5

unsigned long etatHaut;
unsigned long etatBas;
float periode;
float frequence;
float rapportCyclique;

int tempo=1200;

void bpm() {
  digitalWrite(8, HIGH); 
  delay(10); 
  digitalWrite(8, LOW); 
}

void setup() {
  Serial.begin(9600);
  pinMode(IN, INPUT); // calculateur de frequence 
  pinMode(8, OUTPUT); // metronome 
  MsTimer2::set(tempo, bpm); 
  MsTimer2::start();
  delay(600);
}

void loop() {
  etatHaut = pulseIn(IN, HIGH);
  etatBas = pulseIn(IN, LOW);

  periode = etatBas + etatHaut; //calcul de la periode totale en microsecondes 
  frequence = 1000000/periode; // calcul de la frequence 
  rapportCyclique = (etatHaut/periode)*100;// rapprot cyclique (pourcentage)

  Serial.print("Periode : ");
  Serial.println(periode);


  Serial.print("Frequence : ");
  Serial.println(frequence);


  Serial.print("Rapport cyclique : ");
  Serial.println(rapportCyclique);

  Serial.println();
  delay(100);
}





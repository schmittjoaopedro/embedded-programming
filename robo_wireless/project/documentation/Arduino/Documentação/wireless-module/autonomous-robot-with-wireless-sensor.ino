#include <Servo.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int MotorUmPolaridadePositiva = 7;
int MotorUmPolaridadeNegativa = 8;
int MotorDoisPolaridadePositiva = 4;
int MotorDoisPolaridadeNegativa = 2;
int tempo = 0;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

char movimentoDesignado;

void setup(){
 
  pinMode(MotorUmPolaridadePositiva,OUTPUT);
  pinMode(MotorUmPolaridadeNegativa,OUTPUT);
  pinMode(MotorDoisPolaridadePositiva,OUTPUT);
  pinMode(MotorDoisPolaridadeNegativa,OUTPUT);
  

  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}


void loop(){

  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read( &movimentoDesignado, sizeof(unsigned char) );
      if(movimentoDesignado == 'w'){
        AtivaFrente();
        delay(1000);
      }
      if(movimentoDesignado == 'p'){
        AtivaRe();
      }
    }
  }
  else
  {
    Serial.println("Rádio não disponível");
  }
  delay(10);
}

void AtivaFrente(){
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  digitalWrite(MotorUmPolaridadeNegativa, HIGH);
  digitalWrite(MotorDoisPolaridadeNegativa, HIGH);
  delay(tempo);
}

void AtivaRe(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, HIGH);
  digitalWrite(MotorDoisPolaridadePositiva, HIGH);
  delay(tempo);
}

void rotacionarDireita(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, HIGH);
  digitalWrite(MotorUmPolaridadePositiva, HIGH);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  delay(tempo);
}

void rotacionarEsquerda(){
  digitalWrite(MotorUmPolaridadeNegativa, HIGH);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, HIGH);
  delay(tempo);
}

void paraMovimento(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
}


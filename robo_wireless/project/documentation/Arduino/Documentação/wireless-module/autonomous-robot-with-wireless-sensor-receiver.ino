#include <Servo.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int MotorUmPolaridadePositiva = 7;
int MotorUmPolaridadeNegativa = 8;
int MotorDoisPolaridadePositiva = 4;
int MotorDoisPolaridadeNegativa = 2;
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
      Serial.println(movimentoDesignado);
      if(movimentoDesignado == 'w'){
        AtivaFrente();
        done = true;
      }
      if(movimentoDesignado == 's'){
        AtivaRe();
        done = true;
      }
      if(movimentoDesignado == 'a'){
        rotacionarDireita();
        done = true;
      }
      if(movimentoDesignado == 'd'){
        rotacionarEsquerda();
        done = true;
      }
      if(movimentoDesignado == 'p'){
        paraMovimento();
        done = true;
      }
    }
  }
  else
  {
    Serial.println("Nenhum valor recebido");
  }
}

void AtivaFrente(){
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  digitalWrite(MotorUmPolaridadeNegativa, HIGH);
  digitalWrite(MotorDoisPolaridadeNegativa, HIGH);
}

void AtivaRe(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, HIGH);
  digitalWrite(MotorDoisPolaridadePositiva, HIGH);
}

void rotacionarDireita(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, HIGH);
  digitalWrite(MotorUmPolaridadePositiva, HIGH);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
}

void rotacionarEsquerda(){
  digitalWrite(MotorUmPolaridadeNegativa, HIGH);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, HIGH);
}

void paraMovimento(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
}


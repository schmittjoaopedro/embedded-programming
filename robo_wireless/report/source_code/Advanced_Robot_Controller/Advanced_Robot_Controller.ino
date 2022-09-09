/******************************************************************************************
 * |                                                                                      |
 * |            Autor: João Pedro Schmitt                                                 |
 * |                   Emiliano Adamski Stack                                             |  
 * |            Instituição: Católica de Jaraguá do Sul                                   |
 * |            Pesquisa: Robôs Colaborativos com Comunicação sem Fio                     |
 * |            Data: 27/05/2013                                                          |
 * |            Versão: 2.0.1                                                             |
 * |                                                                                      |
 * |            Função: Ser controlado via rádio frêquencia por um controlador            |
 * |            com joystick, e ao detectar um obstáculo no caminho parar e tirar         |
 * |            a melhor métrica desviando o obstáculo evitando uma possivel              |
 * |            colisão.                                                                  |
 * |                                                                                      |
 *****************************************************************************************/

//Inclusão das bibliotecas
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Definição das variáveis
int quantidadeMovimento[3];
const byte PIN_D6 = 6;
const byte PIN_D5 = 5;
const byte PIN_D4 = 4;
const byte PIN_D3 = 3;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int value = 4;

//Inicialização dos controles********************/
void setup(void)                              /**/
{                                             /**/
  //Inicialização da comunicação serial       /**/
  Serial.begin(9600);                         /**/
                                              /**/
  //Inicialização do rádio                    /**/
  radio.begin();                              /**/
  pinMode(PIN_D6, INPUT);                     /**/ 
  pinMode(PIN_D5, INPUT);                     /**/   
  pinMode(PIN_D4, INPUT);                     /**/
  pinMode(PIN_D3, INPUT);                     /**/
  digitalWrite(PIN_D6, HIGH);                 /**/
  digitalWrite(PIN_D5, HIGH);                 /**/
  digitalWrite(PIN_D4, HIGH);                 /**/
  digitalWrite(PIN_D3, HIGH);                 /**/
  radio.openWritingPipe(pipe);                /**/
  quantidadeMovimento[2] = 0;                 /**/   
}                                             /**/
//***********************************************/

//Loop infinito*******************************************************/
void loop(void)                                                    /**/  
{                                                                  /**/  
                                                                   /**/  
  //Leitura dos analogos de movimento                              /**/  
  quantidadeMovimento[0] = analogRead(1);                          /**/
  quantidadeMovimento[1] = analogRead(0);                          /**/
                                                                   /**/
  //Leitura do valor do pino de parada                             /**/
  if(digitalRead(PIN_D6) == LOW){                                  /**/
    value = 4;                                                     /**/
   }                                                               /**/
  else if(digitalRead(PIN_D5) == LOW){                             /**/
    value = 3;                                                     /**/
   }                                                               /**/
  else if(digitalRead(PIN_D4) == LOW){                             /**/
    value = 2;                                                     /**/
   }                                                               /**/
  else if(digitalRead(PIN_D3) == LOW){                             /**/
    value = 1;                                                     /**/
   }                                                               /**/
                                                                   /**/  
  quantidadeMovimento[2] = value;                                  /**/
                                                                   /**/
  //Escrita por rádio frequência                                   /**/
  for(int i = 0; i < 5; i++){                                      /**/
    radio.write( quantidadeMovimento, sizeof(quantidadeMovimento));/**/
  }                                                                /**/
}                                                                  /**/
//********************************************************************/

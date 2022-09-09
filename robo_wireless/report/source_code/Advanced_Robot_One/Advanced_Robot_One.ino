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

/*Bibliotecas de uso*/
#include <Servo.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

/*Variáveis CI Porta Lógica*/
int dataPin = 3;
int latchPin = 2;
int clockPin = 4; 

/*Variáveis rádio frêquencia*/
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;

/*Variável para controlar Servo Motor*/
Servo servoSensor;

/*Variáveis sensor ultrassônico*/
int URPWM=6;                                   
int URTRIG=5;   
unsigned int distancia =0;
unsigned int distanciaMedida =0;
uint8_t EnPwmCmd[4]={
  0x44,0x22,0xbb,0x01}; 

/*Variáveis de uso*/
int tempoRe = 1000;              //Tempo de delay para motores em ré
int tempoRotacao = 500;          //Tempo de delay para motores em rotação
int x,y;                         //Variáveis de mapeamento do controle dos motores
int movimentoDesignado[3];       //Variável para armazenar leitura da radio
int valueFlag = 4;               //Variável para definir o tipo de controle sobre o robô

//Inicialização do arduíno************************
void setup(){                                 /**/
                                              /**/
  //Iniciar sensor ultrasônico                /**/
  ModoPWMSetup();                             /**/
                                              /**/
  /*Configura o servo motor*/                 /**/
  servoSensor.attach(9);                      /**/
                                              /**/
  //Inicia comunicação serial                 /**/
  Serial.begin(9600);                         /**/
                                              /**/
  //Inicialização da rádio frequência         /**/
  radio.begin();                              /**/
  radio.openReadingPipe(1,pipe);              /**/
  radio.startListening();                     /**/
                                              /**/
  //Iniciar CI Porta lógica                   /**/
  pinMode(dataPin, OUTPUT);                   /**/
  pinMode(latchPin, OUTPUT);                  /**/
  pinMode(clockPin, OUTPUT);                  /**/
                                              /**/
  servoSensor.write(90);                      /**/
}                                             /**/
/************************************************/

//Loop eterno*******************************************************************/
void loop(){                                                                 /**/
                                                                             /**/
  //Verifica disponibilidade da comunicação com o rádio                      /**/
  if (radio.available())                                                     /**/
  {                                                                          /**/
    //Imprimi sinal de conexão recebida                                      /**/
    Serial.print("-->");                                                     /**/
    bool done = false;                                                       /**/
                                                                             /**/
    //Enquanto done for falso                                                /**/
    while (!done)                                                            /**/
    {                                                                        /**/
      //Faz leitura dos valores recebidos                                    /**/
      done = radio.read( movimentoDesignado, sizeof(movimentoDesignado));    /**/
                                                                             /**/
      valueFlag = movimentoDesignado[2];                                     /**/   
                                                                             /**/
      //Verifica se o robô será controlado pelo joystick                     /**/
      while(valueFlag == 2 || valueFlag == 4){                               /**/
                                                                             /**/    
        done = radio.read( movimentoDesignado, sizeof(movimentoDesignado));  /**/ 
        x = map(movimentoDesignado[0],0,1023,0,255);                         /**/
        y = map(movimentoDesignado[1],0,1023,0,255);                         /**/  
        Serial.print(x);                                                     /**/
        Serial.print("<-->");                                                /**/
        Serial.println(y);                                                   /**/   
        while(x < 20 || x > 220 || y < 20 || y > 220){                       /**/
          //Atualiza valores                                                 /**/
          done = radio.read( movimentoDesignado, sizeof(movimentoDesignado));/**/ 
                                                                             /**/
          //Mapeia os valores recebidos para usar com o Arduino              /**/
          x = map(movimentoDesignado[0],0,1023,0,255);                       /**/
          y = map(movimentoDesignado[1],0,1023,0,255);                       /**/
                                                                             /**/
          //Verifica se não detectado nenhum obstáculo                       /**/
          desviarObstaculo();                                                /**/
                                                                             /**/     
          //Envia os valores para os motores                                 /**/ 
          ativarEixoX(x);                                                    /**/
          ativarEixoY(y);                                                    /**/
          valueFlag = movimentoDesignado[2];                                 /**/ 
        }                                                                    /**/   
        valueFlag = movimentoDesignado[2];                                   /**/
        controlarMotores('p');                                               /**/   
      }                                                                      /**/
                                                                             /**/
      //Define se o robô deve entrar no modo autônomo ou não                 /**/ 
      while(valueFlag == 1){                                                 /**/
        done = radio.read( movimentoDesignado, sizeof(movimentoDesignado));  /**/
        controlarMotores('s');                                               /**/
        desviarObstaculo();                                                  /**/
        valueFlag = movimentoDesignado[2];                                   /**/
        Serial.println(valueFlag);                                           /**/
      }                                                                      /**/      
                                                                             /**/   
      controlarMotores('p');                                                 /**/
    }                                                                        /**/
  }                                                                          /**/
  desviarObstaculo();                                                        /**/
}                                                                            /**/
//******************************************************************************/

//Método para desviar obstáculos////////////////////////////////////
void desviarObstaculo(){                                          //
                                                                  //
  //Se o obstáculos estiver mais perto do que 20cm                //
  if(ModoPWM() < 20){                                             //
    //Para o movimento do robô                                    //
    controlarMotores('p');                                        //
                                                                  //
    //Análise melhor caminho para desviar                         //
    int opcao = melhorCaminho();                                  //
    if(opcao > 0){                                                // 
      controlarMotores('w');                                      //
      delay(1000);                                                //
      controlarMotores('p');                                      //
      controlarMotores('a');                                      //
      delay(500);                                                 //
    }                                                             //
    if(opcao < 0){                                                //
      controlarMotores('w');                                      //
      delay(1000);                                                //
      controlarMotores('p');                                      //
      controlarMotores('d');                                      //
      delay(500);                                                 //
    }                                                             //
    if(opcao == 0){                                               //
      controlarMotores('w');                                      //
      controlarMotores('p');                                      //
      delay(2000);                                                //
    }                                                             //
  }                                                               //
}                                                                 //
////////////////////////////////////////////////////////////////////

//Faz a leitura do melhor caminho para desviar o obstáculo//
int melhorCaminho(){                                      //
                                                          //
  int escolha = 0;                                        //
  int ladoEsquerdo = 0;                                   //
  int ladoDireito = 0;                                    //
                                                          //
  //Leitura do lado direito                               //
  servoSensor.write(40);                                  //
  delay(1000);                                            //
  ladoEsquerdo = ModoPWM();                               //
                                                          //
  //Leitura do lado esquerdo                              //
  servoSensor.write(140);                                 //
  delay(1000);                                            //
  ladoDireito = ModoPWM();                                //
                                                          //
                                                          //
  //Define caminho com menos obstáculos                   //
  escolha = ladoEsquerdo - ladoDireito;                   //
                                                          //
  //Deixa o sensor alinhado novamente                     //
  servoSensor.write(90);                                  //
                                                          //
  //Retorna o caminho a seguir                            //
  return escolha;                                         //
}                                                         //
////////////////////////////////////////////////////////////

//Define o movimento do robô conforme leitura dos controles
void ativarEixoX(int valorX){                            //
  Serial.print(valorX);                                  //
  Serial.print(" <---> ");                               //
  if(valorX > 220){                                      //
    controlarMotores('s');                               //
  }                                                      //
  if(valorX < 20){                                       //
    controlarMotores('w');                               //
  }                                                      //
}                                                        //
                                                         //
void ativarEixoY(int valorY){                            //
  Serial.print(valorY);                                  //
  Serial.print(" <> ");                                  //
  if(valorY > 220){                                      //
    controlarMotores('a');                               //  
  }                                                      //
  if(valorY < 20){                                       //
    controlarMotores('d');                               //
  }                                                      //
}                                                        //
                                                         //
void P6(int valor){                                      //
  Serial.println(valor);                                 //
  if(valor > 250){                                       //
    //paraMovimento();                                   //
  }                                                      //
}                                                        //
///////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
void controlarMotores(char entrada){                   //
  char direcao = entrada;                              //
  if(direcao == 'w'){                                  //
    movimentar(85);                                    //
  }                                                    //
  else if(direcao == 's'){                             //
    movimentar(170);                                   //
  }                                                    //
  else if(direcao == 'd'){                             //
    movimentar(153);                                   //
  }                                                    //    
  else if(direcao == 'a'){                             //
    movimentar(102);                                   //
  }                                                    //
  else{                                                //
    movimentar(000);                                   //
  }                                                    //
}                                                      //
                                                       //
void movimentar(int value){                            //
  //  counter=atoi(data);                              //
  digitalWrite(latchPin, LOW);                         //
  shiftOut(dataPin, clockPin, MSBFIRST, value);        //
  digitalWrite(latchPin, HIGH);                        //
}                                                      //
/////////////////////////////////////////////////////////

//Realiza leitura do sensor ultrassônico//
int ModoPWM(){                          //
                                        //    
  digitalWrite(URTRIG, LOW);            //
  digitalWrite(URTRIG, HIGH);           //
                                        //
  //Faz leitura da entrada              //
  distanciaMedida=pulseIn(URPWM,LOW);   // 
                                        //                                     
  //Valida leitura dos dados            //
  if(distanciaMedida==50000){           //   
    Serial.print("Invalid");            //
  }                                     //
  else{                                 //
    distancia=distanciaMedida/50;       //  
  }                                     // 
                                        //
  //Imprime valor na tela               //
  if(distancia < 250){                  //
    Serial.print("Distance=");          //
    Serial.print(distancia);            //
    Serial.println("cm");               //
  }                                     //
                                        //
  //Retorna valor lido                  //
  return distancia;                     //
}                                       //
                                        //
//Iniciar sensor ultrassônico           //
void ModoPWMSetup(){                    //
  //Definição dos pinos                 //
  pinMode(URTRIG,OUTPUT);               //         
  digitalWrite(URTRIG,HIGH);            //         
  pinMode(URPWM, INPUT);                //         
                                        //
  for(int i=0;i<4;i++){                 //   
    Serial.write(EnPwmCmd[i]);          //
  }                                     //
}                                       //
//////////////////////////////////////////


#include <Servo.h>

/*Variáveis que trabalham em conjunto com a ponte H, para controle do motor*/
int MotorUmPolaridadePositiva = 12;
int MotorUmPolaridadeNegativa = 10;
int MotorDoisPolaridadePositiva = 11;
int MotorDoisPolaridadeNegativa = 13;

/*Variáveis para controle do sensor de distância*/                                  
int URPWM=3;                                   
int URTRIG=5;   
unsigned int distancia =0;
unsigned int distanciaMedida =0;
uint8_t EnPwmCmd[4]={0x44,0x22,0xbb,0x01};  

/*Variável que define o tempo de rotação do motor para cada ciclo predefinido nas funções*/
int tempo = 1000;

/*Variável para controle do servo motor*/
Servo controladorSensor;

/*Método para iniciar os componentes uma vez*/
void setup(){
  
  /*Define o pino de controle do Servo Motor como pino 6*/
  controladorSensor.attach(6);
  
  /*Define os pinos que controlarão o motor como pinos de saída*/
  pinMode(MotorUmPolaridadePositiva,OUTPUT);
  pinMode(MotorUmPolaridadeNegativa,OUTPUT);
  pinMode(MotorDoisPolaridadePositiva,OUTPUT);
  pinMode(MotorDoisPolaridadeNegativa,OUTPUT);
  
  /*Freio de motor para desligar todos*/
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  
  /*Iniciar a porta serial para exibir informações no computador*/
  Serial.begin(9600);
}

/*Loop para executar funções repetidamente*/
void loop(){
  /*Faz a calibragem do sensor ultrassonico*/
  ModoPWMSetup();
  
  /*Se a leitura do sensor for menor do que 20 centímetros entra 
  na condição*/
  if(ModoPWM()  < 20){
    /*Para o robô*/
    paraMovimento();
    /*Realiza uma validação para escolher o melhor caminho
    a seguir*/
    int opcao = melhorCaminho();
    /*Se o método retornar um valor negativo então o robô 
    desvia pelo lado direito*/
    if(opcao > 0){
      AtivaRe();
      rotacionarDireita();
    }
    /*Se o método retornar um valor positivo então o 
    robô desvia pelo lado esquerdo*/
    if(opcao < 0){
      AtivaRe();
      rotacionarEsquerda();
    }
    if(opcao == 0){
      AtivaRe();
      AtivaRe();
    }
  /*Se a primeira condição não for verdadeira o robô 
  segue andando para frente*/
  }else{
    AtivaFrente();
  }
  
}
/***********************************************************/
/*  Realiza a leitura da distância dos objetos detectados  */
/*  e retorna o valor lido para ser armazenado em uma      */
/*  variável.                                              */
/***********************************************************/
int ModoPWM(){                            
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);            
     
    distanciaMedida=pulseIn(URPWM,LOW);    
     
    if(distanciaMedida==50000){            
      Serial.print("Invalid");    
   }
    else{
      distancia=distanciaMedida/50;        
   }
  Serial.print("Distance=");
  Serial.print(distancia);
  
  Serial.println("cm");

  return distancia;
}
/***********************************************************/



/************************************************************/
/*  Inicia leitura e faz calibragem do sensor para leitura  */
/************************************************************/
void ModoPWMSetup(){ 
  pinMode(URTRIG,OUTPUT);                        
  digitalWrite(URTRIG,HIGH);                     
  
  pinMode(URPWM, INPUT);                         
  
  for(int i=0;i<4;i++){
      Serial.write(EnPwmCmd[i]);
   }
}
/************************************************************/



/************************************************************/
/*  Método para definir melhor caminho que o robô seguirá   */
/************************************************************/
int melhorCaminho(){
  
  int escolha = 0;
  int ladoEsquerdo = 0;
  int ladoDireito = 0;

  /*Leitura do lado direito*/
  controladorSensor.write(30);
  delay(1000);
  ladoEsquerdo = ModoPWM();

  /*Leitura do lado esquerdo*/
  controladorSensor.write(150);
  delay(1000);
  ladoEsquerdo = ModoPWM();
  
  escolha = ladoDireito - ladoEsquerdo;
  
  controladorSensor.write(90); 
  
  return escolha; 
}
/************************************************************/



/************************************************************/
/*  Método para fazer o robô andar para frente              */
/************************************************************/
void AtivaFrente(){
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  digitalWrite(MotorUmPolaridadeNegativa, HIGH);
  digitalWrite(MotorDoisPolaridadeNegativa, HIGH);
  delay(tempo);
}
/************************************************************/



/************************************************************/
/*  Método para fazer o robô andar praa trás                */
/************************************************************/
void AtivaRe(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, HIGH);
  digitalWrite(MotorDoisPolaridadePositiva, HIGH);
  delay(tempo);
}
/************************************************************/



/************************************************************/
/*  Método para fazer o robô andar para direita             */
/************************************************************/
void rotacionarDireita(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, HIGH);
  digitalWrite(MotorUmPolaridadePositiva, HIGH);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  delay(tempo);
}
/************************************************************/



/************************************************************/
/*  Método para fazer o robô andar para esquerda            */
/************************************************************/
void rotacionarEsquerda(){
  digitalWrite(MotorUmPolaridadeNegativa, HIGH);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, HIGH);
  delay(tempo);
}
/************************************************************/



/************************************************************/
/*  Método para fazer o robô parar de andar                 */
/************************************************************/
void paraMovimento(){
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
}
/************************************************************/

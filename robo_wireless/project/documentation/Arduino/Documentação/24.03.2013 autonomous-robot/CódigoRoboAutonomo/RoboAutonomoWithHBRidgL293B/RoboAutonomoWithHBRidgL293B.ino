#include <Servo.h>

int MotorUmPolaridadePositiva = 10;
int MotorUmPolaridadeNegativa = 12;
int MotorDoisPolaridadePositiva = 11;
int MotorDoisPolaridadeNegativa = 13;

int pos=0;                                     
int URPWM=3;                                   
int URTRIG=5;   
unsigned int distancia =0;
unsigned int distanciaMedida =0;
uint8_t EnPwmCmd[4]={0x44,0x22,0xbb,0x01};  
int tempo = 1000;
Servo controladorSensor;


void setup(){
  
  controladorSensor.attach(9);
  
  pinMode(MotorUmPolaridadePositiva,OUTPUT);
  pinMode(MotorUmPolaridadeNegativa,OUTPUT);
  pinMode(MotorDoisPolaridadePositiva,OUTPUT);
  pinMode(MotorDoisPolaridadeNegativa,OUTPUT);
  
  digitalWrite(MotorUmPolaridadePositiva, LOW);
  digitalWrite(MotorUmPolaridadeNegativa, LOW);
  digitalWrite(MotorDoisPolaridadePositiva, LOW);
  digitalWrite(MotorDoisPolaridadeNegativa, LOW);
  
  Serial.begin(9600);
}

void loop(){
  ModoPWMSetup();
  
  if(ModoPWM()  < 20){
    paraMovimento();
    int opcao = melhorCaminho();
    if(opcao > 0){
      AtivaRe();
      rotacionarDireita();
    }
    if(opcao < 0){
      AtivaRe();
      rotacionarEsquerda();
    }
  }else{
    AtivaFrente();
  }
  
}

//Realiza a leitura da distância dos objetos detectados
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

//Inicia leitura e faz calibragem do sensor para leitura

void ModoPWMSetup(){ 
  pinMode(URTRIG,OUTPUT);                        
  digitalWrite(URTRIG,HIGH);                     
  
  pinMode(URPWM, INPUT);                         
  
  for(int i=0;i<4;i++){
      Serial.write(EnPwmCmd[i]);
   }
}

int melhorCaminho(){
  
  int escolha = 0;
  int aux = 0;
  int aux2 = 0;
  
 for(int i = 40; i <= 120; i = i + 10){
   
   controladorSensor.write(i); 
   delay(1000);
   
    if(i == 40){
      aux = ModoPWM();
    }else{
      aux2 = ModoPWM();
    }
  } 
  
  Serial.print(aux);
    Serial.print("   ");
      Serial.println(aux2);
  escolha = aux - aux2;
  
  controladorSensor.write(90); 
  
  if(escolha == 0){
    return -1;
  }else{
    return escolha; 
  }
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

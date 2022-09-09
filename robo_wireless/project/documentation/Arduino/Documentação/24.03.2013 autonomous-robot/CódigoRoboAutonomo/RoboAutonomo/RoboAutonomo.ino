int motorEsquerdo = 6;
int PonteEntrada1 = 10;
int PonteSaida1 = 12;
int PonteEntrada2 = 11;
int PonteSaida2 = 13;
int URPWM = 3;
int URTRIG = 5;
unsigned long distanciaMedida;
unsigned int distancia=0; 
uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};


void setup(){
  pinMode(PonteEntrada1,OUTPUT);
  pinMode(PonteSaida1,OUTPUT);
  pinMode(PonteEntrada2,OUTPUT);
  pinMode(PonteSaida2,OUTPUT);
  pinMode(motorEsquerdo, OUTPUT);
  
  digitalWrite(PonteEntrada1, LOW);
  digitalWrite(PonteSaida1, LOW);
  digitalWrite(PonteEntrada2, LOW);
  digitalWrite(PonteSaida2, LOW);
  
  Serial.begin(9600);
  ModoPWMSetup();
}

void loop(){
  
  if(ModoPWM()  < 10){
    AtivaRe();
    desligarMotorEsquerdo();
    delay(5000);
    torqueInicial();
  }else{
    AtivaFrente();
    ligarMotorEsquerdo();
  }
  
}

void AtivaFrente(){
  digitalWrite(PonteEntrada1, LOW);
  digitalWrite(PonteSaida1, LOW);
  digitalWrite(PonteEntrada2, HIGH);
  digitalWrite(PonteSaida2, HIGH);
}

void AtivaRe(){
  digitalWrite(PonteEntrada2, LOW);
  digitalWrite(PonteSaida2, LOW);
  digitalWrite(PonteEntrada1, HIGH);
  digitalWrite(PonteSaida1, HIGH);
}

void ModoPWMSetup(){ 
  pinMode(URTRIG,OUTPUT);           
  digitalWrite(URTRIG,HIGH);        
  pinMode(URPWM, INPUT);            
  
  for(int i=0;i<4;i++){             
      Serial.write(EnPwmCmd[i]);
   } 
}

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

void ligarMotorEsquerdo(){
  analogWrite(motorEsquerdo,90); 
}
void desligarMotorEsquerdo(){
  digitalWrite(motorEsquerdo,LOW); 
}
void torqueInicial(){
  digitalWrite(motorEsquerdo,HIGH);
  delay(50); 
}

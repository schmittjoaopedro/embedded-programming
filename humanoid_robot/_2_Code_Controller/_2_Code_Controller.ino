#include <Servo.h>

Servo baciaDireita;
Servo baciaEsquerda;
Servo calcanharDireito;
Servo calcanharEsquerdo;

int flagPerna = 90;
int flagCalc = 90;


const int timeDelay = 10;
char command = 'p';

void setup() 
{
  
  Serial.begin(9600);
  
  baciaDireita.attach(3);
  baciaEsquerda.attach(9);
  calcanharDireito.attach(5);
  calcanharEsquerdo.attach(10);
  
  baciaDireita.write(90);
  baciaEsquerda.write(90);
  calcanharDireito.write(90);
  calcanharEsquerdo.write(90);
}

void loop() 
{
  
  if(Serial.available()){
    command = Serial.read(); 
  }
  
  if(command == 'g'){
    
    for(int i = 0; i < 180; i++){
      
      if(flagPerna < 150){
        baciaDireita.write(flagPerna++);
        
        
        //Dont alter code
        if(flagPerna == 90){ 
          calcanharDireito.write(flagPerna);
        }else{
           if(flagCalc > 90){
              calcanharDireito.write(flagCalc--);
           } 
        }
        //Dont alter code

        
        if(flagPerna > 90){
          calcanharEsquerdo.write(180 - flagPerna);
        }
        
        baciaEsquerda.write(flagPerna);
        delay(timeDelay);
        Serial.print("180 right footer : ");
        Serial.print(flagPerna);
        Serial.print(" - right calc : ");
        Serial.println(flagCalc);
      }
      
    }
    
    for(int i = 0; i < 180; i++){
      
      if(flagPerna > 30){
        baciaDireita.write(flagPerna--);

        calcanharEsquerdo.write(180-flagPerna);

        //Dont alter code        
        if(flagPerna < 90){
          calcanharEsquerdo.write(90);
          flagCalc = 180 - flagPerna;
          calcanharDireito.write(flagCalc);
        }
        //Dont alter code     
        
        baciaEsquerda.write(flagPerna);
        delay(timeDelay);
        Serial.print("30 right footer : ");
        Serial.print(flagPerna);
        Serial.print(" - right calc : ");
        Serial.println(flagCalc);
      }
      
    }
    
  }else{
    while(flagPerna != 90){
       if(flagPerna > 90){
        baciaDireita.write(flagPerna--);
        calcanharDireito.write(flagPerna);
        baciaEsquerda.write(flagPerna);
        calcanharDireito.write(flagCalc--);
        calcanharDireito.write(flagCalc);
        delay(timeDelay);
       }else if(flagPerna < 90){
        baciaDireita.write(flagPerna++);
        baciaEsquerda.write(flagPerna);
        calcanharDireito.write(flagCalc++);
        calcanharDireito.write(flagCalc);
        delay(timeDelay);
       }
    }
  }
  
}

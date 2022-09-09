#include <Servo.h>

const int unsigned footerRight = 4;
const int unsigned leginRight = 5;

Servo s_footerRight;
Servo s_leginRight;

int flagFR = 90;
int flagLR = 90;

void setup(){
  Serial.begin(9600);
  s_footerRight.attach(footerRight);
  s_leginRight.attach(leginRight);
  s_footerRight.write(90);
  s_leginRight.write(90);
}

void loop() {
  
  /*for(int i = 80; i < 110; i++){
   
      s_footerRight.write(i);
      s_footerLeft.write(180-i);
      delay(100);
    
  }*/
  if(Serial.available() > 0){
      int value = (int) Serial.parseInt();
      Serial.println(value);
      //s_footerRight.write(value);  // Quanto maior ele vem pra trás
      //s_leginRight.write(value); // Quanto menor ele vai pra trás
  }
  
  for(int i = 0; i < 180; i++){
    

    if(flagFR > 30){ 
      s_footerRight.write(--flagFR);
      s_leginRight.write(--flagFR);
      delay(150);
    }
  }
  
  flagFR = 30;
  
  for(int i = 0; i < 180; i++){
  
    if(flagFR < 90){ 
      s_footerRight.write(++flagFR);
      s_leginRight.write(++flagFR);
      delay(150);
    }else{
      flagFR = 90;
    }
  }
  
}

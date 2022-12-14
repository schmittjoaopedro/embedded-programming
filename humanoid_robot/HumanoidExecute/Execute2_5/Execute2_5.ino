#include <Servo.h>

Servo s38;
Servo s39;
Servo s40;
Servo s32;
Servo s31;
Servo s33;
Servo s34;
Servo s35;
Servo s36;
Servo s37;

int delayTime = 40;
int executable = 1;
int fixCount = 50;
boolean activeLog = false;

boolean initMove = true;

void setup() {
  
  Serial.begin(9600);
  
  s38.attach(38);
  s39.attach(39);
  s40.attach(40);
  s32.attach(32);
  s31.attach(31);
  s33.attach(33);
  s34.attach(34);
  s35.attach(35);
  s36.attach(36);
  s37.attach(37);
  
  init_servo();
  delay(2000);
}



void loop() {
  
  if(Serial.available()){
    executable = Serial.read();
  }
  
  while(executable > 0) {
             
    if(initMove == true) {
      execute(   100, 140, 157, 70, 100, 100, 110, 15, 60, 100,
                 120, 140, 157, 70, 100, 100, 110, 15, 60, 120 );
                 
                 
      execute(   120, 140, 157, 70, 100, 100, 110, 15, 60, 120,
               110, 150, 157, 70, 103, 95, 110, 80, 90, 125 );
               
               
      execute(   110, 150, 157, 70, 103, 95, 110, 80, 90, 125,
               110, 100, 157, 30, 110, 95, 60, 80, 90, 130 );
               
                 initMove = false;
    }



              
    execute(   110, 100, 157, 30, 110, 95, 60, 80, 90, 130,
               80, 100, 157, 50, 110, 110, 60, 80, 70, 90 );
               
    execute(   80, 100, 157, 50, 110, 110, 60, 80, 70, 90,
               80, 100, 120, 70, 110, 100, 160, 10, 70 , 100 );            
          
    execute(   80, 100, 120, 70, 110, 100, 160, 10, 70 , 100,
               80, 150, 150, 70, 110, 95, 160, 10, 70 , 100 );
               
    execute(   80, 150, 150, 70, 110, 95, 160, 10, 70 , 100,
               80, 170, 157, 90, 110, 95, 140, 10, 50 , 100 );
               
    execute(   80, 170, 157, 90, 110, 95, 140, 10, 50 , 100,
               100, 170, 157, 110, 110, 100, 120, 10, 50 , 100 );
               
    execute(   100, 170, 157, 110, 110, 100, 120, 10, 50 , 100,
               120, 170, 157, 110, 110, 105, 120, 10, 50 , 120 );
               
    execute(   120, 170, 157, 110, 110, 105, 120, 10, 50 , 120,
               120, 140, 157, 90, 110, 95, 120, 40, 70 , 125 );
                            
    execute(   120, 140, 157, 90, 110, 95, 120, 40, 70 , 125,
               120, 140, 120, 90, 103, 90, 110, 40, 60, 120 );
                           
    execute(   120, 140, 120, 90, 103, 90, 110, 40, 60, 120,
               110, 100, 157, 30, 110, 95, 60, 80, 90, 130 );
               
    executable = 1;
  }
  
  
  init_servo();
  
  if(executable == 0) {
    
    delay(5000);
    init_servo();
    
  }
  
}


void init_servo() {

  s38.write(100);
  s39.write(95);
  s40.write(100);
  s32.write(95);
  s31.write(103);
  s33.write(95);
  s34.write(80);
  s35.write(85);
  s36.write(90);
  s37.write(100);
}

void execute(
  float p38, float p39, float p40, float p32, float p31, float p33, float p34, float p35, float p36, float p37,
  float g38, float g39, float g40, float g32, float g31, float g33, float g34, float g35, float g36, float g37
) {
  
  float r38 = (p38 - g38) / fixCount,
      r39 = (p39 - g39) / fixCount,
      r40 = (p40 - g40) / fixCount,
      r32 = (p32 - g32) / fixCount,
      r31 = (p31 - g31) / fixCount,
      r33 = (p33 - g33) / fixCount,
      r34 = (p34 - g34) / fixCount,
      r35 = (p35 - g35) / fixCount,
      r36 = (p36 - g36) / fixCount,
      r37 = (p37 - g37) / fixCount;
  
  for(int i = 0; i < fixCount; i++) {
    
    p38 -= r38;
    p39 -= r39;
    p40 -= r40;
    p32 -= r32;
    p31 -= r31;
    p33 -= r33;
    p34 -= r34;
    p35 -= r35;
    p36 -= r36;
    p37 -= r37;
    
    s38.write(p38);
    s39.write(p39);
    s40.write(p40);
    s32.write(p32);
    s31.write(p31);
    s33.write(p33);
    s34.write(p34);
    s35.write(p35);
    s36.write(p36);
    s37.write(p37);
    
    if(activeLog) {
      Serial.print("P38: ");
      Serial.print(p38);
      Serial.print(" P39: ");
      Serial.print(p39);
      Serial.print("  P40: ");
      Serial.print(p40);
      Serial.print("  P32: ");
      Serial.print(p32);
      Serial.print("  P31: ");
      Serial.print(p31);
      Serial.print("  P33: ");
      Serial.print(p33);
      Serial.print("  P34: ");
      Serial.print(p34);
      Serial.print("  P35: ");
      Serial.print(p35);
      Serial.print("  P36: ");
      Serial.print(p36);
      Serial.print("  P37: ");
      Serial.println(p37);
    }
    delay(delayTime);
  }
  Serial.println("\n");
}



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

int delayTime = 50;
boolean executable = true;

void setup() {
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
  
  execute(95,90,100,95,106,100,80,85,90,100);
}


void loop() {
  
  while(executable) {
  
    execute(95, 93 , 105, 92, 106, 100, 80, 85 ,88, 100);
    delay(delayTime);
    execute(95, 96 , 110, 89, 106, 100, 82, 80 ,86, 100);
    delay(delayTime);
    execute(95, 99 , 115, 86, 106, 100, 85, 75 ,84, 100);
    delay(delayTime);
    execute(95, 102, 120, 83, 106, 100, 89, 70 ,82, 100);
    delay(delayTime);
    execute(95, 105, 125, 80, 106, 100, 92, 65 ,80, 100);
    delay(delayTime);
    execute(95, 108, 130, 77, 106, 100, 96, 60 ,78, 100);
    delay(delayTime);
    execute(95, 111, 135, 76, 106, 100, 99, 55 ,76, 100);
    delay(delayTime);
    execute(95, 114, 140, 72, 106, 100, 102, 50 ,74, 100);
    delay(delayTime);
    execute(95, 117, 145, 69, 106, 100, 107, 45 ,72, 100);
    delay(delayTime);
    execute(95, 120, 150, 65, 106, 100, 110, 40 ,70, 100);
    delay(delayTime);
    
    
    
    
    execute(95, 120, 150, 65, 106, 100, 110, 40 ,70, 100);
    delay(delayTime);
    execute(95, 117, 145, 69, 106, 100, 107, 45 ,72, 100);
    delay(delayTime);
    execute(95, 114, 140, 72, 106, 100, 102, 50 ,74, 100);
    delay(delayTime);
    execute(95, 111, 135, 76, 106, 100, 99, 55 ,76, 100);
    delay(delayTime);
    execute(95, 108, 130, 77, 106, 100, 96, 60 ,78, 100);
    delay(delayTime);
    execute(95, 105, 125, 80, 106, 100, 92, 65 ,80, 100);
    delay(delayTime);
    execute(95, 102, 120, 83, 106, 100, 89, 70 ,82, 100);
    delay(delayTime);
    execute(95, 99 , 115, 86, 106, 100, 85, 75 ,84, 100);
    delay(delayTime);
    execute(95, 96 , 110, 89, 106, 100, 82, 80 ,86, 100);
    delay(delayTime);
    execute(95, 93 , 105, 92, 106, 100, 80, 85 ,88, 100);
    delay(delayTime);
  
    executable = true;
  }

}



void execute(int p38, int p39, int p40, int p32, int p31, int p33, int p34, int p35, int p36, int p37) {
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
}

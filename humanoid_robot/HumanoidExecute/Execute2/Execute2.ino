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

int delayTime = 10;
boolean executable = true;
int fixCount = 10;

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
  
  s38.write(95);
  s39.write(90);
  s40.write(100);
  s32.write(95);
  s31.write(106);
  s33.write(100);
  s34.write(80);
  s35.write(85);
  s36.write(90);
  s37.write(100);
  
  delay(2000);
}



void loop() {
  
  while(executable) {
  
    execute(   95, 90, 100, 95, 106, 100, 80, 85, 90, 100,
               95, 120, 150, 65, 106, 100, 110, 40, 70, 100 );
               
               
    execute(   95, 120, 150, 65, 106, 100, 110, 40, 70, 100,
               75, 120, 150, 65, 106, 100, 110, 40, 70, 85 );
               
    execute(   75, 120, 150, 65, 106, 100, 110, 40, 70, 85,
               70, 120, 150, 65, 106, 85, 110, 40, 70, 90 );
               
    execute(   70, 120, 150, 65, 106, 85, 110, 40, 70, 90,
               70, 120, 150, 65, 106, 75, 130, 45, 85, 75 );
               
    execute(   70, 120, 150, 65, 106, 75, 130, 45, 85, 75,
               80, 120, 150, 65, 106, 85, 130, 45, 85, 80 );
               
    execute(   80, 120, 150, 65, 106, 85, 130, 45, 85, 80,
               95, 120, 150, 65, 106, 100, 130, 45, 85, 100 );
               
    execute(   95, 120, 150, 65, 106, 100, 130, 45, 85, 100,
               110, 120, 150, 65, 106, 100, 130, 45, 85, 115 );
               
    execute(   110, 120, 150, 65, 106, 100, 130, 45, 85, 115,
               110, 120, 150, 65, 115, 100, 130, 45, 85, 125 );
               
    execute(   110, 120, 150, 65, 115, 100, 130, 45, 85, 125,
               120, 120, 150, 65, 125, 100, 130, 45, 85, 125 );
               
    execute(   120, 120, 150, 65, 125, 100, 130, 45, 85, 125,
               120, 120, 120, 65, 125, 100, 120, 45, 75, 125 ); //INCLINA BASTANTE
               
    execute(   120, 120, 120, 65, 125, 100, 120, 45, 75, 125,
               120, 120, 140, 65, 125, 100, 100, 45, 75, 125 );
               
    execute(   120, 120, 140, 65, 125, 100, 100, 45, 75, 125,
               110, 90, 100, 65, 115, 100, 100, 45, 75, 115 );
               
    execute(   110, 90, 100, 65, 115, 100, 100, 45, 75, 115,
               80, 90, 110, 65, 100, 100, 100, 45, 75, 60 );
               
    execute(   80, 90, 110, 65, 100, 100, 100, 45, 75, 60,
               80, 90, 110, 65, 120, 100, 100, 45, 75, 60 );
               
    execute(   75, 90, 110, 65, 120, 100, 100, 45, 75, 60,
               75, 90, 100, 75, 120, 100, 120, 45, 75, 60 );
               
    execute(   75, 90, 100, 75, 120, 100, 120, 45, 75, 90,
               75, 90, 100, 70, 120, 100, 120, 45, 75, 90 );
               
    execute(   80, 90, 100, 70, 120, 100, 120, 45, 75, 90,
               85, 100, 100, 75, 100, 90, 120, 30, 70, 95 );
               
    execute(   85, 100, 100, 75, 100, 90, 120, 30, 70, 95,
               95, 120, 150, 65, 106, 100, 110, 40, 70, 100 );
               

    //executable = false;
  }
  
  if(!executable) {
    
    delay(5000);
    s38.write(95);
    s39.write(90);
    s40.write(100);
    s32.write(95);
    s31.write(106);
    s33.write(100);
    s34.write(80);
    s35.write(85);
    s36.write(90);
    s37.write(100);
    
  }
  
}

void execute(
  int p38, int p39, int p40, int p32, int p31, int p33, int p34, int p35, int p36, int p37,
  int g38, int g39, int g40, int g32, int g31, int g33, int g34, int g35, int g36, int g37
) {
  
  int r38 = (p38 - g38) / fixCount,
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
    
    Serial.print("P38: ");
    Serial.print(p38);
    Serial.print("  P39: ");
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
    
    delay(delayTime);
  }
  Serial.println("\n");
}


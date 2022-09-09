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

int delayTime = 150;
int executable = 0;
int fixCount = 15;

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
  
    execute(   100, 95, 100, 95, 103, 95, 80, 85, 90, 100,
               100, 140, 160, 55, 103, 95, 125, 30, 60, 100 );
               Serial.println("1");
    execute(   100, 140, 160, 55, 103, 95, 125, 30, 60, 100,
               120, 140, 160, 55, 103, 95, 125, 30, 60, 120 );
               Serial.println("2");     
    execute(   120, 140, 160, 55, 103, 95, 125, 30, 60, 120,
               110, 150, 160, 55, 103, 95, 125, 30, 60, 120 );
               Serial.println("3");               
    execute(   110, 150, 160, 55, 103, 95, 125, 30, 60, 120,
               110, 110, 180, 20, 103, 95, 125, 10, 60, 120 );
               Serial.println("4");               
    execute(   110, 110, 180, 20, 103, 95, 125, 10, 60, 120,
               80, 110, 180, 20, 103, 95, 125, 10, 60, 80 );
               Serial.println("5");     
    execute(   80, 110, 180, 20, 103, 95, 125, 10, 60, 80,
               100, 140, 160, 55, 103, 95, 125, 30, 60, 100 );
               Serial.println("6");               
               //INVERSA
    execute(   100, 140, 160, 55, 103, 95, 125, 30, 60, 100,
               80, 140, 160, 55, 103, 95, 125, 30, 60, 80 );
               Serial.println("7");               
    execute(   80, 140, 160, 55, 103, 95, 125, 30, 60, 80,
               80, 140, 160, 55, 103, 95, 125, 30, 50, 90 );
               Serial.println("8");               
    execute(   80, 140, 160, 55, 103, 95, 125, 30, 50, 90,
               80, 140, 180, 55, 103, 95, 150, 10, 80, 90 );
               Serial.println("9");               
    execute(   80, 140, 180, 55, 103, 95, 150, 10, 80, 90,
               100, 140, 180, 55, 103, 95, 150, 10, 80, 100 );
               Serial.println("10");               
    execute(   100, 140, 180, 55, 103, 95, 150, 10, 80, 100,
               110, 140, 180, 55, 103, 95, 150, 10, 60, 110 );
               Serial.println("11");               
    execute(   110, 140, 180, 55, 103, 95, 150, 10, 60, 110,
               110, 160, 180, 20, 103, 95, 180, 10, 60, 110 );
               Serial.println("12");               
    execute(   110, 160, 180, 20, 103, 95, 180, 10, 60, 110,
               100, 140, 160, 55, 103, 95, 125, 30, 60, 100 );
               Serial.println("13");                    
    
    
    executable = 0;
    
    
    execute(   100, 140, 160, 55, 103, 95, 125, 30, 60, 100,
               100, 95, 100, 95, 103, 95, 80, 85, 90, 100 );
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



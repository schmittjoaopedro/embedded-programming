#include <Servo.h>

#define PI 3.141592654

float thigSize = 7.5;
float shinSize = 8.5;


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


int staticCOG = 90;
//Calibragem
float c38 = +5;
float c39 = 0;
float c40 = +10;
float c32 = +5;
float c31 = +13;
float c33 = +10;
float c34 = -10;
float c35 = -5;
float c36 = 0;
float c37 = 10;


float delayTime = 10;
boolean executable = true;
float fixCount = 20;
float start = 0;

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
  
  if(Serial.available() > 0) {
    start = Serial.read();
    Serial.println(start);
  }
  if(start > 0) {
  
    delay(5000);
    for(int i = 90; i > 40; i--){
      delay(fixCount);
      fact2(i);
    } 
    Serial.println("----------------");
    delay(5000);
    for(int i = 40; i < 90; i++){
      delay(fixCount);
      fact2(i);
    }
    delay(5000);
    start = 0;

  }
  else {
    
    delay(5000);
    s38.write(95);
    s39.write(90);
    s40.write(100);
    s32.write(95);
    s31.write(103);
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


//FATO S38 == S37 E 3% AJUSTE PARA BACIA
void fact1(int angulo) {
  
  int tempV = angulo;
  
  if(angulo < staticCOG) {
    s33.write((angulo + c33) * 1.03);
  } else {
    s31.write((angulo + c31) * 0.97);
  }
  
  s38.write(tempV + c38);
  s37.write(tempV + c37);
}


void fact2(int angle) {
  if(angle >= 50 && angle <= 90) {
    fact2_left(angle);
    fact2_right(angle);
  }
}


void fact2_left(int condAngle) {
  
  int angle = 90 - condAngle;
  
  float t32cat_op = sin(toRadian(angle)) * thigSize;
  float t40_cat_op_size = sqrt(pow(shinSize, 2) - pow(t32cat_op, 2));
  float t40_angle_arc_sen = t40_cat_op_size / shinSize;
  float t40_angle_inverse = arcseno(t40_angle_arc_sen);
  
  int t39 = staticCOG + angle;
  int t40 = 90 + (90 - t40_angle_inverse) + angle; //REVER ESTE MÉTODO
  int t32 = 90 - (90 - t40_angle_inverse);
  
  s32.write(t32 + c32);
  s39.write(t39 + c39);
  s40.write(t40 + c40);
  
  Serial.print("S39 - ");
  Serial.print(t39 + c39);
  Serial.print("  s40 - ");
  Serial.print(t40 + c40);
  Serial.print("  s32 - ");
  Serial.println(t32 + c32);
    
}

void fact2_right(int condAngle) {
  
  int angle = 90 - condAngle;
  
  float t34cat_op = sin(toRadian(angle)) * thigSize;
  float t35_cat_op_size = sqrt(pow(shinSize, 2) - pow(t34cat_op, 2));
  float t35_angle_arc_sen = t35_cat_op_size / shinSize;
  float t35_angle_inverse = arcseno(t35_angle_arc_sen);
  
  int t36 = staticCOG + angle;
  int t35 = 90 + (90 - t35_angle_inverse) + angle; //REVER ESTE MÉTODO
  int t34 = 90 - (90 - t35_angle_inverse);

  //inverse side
  t36 = 180 - t36;
  t35 = 180 - t35;
  t34 = 180 - t34;
  
  s34.write(t34 + c34);
  s36.write(t36 + c36);
  s35.write(t35 + c35);
  
  Serial.print("S36 - ");
  Serial.print(t36 + c36);
  Serial.print("  s35 - ");
  Serial.print(t35 + c35);
  Serial.print("  s34 - ");
  Serial.println(t34 + c34);
  
}



float toRadian(int angle) {
  return (angle * PI / 180);
}

int arcseno(float seno) {
  int angle = 1;
  if(seno > 0.0175) angle = 2;
  if(seno > 0.0349) angle = 3;
  if(seno > 0.0523) angle = 4;
  if(seno > 0.0698) angle = 5;
  if(seno > 0.0872) angle = 6;
  if(seno > 0.1045) angle = 7;
  if(seno > 0.1219) angle = 8;
  if(seno > 0.1392) angle = 9;
  if(seno > 0.1564) angle = 10;
  if(seno > 0.1736) angle = 11;
  if(seno > 0.1908) angle = 12;
  if(seno > 0.2079) angle = 13;
  if(seno > 0.225) angle = 14;
  if(seno > 0.2419) angle = 15;
  if(seno > 0.2588) angle = 16;
  if(seno > 0.2756) angle = 17;
  if(seno > 0.2924) angle = 18;
  if(seno > 0.309) angle = 19;
  if(seno > 0.3256) angle = 20;
  if(seno > 0.342) angle = 21;
  if(seno > 0.3584) angle = 22;
  if(seno > 0.3746) angle = 23;
  if(seno > 0.3907) angle = 24;
  if(seno > 0.4067) angle = 25;
  if(seno > 0.4226) angle = 26;
  if(seno > 0.4384) angle = 27;
  if(seno > 0.454) angle = 28;
  if(seno > 0.4695) angle = 29;
  if(seno > 0.4848) angle = 30;
  if(seno > 0.5) angle = 31;
  if(seno > 0.515) angle = 32;
  if(seno > 0.5299) angle = 33;
  if(seno > 0.5446) angle = 34;
  if(seno > 0.5592) angle = 35;
  if(seno > 0.5736) angle = 36;
  if(seno > 0.5878) angle = 37;
  if(seno > 0.6018) angle = 38;
  if(seno > 0.6157) angle = 39;
  if(seno > 0.6293) angle = 41;
  if(seno > 0.6428) angle = 41;
  if(seno > 0.6561) angle = 42;
  if(seno > 0.6691) angle = 43;
  if(seno > 0.682) angle = 44;
  if(seno > 0.6947) angle = 45;
  if(seno > 0.7071) angle = 46;
  if(seno > 0.7193) angle = 47;
  if(seno > 0.7314) angle = 48;
  if(seno > 0.7431) angle = 49;
  if(seno > 0.7547) angle = 50;
  if(seno > 0.766) angle = 51;
  if(seno > 0.7771) angle = 52;
  if(seno > 0.788) angle = 53;
  if(seno > 0.7986) angle = 54;
  if(seno > 0.809) angle = 55;
  if(seno > 0.8192) angle = 56;
  if(seno > 0.829) angle = 57;
  if(seno > 0.8387) angle = 58;
  if(seno > 0.848) angle = 59;
  if(seno > 0.8572) angle = 60;
  if(seno > 0.866) angle = 61;
  if(seno > 0.8746) angle = 62;
  if(seno > 0.8829) angle = 63;
  if(seno > 0.891) angle = 64;
  if(seno > 0.8988) angle = 65;
  if(seno > 0.9063) angle = 66;
  if(seno > 0.9135) angle = 67;
  if(seno > 0.9205) angle = 68;
  if(seno > 0.9272) angle = 69;
  if(seno > 0.9336) angle = 70;
  if(seno > 0.9397) angle = 71;
  if(seno > 0.9455) angle = 72;
  if(seno > 0.9511) angle = 73;
  if(seno > 0.9563) angle = 74;
  if(seno > 0.9613) angle = 75;
  if(seno > 0.9659) angle = 76;
  if(seno > 0.9703) angle = 77;
  if(seno > 0.9744) angle = 78;
  if(seno > 0.9781) angle = 79;
  if(seno > 0.9816) angle = 80;
  if(seno > 0.9848) angle = 81;
  if(seno > 0.9903) angle = 82;
  if(seno > 0.9925) angle = 84;
  if(seno > 0.9945) angle = 85;
  if(seno > 0.9962) angle = 86;
  if(seno > 0.9976) angle = 87;
  if(seno > 0.9986) angle = 88;
  if(seno > 0.9994) angle = 89;
  if(seno > 0.9998) angle = 90;
  return angle;
}


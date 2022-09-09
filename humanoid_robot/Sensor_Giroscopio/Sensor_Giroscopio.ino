#include <Wire.h>
#include <L3G.h>

L3G gyro;

int rate = 20000;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  pinMode(50, OUTPUT);
  gyro.enableDefault();
}

void loop() {
  gyro.read();

  int x = (int)gyro.g.x;
  int z = (int)gyro.g.z;
  int y = (int)gyro.g.y; 

  Serial.print("G ");
  Serial.print("\t\tX: ");
  Serial.print(x);
  Serial.print("\t\tY: ");
  Serial.print(y);
  Serial.print("\t\tZ: ");
  Serial.println(z);

  if(
    x > rate || x < -rate ||
    z > rate || z < -rate || 
    y > rate || y < -rate
  ) {
    digitalWrite(50,HIGH);
    delay(1000);  
  } else {
    digitalWrite(50,LOW);    
  }

}

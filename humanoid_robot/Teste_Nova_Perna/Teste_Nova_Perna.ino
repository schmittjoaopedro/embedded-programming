#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
int aux = 90;

void setup(){
  
  Serial.begin(9600);
  
  s1.attach(3);
  s2.attach(5);
  s3.attach(6);
  s4.attach(9);
  
  s1.write(90);
  s2.write(90);
  s3.write(90);
  s4.write(90);
}

void loop(){
  
  String texto = readText();
  
  if(texto == "+"){
    aux = aux + 5;
    s4.write(aux);
  }
  if(texto == "-"){
    aux = aux - 5;
    s4.write(aux);
  }
  
}

String readText(){
  String str = "";
	char character;

	while(Serial.available()){
		character = Serial.read();
    	str.concat(character);
	}

	return str;
}

#include <Servo.h>
#include "Humanoid.h"
#include "Acelerometer.h"

Humanoid humanoid;

void setup(){
	Serial.begin(9600);
}

void loop(){
	humanoid.readParameters();
}
#include <Servo.h>
#include "Arduino.h"
#include "Acelerometer.h"

#ifndef Humanoid_h
#define Humanoid_h

class Humanoid 
{

//Privated members....
private:
	int intensity;
	int angulation;
	Acelerometer acelerometer;

//Public members...
public:
	void balance();
	void calculatedOperation();
	void defineEquation();
	void walk();
	void difineMoviment();

};

#endif
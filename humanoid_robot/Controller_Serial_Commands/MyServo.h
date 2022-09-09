#include "Arduino.h"
#include "Servo.h"
#include "Utilities.h"
#include "CommunicationServo.h"

#ifndef MyServo_h
#define MyServo_h

class MyServo {

//Public members....
public:
	//This values can be changed
	int maxAngulation;
	int minAngulation;

	MyServo();
	void setup(int pinServo);
	void turnFullRight();
	void turnFullLeft();
	void turnMiddle();
	void turnAngulation(int angulation);
	void move(String data);
	int getIdentification();
	int getAngulation();
//Private members...
private:
	Servo servo;
	int pinServo;
	int angulation;
	CommunicationServo communication;
};

#endif
#include "Arduino.h"
#include "Servo.h"
#include "Utilities.h"

#ifndef CommunicationServo_h
#define CommunicationServo_h


class CommunicationServo {

/*
	Pattern comunication with the servo
	S:{pino-servo};A:{angulo-rotação};
*/

//Public members...
public:
	CommunicationServo();
	void setup(Servo servo);

	//Methods identfification
	int readServo(String data);
	int readAngulation(String data);

	const static char patternAngulation = 'A';
//Private members...
private:
	int angulation;
	Servo servo;
	Utilities myUtils;
};


#endif

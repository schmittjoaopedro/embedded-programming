#include <Servo.h>
#include "Arduino.h"

#ifndef Humanoide_h
#define Humanoide_h

class Humanoide {

//Public Members..
public:
	//Contructor...
	Humanoide();
	//Public Methods...
	void init(int legRightPin, int legLeftPin, int shinRightPin, int shinLeftPin);
	void aheadWalk();
	void backWalk();
	void stopWalk();
	void onTimeRespanw();
	void danceCanCan();

	//Public Methods setter and getters atributes...
	void setTimeRespawn(int time);
	int getTimeRespawn();

//Private Members...
private:
	Servo legRight;
	Servo legLeft;
	Servo shinRight;
	Servo shinLeft;
	int timeRespawn;
};

#endif
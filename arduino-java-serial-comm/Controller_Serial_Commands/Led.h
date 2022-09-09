#include "Arduino.h"

#ifndef Led_h
#define Led_h

class Led {

//Public members...
public:
	Led();
	void setup(int ledPin);
	void setup(int led, bool state);
	void powerOff();
	void powerOn();
	void changeState();
	void setState(bool state);
	bool getState();
//Private members...
private:
	int ledPin;
	bool state;
};

#endif
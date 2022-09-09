#include "Arduino.h"
#include "Led.h"

Led::Led(){
	this->state = false;
}

void Led::setup(int ledPin){
	this->ledPin = ledPin;
	pinMode(this->ledPin,OUTPUT);
	digitalWrite(this->ledPin,this->state);
}

void Led::setup(int ledPin,bool state){
	this->ledPin = ledPin;
	this->state = state;
	pinMode(this->ledPin,OUTPUT);
	digitalWrite(this->ledPin,this->state);
}

void Led::powerOn(){
	this->state = true;
	digitalWrite(this->ledPin,this->state);
}

void Led::powerOff(){
	this->state = false;
	digitalWrite(this->ledPin,this->state);
}

void Led::changeState(){
	if(this->state){
		this->powerOff();
	}else{
		this->powerOn();
	}
}

void Led::setState(bool state){
	this->state = state;
	this->changeState();
}

bool Led::getState(){
	return this->state;
}
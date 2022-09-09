#include "Arduino.h"
#include "Servo.h"
#include "Utilities.h"
#include "CommunicationServo.h"
#include "MyServo.h"

MyServo::MyServo(){
	this->maxAngulation = 180;
	this->minAngulation = 0;
}

void MyServo::setup(int pinServo){
	this->pinServo = pinServo;
	this->servo.attach(this->pinServo);
	this->communication.setup(this->servo);
}

void MyServo::turnFullRight(){
	this->angulation = minAngulation;
	this->servo.write(this->angulation);
}

void MyServo::turnFullLeft(){
	this->angulation = maxAngulation;
	this->servo.write(this->angulation);
}

void MyServo::turnMiddle(){
	this->angulation = (maxAngulation + minAngulation)/2;
	this->servo.write(this->angulation);
}

int MyServo::getIdentification(){
	return this->pinServo;
}

int MyServo::getAngulation(){
	return this->angulation;
}

void MyServo::move(String data){
	this->turnAngulation(this->communication.readAngulation(data));
}

void MyServo::turnAngulation(int angulation){
	this->angulation = angulation;
	this->servo.write(this->angulation);
}
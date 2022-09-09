#include "Servo.h"
#include "Arduino.h"
#include "Utilities.h"
#include "CommunicationServo.h"

CommunicationServo::CommunicationServo(){}

void CommunicationServo::setup(Servo servo){
	this->servo = servo;
}

int CommunicationServo::readServo(String data){
	int indexInitIdentification = data.indexOf(':') + 1;
	int indexEndIdentification = data.indexOf(';');
	String value = data.substring(indexInitIdentification,indexEndIdentification);
	return value.toInt();
}

int CommunicationServo::readAngulation(String data){
	int indexInitIdentification = data.lastIndexOf(':') + 1;
	int indexEndIdentification = data.lastIndexOf(';');
	String value = data.substring(indexInitIdentification,indexEndIdentification);
	return value.toInt();
}
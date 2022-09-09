#include "Servo.h"
#include "Arduino.h"
#include "Utilities.h"
#include "Controller.h"

void Controller::init() {
	this->defined = false;
}

void Controller::define(String message){

	char index = ',';

	int commaPosition;
	int counter = 0;
	int arraySize;
	String temp = message;
	while(temp.indexOf(index) != -1) {
		commaPosition = temp.indexOf(index);
		if(commaPosition != -1){
			temp = temp.substring(commaPosition+1, temp.length());
			arraySize++;
		}else{
			arraySize++;
		}
	};
	commaPosition = 0;
	String data[arraySize];
  	do
  	{
    	commaPosition = message.indexOf(index);
     	if(commaPosition != -1)
      	{
        	data[counter] = message.substring(0,commaPosition);
          	message = message.substring(commaPosition+1, message.length());
          	counter++;
      	}
      	else
      	{  // here after the last comma is found
         	if(message.length() > 0)
           	data[counter] = message;
      	}
   }
   while(commaPosition >=0);

   for(int i = 0; i <= arraySize; i++) {

   		char type = data[i].charAt(0);

   		if(type == 'D') {
   			fillDigitalPin(data[i]);
   		}   
   		if(type == 'S') {
   			fillServoPin(data[i]);
   		}
   		if(type == 'P') {
   			fillPWMPin(data[i]);
   		}
   		if(type == 'A') {
   			fillAnalogPin(data[i]);
   		}
   }

   this->defined = true;
}



void Controller::execute(String message) {

	char index = ',';
	int commaPosition;
	int counter = 0;
	int arraySize;
	String temp = message;
	while(temp.indexOf(index) != -1) {
		commaPosition = temp.indexOf(index);
		if(commaPosition != -1){
			temp = temp.substring(commaPosition+1, temp.length());
			arraySize++;
		}else{
			arraySize++;
		}
	};
	commaPosition = 0;
	String data[arraySize];
  	do
  	{
    	commaPosition = message.indexOf(index);
     	if(commaPosition != -1)
      	{
        	data[counter] = message.substring(0,commaPosition);
          	message = message.substring(commaPosition+1, message.length());
          	counter++;
      	}
      	else
      	{  // here after the last comma is found
         	if(message.length() > 0)
           	data[counter] = message;
      	}
   }
   while(commaPosition >=0);

   for(int i = 0; i <= arraySize; i++) {

   		char type = data[i].charAt(0);
   		if(type == 'D') {
   			executeDigitalPin(data[i]);
   		} 
   		if(type == 'S') {
   			executeServoPin(data[i]);
   		}
   		if(type == 'P') {
   			executePWMPin(data[i]);
   		}
   		if(type == 'A') {
   			executeAnalogPin(data[i]);
   		}
   		if(type == 'L') {
   			loggerPositions();
   		}
   		if(type == 'R') {
   			this->util.reset();
   		}
   }

   this->defined = true;
}



/*
 * Methods digital PIN
 */
void Controller::fillDigitalPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	String mode = data.substring(endPin + 1, data.length());
	this->mapped += "DIGITAL ";
	this->mapped += finalPin;
	this->mapped += ": ";
	if(mode == "OUTPUT"){
		pinMode(finalPin, OUTPUT);
		this->mapped += "OUTPUT";
	} else if(mode = "INPUT") {
		pinMode(finalPin, INPUT);
		this->mapped += "INPUT";
	}
	this->mapped += ";\n";

}
void Controller::executeDigitalPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	String value = data.substring(endPin + 1, data.length());

	if(value == "HIGH"){
		digitalWrite(finalPin, HIGH);
	} else if(value == "LOW") {
		digitalWrite(finalPin, LOW);
	} else if(value == "READ") {
		int read = digitalRead(finalPin);
		String response = "D-";
		response += String(finalPin);
		response += ":";
		response += String(read);
		response += ",";
		Serial.println(response);
	}
}



/*
 * Methods Servos
 */
void Controller::fillServoPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	int position = finalPin - 22;
	String angle = data.substring(endPin + 1, data.length());
	int initialAngulation = angle.toInt();
	this->mapped += "SERVO ";
	this->mapped += finalPin;
	this->mapped += ": A(";
	this->mapped += angle;
	this->servos[position].attach(finalPin);
	this->servos[position].write(initialAngulation);
	this->mapped += ");\n";

}
void Controller::executeServoPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	int position = finalPin - 22;
	String value = data.substring(endPin + 1, data.length());
	int angulation = value.toInt();
	this->servos[position].write(angulation);
	String response = "S-";
	response += String(finalPin);
	response += ":";
	response += String(angulation);
	response += ",";
	Serial.println(response);
}



/*
 * Methods PWM Pin
 */
void Controller::fillPWMPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	String mode = data.substring(endPin + 1, data.length());
	this->mapped += "PWM ";
	this->mapped += finalPin;
	this->mapped += ": ";
	if(mode == "WRITE"){
		this->PWM[finalPin] = "WRITE";
		this->mapped += "WRITE";
	} else if(mode = "READ") {
		this->PWM[finalPin] = "READ";
		this->mapped += "READ";
	}
	this->mapped += ";\n";
}
void Controller::executePWMPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	String value = data.substring(endPin + 1, data.length());

	if(this->PWM[finalPin] == "READ") {
		//int read = analogRead(finalPin);
		//String response = "PWM ";
		//response += String(finalPin);
		//response += ":";
		//response += String(read);
		//response += ";";
		//Serial.println(response);
	} else if(this->PWM[finalPin] == "WRITE") {
		analogWrite(finalPin, value.toInt());
	}
}


void Controller::fillAnalogPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	String mode = data.substring(endPin + 1, data.length());
	this->mapped += "ANALOG ";
	this->mapped += finalPin;
	this->mapped += ": ";
	if(mode == "WRITE"){
		this->analog[finalPin] = "WRITE";
		this->mapped += "WRITE";
	} else if(mode = "READ") {
		this->analog[finalPin] = "READ";
		this->mapped += "READ";
	}
	this->mapped += ";\n";
}
void Controller::executeAnalogPin(String data) {

	int initPin = data.indexOf('-') + 1;
	int endPin = data.indexOf(':');
	String pin = data.substring(initPin, endPin);
	int finalPin = pin.toInt();
	String value = data.substring(endPin + 1, data.length());

	if(this->analog[finalPin] == "READ") {
		int read = analogRead(finalPin);
		String response = "A-";
		response += String(finalPin);
		response += ":";
		response += String(read);
		response += ",";
		Serial.println(response);
	} else if(this->analog[finalPin] == "WRITE") {
		//analogWrite(finalPin, value.toInt());
	}
}


void Controller::loggerPositions() {
	Serial.println(this->mapped);
}
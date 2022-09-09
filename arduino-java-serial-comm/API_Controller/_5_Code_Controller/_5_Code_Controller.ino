#include "Arduino.h"
#include "Utilities.h"
#include "Servo.h"
#include "Controller.h"

Utilities util;
Controller controller;

void setup() {
	Serial.begin(9600);
	controller.init();
};

void loop() {

	if(controller.defined == true){

		String readData = util.readString();
		if(readData != "") {
			controller.execute(readData);
		}

	}else{

		String readData = util.readString();
		if(readData != "") {
			controller.define(readData);
		}

	}

	
};


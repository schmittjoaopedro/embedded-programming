#include "Arduino.h"
#include "Utilities.h"

Utilities::Utilities()
{
}

String Utilities::readString()
{
	String str = "";
	char character;

	while(Serial.available()){
		character = Serial.read();
    	str.concat(character);
	}

	return str;
}
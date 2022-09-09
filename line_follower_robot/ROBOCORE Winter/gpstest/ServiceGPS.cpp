#include <Arduino.h>
#include "ServiceGPS.h"


void ServiceGPS::init(HardwareSerial *serial) {
	this->__serial = serial;
  	this->__serial->begin(38400);
}

void ServiceGPS::readGPS(String *dataRead) {
	while(this->__serial->available()) {
	    this->readChar = this->__serial->read();
	    this->data += this->readChar;
	    if(this->readChar == BROKEN_LINE) {
	    	this->toCompare = this->data.substring(0,6);
	    	if(this->toCompare.equals(GPGLL)) {
	    		*dataRead = this->data;
	    	}
    		this->data = "";
	    }
	};
}

void ServiceGPS::getCoordinates(float *latitude, float *longitude) {
	
	this->rawData = "";
	this->readGPS(&rawData);

	if(!this->rawData.equals("")) {

			this->rawData = this->rawData.substring(this->rawData.indexOf(',') + 1, this->rawData.length());
            
            //2627.99470
            this->latitudeString = this->rawData.substring(0, this->rawData.indexOf(','));
            
            //S,04906.85799,W,000122.00,A,A*64
            this->rawData = this->rawData.substring(this->rawData.indexOf(',') + 1, this->rawData.length());
            
            //04906.85799,W,000122.00,A,A*64
            this->rawData = this->rawData.substring(this->rawData.indexOf(',') + 1, this->rawData.length());

            //04906.85799
            this->longitudeString = this->rawData.substring(0, this->rawData.indexOf(','));

            this->latDeg = this->latitudeString.substring(0, this->latitudeString.indexOf('.') - 2).toInt();
            this->latMin = this->latitudeString.substring(this->latitudeString.indexOf('.') - 2, this->latitudeString.length()).toFloat();

            this->longDeg = this->longitudeString.substring(0, this->longitudeString.indexOf('.') - 2).toInt();
            this->longMin = this->longitudeString.substring(this->longitudeString.indexOf('.') - 2, this->longitudeString.length()).toFloat();

            *latitude = this->latDeg + ( this->latMin / 60 );
            *longitude = this->longDeg + ( this->longMin / 60 );

	}
}
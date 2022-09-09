#include <Arduino.h>

#define BROKEN_LINE '\n'
#define GPGLL ((const char *) "$GPGLL")


#ifndef servicegps_h
#define servicegps_h

class ServiceGPS
{
	
	
	public:

		void init(HardwareSerial *serial);
		void getCoordinates(float *latitude, float *longitude);
		

	private:

		HardwareSerial * __serial;
		char readChar = 0;
		String data, toCompare, rawData, latitudeString, longitudeString;
		int latDeg, longDeg;
		float latMin, longMin;

		void readGPS(String *dataRead);

};

#endif
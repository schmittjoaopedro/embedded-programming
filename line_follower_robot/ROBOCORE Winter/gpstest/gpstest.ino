//#include <LiquidCrystal.h>
#include "ServiceGPS.h"

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
ServiceGPS serviceGPS;

float latitude, longitude;

void setup() {
    
    serviceGPS.init(&Serial1);
    Serial.begin(38400);
    //lcd.begin(16, 2);
    //lcd.print("Starting...");
    delay(500);
    //lcd.clear();

}

void loop() {
    serviceGPS.getCoordinates(&latitude, &longitude);

    //lcd.setCursor(0, 0);
    Serial.print("Lat: ");
    //lcd.setCursor(6, 0);
    Serial.print(latitude, 5);
    //lcd.setCursor(0, 1);
    Serial.print("Long: ");
    //lcd.setCursor(6, 1);
    Serial.println(longitude, 5);

}

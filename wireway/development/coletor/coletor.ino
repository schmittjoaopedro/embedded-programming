#include <Wire.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <XBee.h>


#define DHTTYPE            	DHT22
#define DHTPIN             	9
#define SOIL_HUM_PIN				A3
#define RAIN_PIN						A2
#define SUCCESS_LED					11
#define ERROR_LED						10
#define PACKET_SIZE         40
#define RELE_1							4
#define RELE_2							5


DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

//Coletor and Actuator data
String serialData = "";
double 	pressure = 0.0,
				temperature = 0.0,
				humidity = 0.0,
				soilHumidity = 0.0,
				rain = 0.0;
long lastTimeActuator = 0, lastTimeColetor = 0;


//XBee variables
char payload[] = "                                        ";
char buffer[PACKET_SIZE];
XBee xbee = XBee();
ZBRxResponse rx = ZBRxResponse();
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40B910D5);
ZBTxRequest zbTx = ZBTxRequest(addr64, (uint8_t*)   payload, strlen(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();


void setup() {

	pinMode(SUCCESS_LED, OUTPUT);
	pinMode(ERROR_LED, OUTPUT);
	pinMode(RELE_1, OUTPUT);
	pinMode(RELE_2, OUTPUT);

  Serial.begin(9600);
  xbee.setSerial(Serial);
  dht.begin();
  if (!bmp.begin()) {
    flash(SUCCESS_LED, 5, 50);
  }

  flash(SUCCESS_LED, 15, 20);
  flash(ERROR_LED, 15, 20);

}

void loop() {

	readXBee();
  if(millis() - lastTimeColetor > 30000) {
    collect();
  }

}


String collectData() {

	String data = "";

	temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  pressure = bmp.readPressure();
  soilHumidity = 100.0 - ((((int) analogRead(SOIL_HUM_PIN)) / 1024.0) * 100.0);
  rain = 100.0 - ((((int) analogRead(RAIN_PIN)) / 1024.0) * 100.0);

  data += doubleToString(temperature, 1);
  data += ";";
  data += doubleToString(humidity, 1);
  data += ";";
  data += doubleToString(pressure, 1);
  data += ";";
  data += doubleToString(soilHumidity, 1);
  data += ";";
  data += doubleToString(rain, 1);
  data += ";";

  return data;

}


void readXBee() {

  serialData = "";

  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {

    flash(SUCCESS_LED, 1, 100);

    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {

      xbee.getResponse().getZBRxResponse(rx);

      for (int i = 0; i < rx.getDataLength(); i++) {
        serialData += (char) rx.getData(i);
      }
      flash(SUCCESS_LED, 5, 20);
      action();

    } else {
        flash(ERROR_LED, 5, 20);
    }

  } else if (xbee.getResponse().isError()) {

    flash(ERROR_LED, 5, 100);

  }

}

void action() {

  String sRele1 = serialData.substring(0, 1);
  String sRele2 = serialData.substring(1, 2);

  digitalWrite(RELE_1, sRele1.toInt());
  digitalWrite(RELE_2, sRele2.toInt());

  lastTimeActuator = millis();

}


void collect() {

	String dataCollected = collectData();

  dataCollected.toCharArray(buffer, PACKET_SIZE);

  for (int i = 0; i < PACKET_SIZE; payload[i] = ' ', i++);
  for (int i = 0; i < PACKET_SIZE; i++) {
    if (buffer[i] != '\0')
      payload[i] = buffer[i];
    else
      break;
  }

  xbee.send(zbTx);

  delay(100);

  if (xbee.readPacket(500)) {

    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) {

      xbee.getResponse().getZBTxStatusResponse(txStatus);

      if (txStatus.getDeliveryStatus() == SUCCESS) {
        flash(SUCCESS_LED, 15, 20);
      } else {
        flash(ERROR_LED, 15, 20);
      }
    }

  } else if (xbee.getResponse().isError()) {
      flash(ERROR_LED, 5, 20);
  } else {
      flash(ERROR_LED, 5, 200);
  }

  lastTimeColetor = millis();

}



//External status notification
void flash(int led, int count, int time) {
	for(int i = 0; i < count; i++) {
    digitalWrite(led, HIGH);
    delay(time);
    digitalWrite(led, LOW);
    if(i < count - 1)
    	delay(time);
	}
}


String doubleToString(double input, int decimalPlaces) {
  if (decimalPlaces != 0) {
    String string = String((int)(input * pow(10, decimalPlaces)));
    if (abs(input) < 1) {
      if (input > 0)
        string = "0" + string;
      else if (input < 0)
        string = string.substring(0, 1) + "0" + string.substring(1);
    }
    return string.substring(0, string.length() - decimalPlaces) + "." + string.substring(string.length() - decimalPlaces);
  }
  else {
    return String((int)input);
  }
}

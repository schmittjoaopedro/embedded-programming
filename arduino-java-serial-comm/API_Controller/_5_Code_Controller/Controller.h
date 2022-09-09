#include "Arduino.h"
#include "Utilities.h"
#include "Servo.h"

#ifndef Controller_h
#define Controller_h

class Controller {

private:
	String data;
	Utilities util;
	String mapped;
	//Servo servos[50];

public:
	/*

	D - Digital
	S - Servo
	A - Analogico
	P - PWM

	PWM
		WRITE - Define para escrita
		READ - Define para leitura (NÃO IMPLEMENTADO)

	Analog:
		WRITE - Define para escrita (NÃO IMPLEMENTADO)
		READ - Define para leitura

	define:
		[type]-[pin]:[argument]
		D-1:INPUT,D-13:OUTPUT,S-2:90,P-12:WRITE,P-11:READ
	*/
	void define(String data);

	/*

	Digital:
		HIGH: escreve HIGH
		LOW: escreve LOW
		READ: faz leitura e retorna

	PWM:
		0 - 255 -> range de escrita
		READ: ler valores 0-255

	Analog:
		READ: retorna entre 0-1023

	execute
		D-[pin]:[value]

		S-[pin]:[angulation]

		P-[pin]:[type] 	
			Obs: [type] = READ -> leitura || 0-255 -> escrita

		A-[pin]:[type]
	*/
	void execute(String data);


	void init();

	//Digital
	void fillDigitalPin(String data);
	void executeDigitalPin(String data);

	//Servo
	void fillServoPin(String data);
	void executeServoPin(String data);

	//PWM
	void fillPWMPin(String data);
	void executePWMPin(String data);

	//Analog
	void fillAnalogPin(String data);
	void executeAnalogPin(String data);

	String type(int pin);
	void loggerPositions();

	//Variables
		bool defined;
		//25 servos in maximum
		Servo servos[20];
		String PWM[25];
		String analog[25];

};

#endif
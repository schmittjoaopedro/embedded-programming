#include "Humanoide.h"

Humanoide::Humanoide()
{
	this->timeRespawn = 400;
}

void Humanoide::setTimeRespawn(int time)
{
	if(time <= 400){
		this->timeRespawn = 400;	
	}else{
		this->timeRespawn = time;
	}
}

int Humanoide::getTimeRespawn()
{
	return this->timeRespawn;
}

void Humanoide::onTimeRespanw()
{
	delay(getTimeRespawn());
}

void Humanoide::init(int legRightPin, int legLeftPin, int shinRightPin, int shinLeftPin)
{
	this->legRight.attach(legRightPin);
	this->legLeft.attach(legLeftPin);
	this->shinRight.attach(shinRightPin);
	this->shinLeft.attach(shinLeftPin);
	stopWalk();
}

void Humanoide::aheadWalk(){

	this->shinRight.write(30);
	this->shinLeft.write(90);
	this->legRight.write(150);
	this->legLeft.write(150);
	onTimeRespanw();
	this->shinRight.write(90);
	this->shinLeft.write(150);
	this->legLeft.write(30);
	this->legRight.write(30);
	onTimeRespanw();
}

void Humanoide::stopWalk()
{
	this->legRight.write(90);
	this->legLeft.write(90);
	this->shinLeft.write(90);
	this->shinRight.write(90);
}

void Humanoide::danceCanCan()
{
	stopWalk();
	this->legRight.write(180);
	this->shinRight.write(30);
	onTimeRespanw();
	stopWalk();
	onTimeRespanw();
	this->legRight.write(150);
	onTimeRespanw();
	stopWalk();
	onTimeRespanw();

	this->legLeft.write(30);
	this->shinLeft.write(180);
	onTimeRespanw();
	stopWalk();
	onTimeRespanw();
	this->legLeft.write(30);
	onTimeRespanw();
	stopWalk();
	onTimeRespanw();
}
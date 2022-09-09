#include "Humanoid.h"

void Humanoid::defineEquation()
{
	Serial.print(this->acelerometer.defineEquation());
}
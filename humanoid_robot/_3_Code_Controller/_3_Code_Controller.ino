#include "Utilities.h"
#include "Humanoide.h"
#include <Servo.h>

Utilities utils;
Humanoide humanoide;
Servo s;

void setup()
{
  Serial.begin(9600);
  humanoide.init(3,9,5,10);
}

void loop()
{
  delay(100);
  String comand = utils.readString();
  if(comand == "ahead")
  {
    for (int i = 0; i < 3; ++i)
    {
      humanoide.setTimeRespawn(400 * (i^2));
      humanoide.aheadWalk();
    }
  }
  if(comand == "aheadfast"){
    humanoide.setTimeRespawn(250);
    for (int i = 0; i < 10; ++i)
    {
      humanoide.aheadWalk();
    }
  }
  if(comand == "cancan")
  {
    humanoide.danceCanCan();
  }
  humanoide.stopWalk();
}

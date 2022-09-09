#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

char movimentoDesignado;

RF24 radio(9,10);

const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void)
{ 
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  if(Serial.available() > 0)
 {
   char entrada = Serial.read();
   radio.write( &entrada, sizeof(unsigned char) );
 }
}


int pinMotor = 9;
int pinPotenciometro = 0;
int valorLido;

void setup(){
  pinMode(pinMotor, OUTPUT);
}

void loop(){
  valorLido = analogRead(pinPotenciometro);
  valorLido = map(valorLido, 0, 1023, 0, 255);
  
  analogWrite(pinMotor, valorLido);
}

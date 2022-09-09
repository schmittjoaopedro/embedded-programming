

void setup(){
  
  Serial.begin(9600);
  
}

void loop(){
  
  int z = analogRead(2);
  int x = analogRead(1);
  int y = analogRead(0);
  
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Z: ");
  Serial.print(z);
  Serial.print(" Y: ");
  Serial.println(y);
  
}



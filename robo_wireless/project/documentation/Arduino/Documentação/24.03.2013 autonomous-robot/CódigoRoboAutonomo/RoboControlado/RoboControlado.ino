int FrenteDireito = 11;
int TrasDireito = 13;
int FrenteEsquerdo = 12;
int TrasEsquerdo = 10;


void setup() {
 
Serial.begin(9600);
 
pinMode(FrenteDireito, OUTPUT);
pinMode(TrasDireito, OUTPUT);
pinMode(FrenteEsquerdo, OUTPUT);
pinMode(TrasEsquerdo, OUTPUT);

digitalWrite(FrenteDireito,LOW);
digitalWrite(TrasDireito,LOW);
digitalWrite(FrenteEsquerdo,LOW);
digitalWrite(TrasEsquerdo,LOW);
}
 
void loop() {
 
if(Serial.available() > 0)
 {
 int entrada = Serial.read();
 
switch (entrada){
 case 'w':
 frente();
 break;
 
case 's':
 re();
 break;
 
case 'p':
 parar();
 
 case 'c':
 centro();
 break;
 
 case 'd':
 direita();
 break;
 
case 'a':
 esquerda();
 break;
 }
 }
}
void frente(){
  digitalWrite(FrenteDireito,HIGH);
  digitalWrite(TrasDireito,LOW);
  digitalWrite(FrenteEsquerdo,HIGH);
  digitalWrite(TrasEsquerdo,LOW);
}
void re(){
  digitalWrite(FrenteDireito,LOW);
  digitalWrite(TrasDireito,HIGH);
  digitalWrite(FrenteEsquerdo,LOW);
  digitalWrite(TrasEsquerdo,HIGH);
}
void parar(){
  digitalWrite(FrenteDireito,LOW);
  digitalWrite(TrasDireito,LOW);
  digitalWrite(FrenteEsquerdo,LOW);
  digitalWrite(TrasEsquerdo,LOW);
}
 
void direita(){
  digitalWrite(FrenteDireito,HIGH);
  digitalWrite(TrasDireito,LOW);
  digitalWrite(FrenteEsquerdo,LOW);
  digitalWrite(TrasEsquerdo,HIGH);
 }
 
void esquerda(){
  digitalWrite(FrenteDireito,LOW);
  digitalWrite(TrasDireito,HIGH);
  digitalWrite(FrenteEsquerdo,HIGH);
  digitalWrite(TrasEsquerdo,LOW);
}
void centro(){
 digitalWrite(7, LOW);
 digitalWrite(6, LOW);
}

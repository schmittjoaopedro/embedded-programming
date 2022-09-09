#include <Servo.h> // Comando para importação da biblioteca que faz controle do servo motor

int URPWM = 3;  // Saída PWM 0-25000US, cada 50US representam um centímetro
int URTRIG=5;   // Pino do gatilho PWM
Servo servo1;   // Variável do tipo servo que fará dará acesso as funções do servo motor

// # Conexão:
// # Pino 1 VCC (V3.2 URM) -> VCC (Arduino)
// # Pino 2 GND (URM V3.2) -> GND (Arduino)
// # 4 Pin PWM (URM V3.2) -> Pino 3 (Arduino)
// # Pino 6 COMP / TRIG (URM V3.2) -> Pino 5 (Arduino)

unsigned long distanciaMedida; // Variável para armanezar o valor lido pelo sensor
int anteriorMenor = 0;  // Variável de controle para impedir oscilação contante do motor servo armazenará um valor menor que o lido
int anteriorMaior = 0;  // Variável de controle para impedir oscilação contante do motor servo armazenará um valor maior que o lido
 
unsigned int distancia=0; // Variável que armazenará o valor para impressão e escrita no servo
uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};    // comando medida / distância /
 
//Seta os parâmetros iniciais
void setup(){                               
  Serial.begin(9600);            // Inicia a configuração serial com o monitor em uma taxa de 9600 bits        
  ModoPWMSetup();                // Invoca função ModoPWMSetup
  servo1.attach(9);              // Define o pino 9 para escrita do servo motor
}

//Inicio o loop de repetição infinata 
void loop()
{
 ModoPWM();  //Chamada da função ModoPWM
 delay(500); //Delay de 500 milissegundos até o próximo loop
}                 
 
void ModoPWMSetup(){ 
  pinMode(URTRIG,OUTPUT);           // puxar um baixo no pino COMP / TRIG       
  
  digitalWrite(URTRIG,HIGH);        // Set / para ALTA
  
  pinMode(URPWM, INPUT);            // Enviando comando Ativar modo PWM
  
  for(int i=0;i<4;i++){             // Loop para iniciar parâmetros da variável definida acima
      Serial.write(EnPwmCmd[i]);
   } 
}
 
void ModoPWM(){                                // um puxão baixo no pino COMP / TRIG provocando uma leitura do sensor
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);                // leitura / Pin PWM pulsos de saída           
     
    distanciaMedida=pulseIn(URPWM,LOW);        // Leitra do valor de pulso de entrada
     
    if(distanciaMedida==50000){                // a leitura é inválido.
      Serial.print("Invalid");    
   }
    else{
      distancia=distanciaMedida/50;             // todos os níveis 50us baixo significa um centímetro, (conversão para centímetros)
   }
  Serial.print("Distance=");
  Serial.print(distancia);
  
  if( distancia < 95){                                                    //Verificador para impedir picos de leitura e acionar irregularidades do motor, aumentando a precisão
      int servoAngulo = map(distancia, 5, 95, 0, 180);                    //Mapeamento da leitura do sensor para um valor compreendido na faixa do servo motor em angulo de 0 - 180 graus
      if(servoAngulo < anteriorMenor || servoAngulo > anteriorMaior){     //Compara o valor de leitura com o menor e maior valor de flag, esse teste aumenta a precisão do motor e diminui instabilidades
        servo1.write(servoAngulo);                                        //Escreve o valor de angulação para ativação do motor servo  
        anteriorMenor = servoAngulo - 10;                                 //Atualiza as flags para a leitura do motor
        anteriorMaior = servoAngulo + 10;
      } 
  }
  Serial.println("cm");
}


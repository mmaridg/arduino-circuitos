/*  Código Para Controle De Motor DC Via PWM Arduino
    
    Monte seus próprios projetos sem dificuldade com programação! 
    ACESSE: https://flaviobabos.com.br/
*/

// Define as variáveis utilizadas
#define pinovelocidade 3
#define pinoPonteH1 2
#define pinoPonteH2 7
#define potenciometro A0
   
void setup()  
{  
  // Define os pinos como saida  
  pinMode(3, OUTPUT);  
  pinMode(2, OUTPUT);  
  pinMode(7, OUTPUT); 

  // Define o pino do potenciômetro como entrada
  pinMode(A0, INPUT); 
  }  
   
void loop(){  
  
  // Faz a leitura do Potenciômetro 
  int velocidade = analogRead(potenciometro)/4;  

  // Define a velocidade de rotacao do motor 
  analogWrite(pinovelocidade, velocidade);   

  // Aciona o motor  
  digitalWrite(pinoPonteH1, LOW);  
  digitalWrite(pinoPonteH2, HIGH);    
}  
#include "Keypad.h"
#include "SimpleOLED.h"
#include "DHT.h"

SimpleOLED display(0x3C, 128, 64); 


const byte LINHAS = 4; 
const byte COLUNAS = 4; 
char mapaTeclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 
byte pinosLinhas[LINHAS] = {8, 7, 6, 5};  
byte pinosColunas[COLUNAS] = {12, 11, 10, 9}; 
Keypad teclado = Keypad(makeKeymap(mapaTeclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS); 

const int pinoPIR = A3;

#define DHTPIN 4     
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

String senhaDigitada = "";
bool aguardandoSenha = false;

void setup() {
  Serial.begin(9600);
  
  display.begin(); 
  display.clear(); 
  
  pinMode(pinoPIR, INPUT); 
  
  pinMode(DHTPIN, INPUT_PULLUP); 
  dht.begin(); 
  
  display.setCursor(0, 20); 
  display.println("Calibrando o");
  display.setCursor(0, 35);
  display.println("sensor PIR...");
  display.display(); 
  
  delay(15000); 
  
  display.clear(); 
  display.setCursor(0, 30); 
  display.println("Sistema Iniciado"); 
  display.display(); 
  
  delay(2000);
  
  display.clear(); 
  display.display(); 
}

void loop() {
  int estadoPIR = digitalRead(pinoPIR); 

  if (estadoPIR == HIGH && !aguardandoSenha) { 
    aguardandoSenha = true;
    senhaDigitada = "";
    
    display.clear(); 
    display.setCursor(0, 10); 
    display.println("Insira sua");
    display.setCursor(0, 25);
    display.println("senha de acesso.");
    display.display(); //[cite: 1]
  }

  if (aguardandoSenha) {
    char teclaPressionada = teclado.getKey(); 
    
    if (teclaPressionada) { 
      senhaDigitada += teclaPressionada;
      
      display.clear(); 
      display.setCursor(0, 10);
      display.println("Senha: ");
      display.setCursor(0, 30);
      display.println(senhaDigitada.c_str());
      display.display(); 
      

        if (senhaDigitada.length() == 4) {
          delay(500); 
          
          display.clear(); 
          
          if (senhaDigitada == "0401") {
            display.setCursor(0, 30); 
            display.println("Bem-vinda, Mariana!");
          } 
          else if (senhaDigitada == "1909") {
            display.setCursor(0, 30); 
            display.println("Bem-vinda, Ludmila!");
          } 
          else if (senhaDigitada == "2710") {
            display.setCursor(0, 30); 
            display.println("Bem-vinda, Evilyn!");
          } 
          else if (senhaDigitada == "3011") {
            display.setCursor(0, 30); 
            display.println("Bem-vindo, Tiago!");
          } 
          else if (senhaDigitada == "1234") {
            float t = dht.readTemperature(); 
            display.setCursor(0, 15); 
            display.println("Temperatura");
            display.setCursor(0, 35); 
            display.print("identificada: ");
            display.print(t, 1); 
            display.print("C");
          } 
          else {
            display.setCursor(0, 30); 
            display.println("Senha Incorreta!");
          }
          
          display.display(); 
          
          delay(3000); 
          display.clear(); 
          display.display(); 
          
          aguardandoSenha = false;
          senhaDigitada = "";
          
          delay(3000);
        }
    }
  }
}

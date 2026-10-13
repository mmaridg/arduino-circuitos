#include "Keypad.h"
#include "SimpleOLED.h"
#include "DHT.h"

// Configurações do Display
SimpleOLED display(0x3C, 128, 64); //[cite: 1, 4]

// Teclado
const byte LINHAS = 4; //[cite: 1]
const byte COLUNAS = 4; //[cite: 1]
char mapaTeclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; //[cite: 1]
byte pinosLinhas[LINHAS] = {8, 7, 6, 5};  //[cite: 1]
byte pinosColunas[COLUNAS] = {12, 11, 10, 9}; //[cite: 1]
Keypad teclado = Keypad(makeKeymap(mapaTeclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS); //[cite: 1]

// Configurações do Sensor PIR
const int pinoPIR = A3; //[cite: 3]

// Configurações DHT11
#define DHTPIN 4     //[cite: 7]
#define DHTTYPE DHT11 //[cite: 7]
DHT dht(DHTPIN, DHTTYPE); //[cite: 7]

// Variáveis de controle
String senhaDigitada = "";
bool aguardandoSenha = false;

void setup() {
  Serial.begin(9600);
  
  // Inicializa Display
  display.begin(); //[cite: 1]
  display.clear(); //[cite: 1]
  
  // Inicializa PIR
  pinMode(pinoPIR, INPUT); //[cite: 3]
  
  // Inicializa DHT 
  pinMode(DHTPIN, INPUT_PULLUP); //[cite: 7]
  dht.begin(); //[cite: 7]
  
  // Aviso de calibração do PIR no display
  display.setCursor(0, 20); //[cite: 1, 4]
  display.println("Calibrando o");
  display.setCursor(0, 35);
  display.println("sensor PIR...");
  display.display(); //[cite: 1]
  
  // O sensor precisa de 15 a 60 segundos para calibrar o ambiente ao ligar[cite: 3]
  delay(15000); 
  
  // Aviso de sistema pronto
  display.clear(); //[cite: 1]
  display.setCursor(0, 30); //[cite: 1, 4]
  display.println("Sistema Iniciado"); //[cite: 1]
  display.display(); //[cite: 1]
  
  delay(2000);
  
  // Limpa a tela e ATUALIZA o display para apagar a mensagem fisicamente
  display.clear(); //[cite: 1]
  display.display(); //[cite: 1]
}

void loop() {
  int estadoPIR = digitalRead(pinoPIR); //[cite: 3]

  // Se o PIR detectar movimento e o sistema não estiver no meio de uma digitação
  if (estadoPIR == HIGH && !aguardandoSenha) { //[cite: 3]
    aguardandoSenha = true;
    senhaDigitada = "";
    
    display.clear(); //[cite: 1]
    display.setCursor(0, 10); //[cite: 1, 4]
    display.println("Insira sua");
    display.setCursor(0, 25);
    display.println("senha de acesso.");
    display.display(); //[cite: 1]
  }

  // Se o sistema estiver aguardando senha, monitora o teclado
  if (aguardandoSenha) {
    char teclaPressionada = teclado.getKey(); //[cite: 1]
    
    if (teclaPressionada) { //[cite: 1]
      senhaDigitada += teclaPressionada;
      
      // Atualiza o display para mostrar a senha sendo digitada
      display.clear(); //[cite: 1]
      display.setCursor(0, 10); //[cite: 1]
      display.println("Senha: ");
      display.setCursor(0, 30);
      display.println(senhaDigitada.c_str());
      display.display(); //[cite: 1]
      
      // Quando 4 dígitos forem inseridos, faz a verificação
      if (senhaDigitada.length() == 4) {
        display.clear(); 
        display.setCursor(0, 10); 
        display.println("Senha: ");
        display.setCursor(0, 30);
        display.println(senhaDigitada.c_str()); 
        display.display();
        
        if (senhaDigitada == "0401") {
          display.println("Bem-vinda, Mari!");
        } 
        else if (senhaDigitada == "1909") {
          display.println("Bem-vinda, Lud!");
        } 
        else if (senhaDigitada == "2711") {
          display.println("Bem-vinda, Evi!");
        } 
        else if (senhaDigitada == "3011") {
          display.println("Bem-vindo, Ti!");
        } 
        else if (senhaDigitada == "1234") {
          float t = dht.readTemperature(); //[cite: 7]
          display.setCursor(0, 20); //[cite: 1]
          display.println("Temperatura");
          display.setCursor(0, 40);
          display.print("identificada: ");
          display.print(t); //[cite: 7]
          display.print(" graus");
        } 
        else {
          display.println("Senha Incorreta!");
        }
        
        display.display(); //[cite: 1]
        
        // Mantém a mensagem na tela por 3 segundos antes de resetar o sistema
        delay(3000); 
        display.clear(); //[cite: 1]
        display.display(); //[cite: 1]
        
        // Reseta as variáveis para nova detecção
        aguardandoSenha = false;
        senhaDigitada = "";
        
        // Pequena pausa para evitar leitura imediata fantasma do PIR
        delay(1000);
      }
    }
  }
}

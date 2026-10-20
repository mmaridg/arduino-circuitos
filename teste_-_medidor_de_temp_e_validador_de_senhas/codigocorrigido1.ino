#include "Keypad.h"
#include "SimpleOLED.h"
#include "DHT.h"

// Configurações do Display
SimpleOLED display(0x3C, 128, 64); //[cite: 17]

// Teclado
const byte LINHAS = 4; //[cite: 17]
const byte COLUNAS = 4; //[cite: 17]
char mapaTeclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; //[cite: 17]

// CORREÇÃO: Pinos invertidos para corresponder à montagem no SimulIDE
byte pinosLinhas[LINHAS] = {12, 11, 10, 9};  
byte pinosColunas[COLUNAS] = {8, 7, 6, 5}; 

Keypad teclado = Keypad(makeKeymap(mapaTeclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS); //[cite: 17]

// Configurações do Sensor PIR (Simulado por uma chave)
const int pinoPIR = A3; //[cite: 17]

// Configurações DHT
#define DHTPIN 4     //[cite: 17]
#define DHTTYPE DHT22 // CORREÇÃO: Atualizado para DHT22 conforme o componente da simulação
DHT dht(DHTPIN, DHTTYPE); //[cite: 17]

// Variáveis de controle
String senhaDigitada = ""; //[cite: 17]
bool aguardandoSenha = false; //[cite: 17]

void setup() {
  Serial.begin(9600); //[cite: 17]
  
  // Inicializa Display
  display.begin(); //[cite: 17]
  display.clear(); //[cite: 17]
  
  // Inicializa PIR
  pinMode(pinoPIR, INPUT); //[cite: 17]
  
  // Inicializa DHT 
  pinMode(DHTPIN, INPUT_PULLUP); //[cite: 17]
  dht.begin(); //[cite: 17]
  
  // Aviso de calibração do PIR no display
  display.setCursor(0, 20); //[cite: 17]
  display.println("Calibrando o"); //[cite: 17]
  display.setCursor(0, 35); //[cite: 17]
  display.println("sensor PIR..."); //[cite: 17]
  display.display(); //[cite: 17]
  
  // O sensor precisa de 15 a 60 segundos para calibrar o ambiente ao ligar[cite: 17]
  delay(15000); //[cite: 17]
  
  // Aviso de sistema pronto
  display.clear(); //[cite: 17]
  display.setCursor(0, 30); //[cite: 17]
  display.println("Sistema Iniciado"); //[cite: 17]
  display.display(); //[cite: 17]
  
  delay(2000); //[cite: 17]
  
  // Limpa a tela e ATUALIZA o display para apagar a mensagem fisicamente
  display.clear(); //[cite: 17]
  display.display(); //[cite: 17]
}

void loop() {
  int estadoPIR = digitalRead(pinoPIR); //[cite: 17]

  // Se a chave for fechada (HIGH) e o sistema não estiver no meio de uma digitação
  if (estadoPIR == HIGH && !aguardandoSenha) { //[cite: 17]
    aguardandoSenha = true; //[cite: 17]
    senhaDigitada = ""; //[cite: 17]
    
    display.clear(); //[cite: 17]
    display.setCursor(0, 10); //[cite: 17]
    display.println("Insira sua"); //[cite: 17]
    display.setCursor(0, 25); //[cite: 17]
    display.println("senha de acesso."); //[cite: 17]
    display.display(); //[cite: 17]
  }

  // Se o sistema estiver aguardando senha, monitora o teclado
  if (aguardandoSenha) { //[cite: 17]
    char teclaPressionada = teclado.getKey(); //[cite: 17]
    
    if (teclaPressionada) { //[cite: 17]
      senhaDigitada += teclaPressionada; //[cite: 17]
      
      // Atualiza o display para mostrar a senha sendo digitada
      display.clear(); //[cite: 17]
      display.setCursor(0, 10); //[cite: 17]
      display.println("Senha: "); //[cite: 17]
      display.setCursor(0, 30); //[cite: 17]
      display.println(senhaDigitada.c_str()); //[cite: 17]
      display.display(); //[cite: 17]
      
      // Quando 4 dígitos forem inseridos, faz a verificação
      if (senhaDigitada.length() == 4) { //[cite: 17]
        // Pausa de meio segundo para o usuário ver o 4º dígito antes da tela mudar
        delay(500); //[cite: 17]
        
        display.clear(); // Limpa o "Senha: 1234" da tela[cite: 17]
        
        if (senhaDigitada == "0401") { //[cite: 17]
          display.setCursor(0, 30); //[cite: 17]
          display.println("Bem-vinda, Mari!"); //[cite: 17]
        } 
        else if (senhaDigitada == "1909") { //[cite: 17]
          display.setCursor(0, 30); //[cite: 17]
          display.println("Bem-vinda, Lud!"); //[cite: 17]
        } 
        else if (senhaDigitada == "2711") { //[cite: 17]
          display.setCursor(0, 30); //[cite: 17]
          display.println("Bem-vinda, Evi!"); //[cite: 17]
        } 
        else if (senhaDigitada == "3011") { //[cite: 17]
          display.setCursor(0, 30); //[cite: 17]
          display.println("Bem-vindo, Ti!"); //[cite: 17]
        } 
        else if (senhaDigitada == "1234") { //[cite: 17]
          float t = dht.readTemperature(); //[cite: 17]
          display.setCursor(0, 15); //[cite: 17]
          display.println("Temperatura"); //[cite: 17]
          display.setCursor(0, 35); //[cite: 17]
          display.print("identificada: "); //[cite: 17]
          display.print(t, 1); // O ", 1" formata para ter apenas 1 casa decimal[cite: 17]
          display.print("C"); //[cite: 17]
        } 
        else {
          display.setCursor(0, 30); //[cite: 17]
          display.println("Senha Incorreta!"); //[cite: 17]
        }
        
        display.display(); //[cite: 17]
        
        // Mantém a mensagem de boas-vindas/temperatura na tela por 3 segundos
        delay(3000); //[cite: 17]
        display.clear(); //[cite: 17]
        display.display(); //[cite: 17]
        
        // Reseta as variáveis
        aguardandoSenha = false; //[cite: 17]
        senhaDigitada = ""; //[cite: 17]
        
        // Pausa para evitar nova leitura imediata
        delay(3000); //[cite: 17]
      }
    }
  }
}

//Instruções do display LCD
//S R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0

//00 0000 0001 - Clear Display
//00 0000 0010 — Return Home
//00 0000 01 I/D S - move cursor e desloca display
//I/D =1 - Incrementa
//S = 1 - desloca display junto
//00 0000 1 D C B - configuração do display
//D = 1 - Liga display
//C = 1 - liga cursor
//B = 1 - Pisca cursor
//00 0001 S/C R/L 00 - move cursor e desloca display sem alterar registro de dados
//S/C = 1 - desloca display
//R/L = 1 - Desloca para a direita
//00 001 DL N F 00  - configura interface de dados, número de linhas e tipo fonte.
//DL = 1 - 8 bits
//N = 1 - 2 linhas
//F = 1 - 5x10 pontos
//00 01 ACG ACG ACG ACG ACG ACG - Seta endereço do registro de comando
//00 1 ADD ADD ADD ADD ADD ADD ADD - //Seta endereço do registro de dados
//01 BF AC AC AC AC AC AC AC - Lê flag de ocupado
//1 0 Write data
//1 1 Read data

const byte D4 = 2;
const byte D5 = 3;
const byte D6 = 4;
const byte D7 = 5;
const byte En = 6;
const byte RS = 7;

void inicializaLCD(void);
void escreveDisplay(char b);
void escreverComando(char a);

//Vetor de Caracteres a 
//serem mostrados no display
volatile char Dado[6];

//volatile float dado;
volatile int antigo = 0;

void setup()
{
//Define pinos de saída
	pinMode(D4,OUTPUT);
	pinMode(D5,OUTPUT);
	pinMode(D6,OUTPUT);
	pinMode(D7,OUTPUT);
	pinMode(En,OUTPUT);
	pinMode(RS,OUTPUT);
	
	for(int i = 0; i < 6; i++)
	{
		Dado[i] = '0';
	}
	//Serial.begin(9600);
	inicializaLCD();
}

void loop()
{
	float valorMedido = 0;
//Lê variável na entrada A0
	int valor = analogRead(A0);
	
//Se valor medido mudou
	if(antigo != valor)
	{
		
//Obtém valor medido
		valorMedido = valor*5.0/1023;		

//Converte valorMedido para
//array de caracteres
		dtostrf(valorMedido,5, 2, Dado);

//Seleciona registro de dados
		digitalWrite(RS,HIGH);
		
//Envia caracteres para o display
		escreveDisplay(Dado[0]);
		escreveDisplay(Dado[1]);
		escreveDisplay(Dado[2]);
		escreveDisplay(Dado[3]);
		escreveDisplay(Dado[4]);
//Seleciona registro de comando		
		digitalWrite(RS,LOW);

//Envia comando para retornar
//ao início da segunda linha
		escreveDisplay(0xC0);
		
//Guarda valor medido
		antigo = valor;	
	}
}

void inicializaLCD(void)
{
//Sequência mágica
	byte a = 0x33;
	byte b = 0x32;//4 bits

	byte c = 0x2C;
//0 0 1 DL N F — —
//DL = 0 - 4 bits
//N = 1 - 2 linhas
//F = 1 - 5x10 pontos	


  
	byte d = 0x0C;
//0 0 0 0 1 D C B
//D = 1 - Liga display
//C = 1 - Liga cursor
//B = 1 - Pisca caracter de cursor	

  byte e = 0x01;
  
 digitalWrite(RS,LOW);
	escreverComando(a);	
	escreverComando(b);	

	escreverComando(c);	

	escreverComando(d);
  //escreverComando(0x01);  
  escreverComando(0x02);
  
  
//Seleciona registro de dados
	digitalWrite(RS,HIGH);
	escreveDisplay('V');
	escreveDisplay('a');
	escreveDisplay('l');
	escreveDisplay('o');
	escreveDisplay('r');
	escreveDisplay(':');

//Seleciona registro de comando	
	digitalWrite(RS,LOW);
	
//Envia comando para saltar
//para o início da segunda linha
	escreveDisplay(0xC0);
}

void escreveDisplay(char a)
{
	if((a>>4)&0x01)
		digitalWrite(D4,HIGH);
	else
		digitalWrite(D4,LOW);
	
	if((a>>5)&0x01)
		digitalWrite(D5,HIGH);
	else
		digitalWrite(D5,LOW);

	if((a>>6)&0x01)
		digitalWrite(D6,HIGH);
	else
		digitalWrite(D6,LOW);

	if((a>>7)&0x01)
		digitalWrite(D7,HIGH);
	else
		digitalWrite(D7,LOW);

//Pulsa o Eanable		
	digitalWrite(En,HIGH);
	delayMicroseconds(10);
	digitalWrite(En,LOW);

	if((a)&0x01)
		{digitalWrite(D4,HIGH);}
	else
		{digitalWrite(D4,LOW);}
	
	if((a>>1)&0x01)
		{digitalWrite(D5,HIGH);}
	else
		{digitalWrite(D5,LOW);}
	
	if((a>>2)&0x01)
		{digitalWrite(D6,HIGH);}
	else
		{digitalWrite(D6,LOW);}
	
	if((a>>3)&0x01)
		{digitalWrite(D7,HIGH);}
	else
		{digitalWrite(D7,LOW);}	

//Pulsa o Enable	
	digitalWrite(En,HIGH);
	delayMicroseconds(10);
	digitalWrite(En,LOW);
}

void escreverComando(char a)
{
  if((a>>4)&0x01)
    digitalWrite(D4,HIGH);
  else
    digitalWrite(D4,LOW);
  
  if((a>>5)&0x01)
    digitalWrite(D5,HIGH);
  else
    digitalWrite(D5,LOW);

  if((a>>6)&0x01)
    digitalWrite(D6,HIGH);
  else
    digitalWrite(D6,LOW);

  if((a>>7)&0x01)
    digitalWrite(D7,HIGH);
  else
    digitalWrite(D7,LOW);

//Pulsa o Eanable   
  digitalWrite(En,HIGH);
  delayMicroseconds(10);
  digitalWrite(En,LOW);

  if((a)&0x01)
    {digitalWrite(D4,HIGH);}
  else
    {digitalWrite(D4,LOW);}
  
  if((a>>1)&0x01)
    {digitalWrite(D5,HIGH);}
  else
    {digitalWrite(D5,LOW);}
  
  if((a>>2)&0x01)
    {digitalWrite(D6,HIGH);}
  else
    {digitalWrite(D6,LOW);}
  
  if((a>>3)&0x01)
    {digitalWrite(D7,HIGH);}
  else
    {digitalWrite(D7,LOW);} 

//Pulsa o Enable  
  digitalWrite(En,HIGH);
  delayMicroseconds(10);
  digitalWrite(En,LOW);
}

#include <HCSR04.h>
#include <LiquidCrystal.h>

byte triggerPin = 10;
byte echoPin = 9;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

//volatile float dado;
volatile float antigo = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Valor medido:");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

 	float distancia = distanceSensor.measureDistanceCm();
	
//Se valor medido mudou
	if(antigo != distancia)
	{
		lcd.print(distancia);
		lcd.println(" cm");
//Guarda valor medido
		antigo = distancia;
	}
}





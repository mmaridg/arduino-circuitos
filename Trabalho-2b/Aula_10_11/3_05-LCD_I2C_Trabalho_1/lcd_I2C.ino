#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#define I2C_ADDR 0x27 
int BACKLIGHT=3;
LiquidCrystal_I2C lcd(0x27,16,2);//,2,1,0,4,5,6,7); // Address and PFC8574 pins
unsigned long time, differ;
float ampe=0;
int MON=13;
int sense=A2;   // Sense INPUT

void setup() 
{
  pinMode(MON, OUTPUT);
  lcd.begin();
  //lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Valor Atual.");
}

void loop() 
{
  differ=millis()-time;
  if (differ >= 200) 
  {
    ampe=(map(analogRead(sense), 0,1024, 0,507))/100.0f;  // MAP, CALIB AND DECIMALS.
    if( ampe > 1) digitalWrite(MON,HIGH);
    else digitalWrite(MON,LOW);
    lcd.setCursor(4,1);
    lcd.print(ampe);
    lcd.print(" V.");
    time = millis();
  }
}

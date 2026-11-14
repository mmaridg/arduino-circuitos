#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int conta = 0;
int k = 1;
void setup() {
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(conta);                  // sets the servo position according to the scaled value
  delay(100);  
 conta = conta + k*10;
	if((conta > 170)&&(k==1))
		k = -1;
	if ((conta < 10)&&(k==-1))
		k = 1;                         // waits for the servo to get there
}
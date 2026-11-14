const int trigPin = 9;
const int echoPin = 10;
const int LED = 12;
int duracao = 0;
float distancia;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  duracao = 0;
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

//Gera pulso de 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracao = 0;

//Espera pulso de eco subir
  while(!digitalRead(echoPin))
{
}

//Espera pelo eco do pulso
//Lê o pino de eco a cada 100 microsegundos
//A variável duracão indica quantos
//módulos de 100 uaa
  while(digitalRead(echoPin))
  {
	duracao = duracao + 1;

//Espera 100 microsegundos
	delayMicroseconds(100);
  }

//A variável duracao indica quantos módulos
//de 100 microsegundos o eco levou para retornar
//O tempo corresponde à ida e volta.
//Calcula distância do obstáculo
//O som percorre 343 m/s

  distancia = (duracao*3.43)/2;

//Acende LED para distâncias maiores do que 200 cm
  if(distancia >= 200)
  {
	digitalWrite(LED, HIGH);
  }
  else
  {
	digitalWrite(LED, LOW);
  }

//Imprime distância calculada
  Serial.print("Distancia: ");
  Serial.println(distancia);

//Espera 1 milisegundo antes de fazer nova medida
  delay(1);
}
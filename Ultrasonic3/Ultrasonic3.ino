// Sensor 1
int TRIG1 = 25;
int ECO1 = 32;
int LED1 = 2;

// Sensor 2
int TRIG2 = 14;
int ECO2 = 13;
int LED2 = 17;

// Sensor 3
int TRIG3 = 16;
int ECO3 = 15;
int LED3 = 5;

int DURACION1, DISTANCIA1;
int DURACION2, DISTANCIA2;
int DURACION3, DISTANCIA3;

void setup() {
  pinMode(TRIG1, OUTPUT);
  pinMode(ECO1, INPUT);
  pinMode(LED1, OUTPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECO2, INPUT);
  pinMode(LED2, OUTPUT);

  pinMode(TRIG3, OUTPUT);
  pinMode(ECO3, INPUT);
  pinMode(LED3, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Sensor 1
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  DURACION1 = pulseIn(ECO1, HIGH);
  DISTANCIA1 = DURACION1 / 58.2;
  Serial.print("Distancia1: ");
  Serial.println(DISTANCIA1);


  // Sensor 2
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  DURACION2 = pulseIn(ECO2, HIGH);
  DISTANCIA2 = DURACION2 / 58.2;
  Serial.print("Distancia2: ");
  Serial.println(DISTANCIA2);
  
  // Sensor 3
  digitalWrite(TRIG3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3, LOW);
  DURACION3 = pulseIn(ECO3, HIGH);
  DISTANCIA3 = DURACION3 / 58.2;
  Serial.print("Distancia3: ");
  Serial.println(DISTANCIA3);

  // Encender LED 1 si la distancia es menor o igual a 70 cm
  if (DISTANCIA1 <= 70 && DISTANCIA1 >= 0) {
    Serial.println("1");
    digitalWrite(LED1, HIGH);
    delay(DISTANCIA1 * 10);
    digitalWrite(LED1, LOW);
  }

  // Encender LED 2 si la distancia es menor o igual a 70 cm
  if (DISTANCIA2 <= 70 && DISTANCIA2 >= 0) {
    Serial.println("2");
    digitalWrite(LED2, HIGH);
    delay(DISTANCIA2 * 10);
    digitalWrite(LED2, LOW);
  }

  // Encender LED 3 si la distancia es menor o igual a 70 cm
  if (DISTANCIA3 <= 70 && DISTANCIA3 >= 0) {
    Serial.println("3");
    digitalWrite(LED3, HIGH);
    delay(DISTANCIA3 * 10);
    digitalWrite(LED3, LOW);
  }

  delay(200);
}

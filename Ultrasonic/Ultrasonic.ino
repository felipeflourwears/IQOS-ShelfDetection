// Sensor 1
int TRIG1 = 32;
int ECO1 = 25;
int LED1 = 2;

// Sensor 2
int TRIG2 = 14;
int ECO2 = 13;
int LED2 = 17;

int DURACION1, DISTANCIA1;
int DURACION2, DISTANCIA2;

void setup() {
  pinMode(TRIG1, OUTPUT);
  pinMode(ECO1, INPUT);
  pinMode(LED1, OUTPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECO2, INPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Sensor 1
  digitalWrite(TRIG1, HIGH);
  delay(1);
  digitalWrite(TRIG1, LOW);
  DURACION1 = pulseIn(ECO1, HIGH);
  DISTANCIA1 = DURACION1 / 58.2;

  // Sensor 2
  digitalWrite(TRIG2, HIGH);
  delay(1);
  digitalWrite(TRIG2, LOW);
  DURACION2 = pulseIn(ECO2, HIGH);
  DISTANCIA2 = DURACION2 / 58.2;

  // Imprimir las distancias por comunicación serial
  //Serial.print("Distancia sensor 1 (cm): ");
  //Serial.println(DISTANCIA1);
  //Serial.print("Distancia sensor 2 (cm): ");
  //Serial.println(DISTANCIA2);

  // Encender LED 1 si la distancia es menor o igual a 20 cm
  if (DISTANCIA1 <= 70 && DISTANCIA1 >= 0) {
    Serial.println("1");
    digitalWrite(LED1, HIGH);
    delay(DISTANCIA1 * 10);
    digitalWrite(LED1, LOW);
  }

  // Encender LED 2 si la distancia es menor o igual a 20 cm
  if (DISTANCIA2 <= 70 && DISTANCIA2 >= 0) {
    Serial.println("2");
    digitalWrite(LED2, HIGH);
    delay(DISTANCIA2 * 10);
    digitalWrite(LED2, LOW);
  }

  delay(200);
}

#include <Ultrasonic.h>

#define TRIGGER_PIN 32
#define ECHO_PIN 25

#define TRIGGER_PIN2 14
#define ECHO_PIN2 13

#define LED_BUILTIN 2
#define LED_BUILTIN2 17

#define umbral_sensor1 50
#define umbral_sensor2 50
#define max_distance 250

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN2, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // Realizar lecturas y calcular promedios para ambos sensores

  float distanciaPromedio1 = obtenerDistanciaPromedio(TRIGGER_PIN, ECHO_PIN);
  float distanciaPromedio2 = obtenerDistanciaPromedio(TRIGGER_PIN2, ECHO_PIN2);

  // Imprimir resultados por comunicación serial
  Serial.print("Distancia promedio sensor 1 (cm): ");
  Serial.println(distanciaPromedio1);
  Serial.print("Distancia promedio sensor 2 (cm): ");
  Serial.println(distanciaPromedio2);

  if (distanciaPromedio1 < umbral_sensor1 && distanciaPromedio1 < max_distance && distanciaPromedio1 > 0) {
      digitalWrite(LED_BUILTIN, HIGH); // Enciende el primer LED si la distancia es menor que el umbral
      Serial.println("1");
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (distanciaPromedio2 < umbral_sensor2 && distanciaPromedio2 < max_distance && distanciaPromedio2 > 0) {
      digitalWrite(LED_BUILTIN2, HIGH); // Enciende el primer LED si la distancia es menor que el umbral
      Serial.println("2");
  }else{
    digitalWrite(LED_BUILTIN2, LOW);

  }
}

float obtenerDistanciaPromedio(int triggerPin, int echoPin) {
  float distanciaPromedio = 0;
  Ultrasonic ultrasonic(triggerPin, echoPin);
  long microsec = ultrasonic.timing();
  float cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
   
  return cmMsec;
}

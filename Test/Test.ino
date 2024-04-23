#include <Ultrasonic.h>

#define TRIGGER_PIN 32
#define ECHO_PIN 25

#define TRIGGER_PIN2 14
#define ECHO_PIN2 13

#define LED_BUILTIN 2
#define LED_BUILTIN2 17

#define umbral_sensor1 23
#define umbral_sensor2 35
#define max_distance 250

// Variables globales para el filtro de Kalman
float P1 = 1, P2 = 1; // Varianza de la estimación de error
float Q = 0.01; // Varianza del proceso (ruido del sistema)
float R = 5; // Varianza de la medición (ruido del sensor)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Realizar lecturas filtradas para ambos sensores
  float distanciaFiltrada1 = obtenerDistanciaFiltrada(TRIGGER_PIN, ECHO_PIN, P1);
  float distanciaFiltrada2 = obtenerDistanciaFiltrada(TRIGGER_PIN2, ECHO_PIN2, P2);

  // Imprimir resultados por comunicación serial
  Serial.print("Distancia filtrada sensor 1 (cm): ");
  Serial.println(distanciaFiltrada1);
  Serial.print("Distancia filtrada sensor 2 (cm): ");
  Serial.println(distanciaFiltrada2);

  if (distanciaFiltrada1 < umbral_sensor1 && distanciaFiltrada1 < max_distance && distanciaFiltrada1 > 0) {
      digitalWrite(LED_BUILTIN, HIGH); // Enciende el primer LED si la distancia es menor que el umbral
      Serial.println("1");
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (distanciaFiltrada2 < umbral_sensor2 && distanciaFiltrada2 < max_distance && distanciaFiltrada2 > 0) {
      digitalWrite(LED_BUILTIN2, HIGH); // Enciende el segundo LED si la distancia es menor que el umbral
      Serial.println("2");
  } else {
    digitalWrite(LED_BUILTIN2, LOW);
  }

  delay(100); // Pequeño retraso entre las iteraciones para reducir la carga en el microcontrolador
}

float obtenerDistanciaFiltrada(int triggerPin, int echoPin, float &P) {
  Ultrasonic ultrasonic(triggerPin, echoPin);
  long microsec = ultrasonic.timing();
  float medida = ultrasonic.convert(microsec, Ultrasonic::CM);

  // Predicción del estado
  float K = P / (P + R); // Ganancia de Kalman
  float estadoPredicho = medida; // Estimación del estado predicho

  // Actualización del estado
  P = (1 - K) * P + Q; // Actualización de la varianza de la estimación del error
  return estadoPredicho;
}

#define ir 34
#define ir2 33
#define LED_BUILTIN 2
#define LED_BUILTIN2 17
#define umbral 50

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float voltage = analogRead(ir) * (3.3 / 4095.0); // Lee el voltaje del primer sensor IR
  float distance = 29.988 * pow(voltage, -1.173); // Calcula la distancia usando la ecuación

  float voltage2 = analogRead(ir2) * (3.3 / 4095.0); // Lee el voltaje del segundo sensor IR
  float distance2 = 29.988 * pow(voltage2, -1.173); // Calcula la distancia usando la ecuación

  // Verificar si la distancia medida por el primer sensor es finita y menor o igual a 300
  if (isfinite(distance) && distance <= 300) {
    if (distance < umbral) {
      digitalWrite(LED_BUILTIN, HIGH); // Enciende el primer LED si la distancia es menor que el umbral
      Serial.println("1");
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  // Verificar si la distancia medida por el segundo sensor es finita y menor o igual a 300
  if (isfinite(distance2) && distance2 <= 300) {
    if (distance2 < umbral) {
      digitalWrite(LED_BUILTIN2, HIGH); // Enciende el segundo LED si la distancia es menor que el umbral
      Serial.println("2");
    } else {
      digitalWrite(LED_BUILTIN2, LOW);
    }
  }

  delay(200); // Espera un poco antes de la siguiente lectura
}
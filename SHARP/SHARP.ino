#define ir 34
#define LED_BUILTIN 2
#define umbral 120

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  float voltage = analogRead(ir) * (3.3 / 4095.0); // Lee el voltaje del sensor IR
  float distance = 29.988 * pow(voltage, -1.173); // Calcula la distancia usando la ecuación

  // Verificar si la distancia es finita y menor o igual a 100
  if (isfinite(distance) && distance <= 300) {
    //Serial.print("Mean distance: ");
    //Serial.println(distance);
    
    if (distance > umbral) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("SHARP1: 0");
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("SHARP1: 1");
    }
  }

  delay(200); // Espera un poco antes de la siguiente lectura
}

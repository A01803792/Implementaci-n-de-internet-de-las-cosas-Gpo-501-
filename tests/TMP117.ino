#include <Wire.h>
#include <Adafruit_TMP117.h>
#include <Adafruit_Sensor.h>


Adafruit_TMP117 tmp117;

const int PIN_SDA = 4;
const int PIN_SCL = 3;


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(50000);

  Serial.println("Iniciando sensor TH40117 (TMP117)...");
  if (!tmp117.begin()) {
    Serial.println("¡No se pudo encontrar el sensor! Revisa que los cables no estén flojos.");
    while (1) {
      delay(10);
    }
  }

  Serial.println("¡Sensor conectado y listo!");
}


void loop() {
  sensors_event_t temp;
  tmp117.getEvent(&temp);

  Serial.print("Temperatura actual: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  delay(1000);
}

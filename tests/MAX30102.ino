#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"


MAX30105 particleSensor;


const int PIN_SDA = 4;
const int PIN_SCL = 3;


void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(50000);

  Serial.println("Iniciando MAX30102...");
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("¡No se encontró el MAX30102! Revisa las conexiones.");
    while (1) delay(10);
  }

  Serial.println("¡MAX30102 conectado con éxito!");
 
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}


void loop() {
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    Serial.print("¡Latido detectado! Valor IR: ");
    Serial.println(irValue);
  }

  if (irValue < 50000) {
    Serial.println("Coloca tu dedo suavemente sobre el sensor...");
  }
 
  delay(20);
}

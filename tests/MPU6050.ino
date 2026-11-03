#include <Wire.h>


const int MPU_ADDR = 0x68;
const int PIN_SDA = 4;
const int PIN_SCL = 5;


void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(50000);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  byte error = Wire.endTransmission();

  if (error != 0) {
    Serial.println("¡El MPU6050 sigue sin responder a los registros directos!");
    Serial.println("Revisa si tu módulo responde cambiando MPU_ADDR a 0x69.");
    while (1) delay(10);
  }

  Serial.println("¡MPU6050 despertado correctamente por registros directos!");
}


void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  if (Wire.available() == 14) {
    int16_t AcX = Wire.read() << 8 | Wire.read();
    int16_t AcY = Wire.read() << 8 | Wire.read();
    int16_t AcZ = Wire.read() << 8 | Wire.read();
    int16_t Tmp = Wire.read() << 8 | Wire.read();
    int16_t GyX = Wire.read() << 8 | Wire.read();
    int16_t GyY = Wire.read() << 8 | Wire.read();
    int16_t GyZ = Wire.read() << 8 | Wire.read();

    Serial.print("AcX: "); Serial.print(AcX);
    Serial.print(" | AcY: "); Serial.print(AcY);
    Serial.print(" | AcZ: "); Serial.println(AcZ);
  } else {
    Serial.println("Error al leer los datos del sensor.");
  }

  delay(500);
}

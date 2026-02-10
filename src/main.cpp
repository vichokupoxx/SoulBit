#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("ESP32-C3 viva 🔥");
}

void loop() {
  Serial.println("tick");
  delay(1000);
}

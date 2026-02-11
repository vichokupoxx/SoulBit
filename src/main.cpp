#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(
    U8G2_R0,
    U8X8_PIN_NONE
);

void setup() {

    Serial.begin(115200);

    // Esperar a que el USB esté listo (importante en C3)
    unsigned long start = millis();
    while (!Serial && millis() - start < 5000) {
        delay(10);
    }

    Serial.println("Iniciando OLED...");

    Wire.begin(5, 6);

    u8g2.begin();
    u8g2.setI2CAddress(0x3C * 2);

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x8_tf);
    u8g2.drawStr(0, 10, "OLED OK");
    u8g2.sendBuffer();

    Serial.println("OLED iniciado correctamente");
}

void loop() {

    static unsigned long last = 0;

    if (millis() - last > 1000) {
        last = millis();
        Serial.println("Latido");
    }
}

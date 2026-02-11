#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2( // Crea una instancia de la clase U8G2_SSD1306_72X40_ER_F_HW_I2C, que es una clase específica para manejar un display OLED SSD1306 de 72x40 píxeles, ER (tipo memoria display), F(full buffer) utiliza la comunicación I2C por hardware
    U8G2_R0, //maneja rotacion de pantalla R0 sin rotacion, R1 rotacion 90 grados, R2 rotacion 180 grados, R3 rotacion 270 grados
    U8X8_PIN_NONE  //No se usa un pin de reset para este display, por lo que se establece en U8X8_PIN_NONE
);

void setup() { // La función setup() se ejecuta una vez al inicio del programa, es el lugar ideal para inicializar componentes y configurar el entorno

    Serial.begin(115200); // Inicia la comunicación serial a 115200 baudios, lo que permite enviar mensajes al monitor serial para depuración y monitoreo del programa

    // Esperar a que el USB esté listo (importante en C3)
    unsigned long start = millis(); // Guardar el tiempo de inicio para implementar un timeout, millis() devuelve el número de milisegundos desde que el microcontrolador arranco
    while (!Serial && millis() - start < 5000) { // Esperar hasta que Serial esté listo o hasta que hayan pasado 5 segundos
        delay(10); // Pequeña pausa para evitar un bucle de espera demasiado rápido, delay() detiene la ejecución del programa durante el número especificado de milisegundos
    }

    Serial.println("Iniciando OLED...");

    Wire.begin(5, 6);

    u8g2.begin(); // Inicializa el display OLED, esto configura la comunicación I2C y prepara el display para recibir comandos y datos
    u8g2.setI2CAddress(0x3C * 2); // Establece la dirección I2C del display OLED, 0x3C es la dirección común para estos displays, pero se multiplica por 2 porque el controlador de pantalla espera la dirección en formato de byte completo (con el bit de lectura/escritura incluido)

    u8g2.clearBuffer(); // Limpia el buffer de dibujo del display, esto es necesario antes de dibujar cualquier cosa en la pantalla para asegurarse de que no haya datos residuales
    u8g2.setFont(u8g2_font_5x8_tf); // Establece la fuente que se utilizará para dibujar texto en el display
    u8g2.drawStr(0, 10, "OLED OK"); // Dibuja la cadena de texto "OLED OK" en la posición (0, 10) del display, donde 0 es la coordenada x (horizontal) y 10 es la coordenada y (vertical)
    u8g2.sendBuffer(); // Envía el contenido del buffer de dibujo al display, esto actualiza la pantalla con lo que se ha dibujado en el buffer

    Serial.println("OLED iniciado correctamente"); // Imprime un mensaje en el monitor serial indicando que el OLED se ha iniciado correctamente, esto es útil para confirmar que la inicialización del display fue exitosa
}

void loop() { // La función loop() se ejecuta repetidamente después de setup(), es el lugar ideal para colocar el código que debe ejecutarse continuamente

    static unsigned long last = 0; // Declara una variable estática llamada last para almacenar el tiempo del último latido, static hace que la variable conserve su valor entre llamadas a la función loop()

    if (millis() - last > 1000) { // Verifica si ha pasado más de 1000 milisegundos (1 segundo) desde el último latido, millis() devuelve el tiempo actual en milisegundos, y al restar last obtenemos el tiempo transcurrido desde el último latido
        last = millis(); // Actualiza la variable last con el tiempo actual para marcar el momento del último latido
        Serial.println("Latido"); // Imprime el mensaje "Latido" en el monitor serial cada segundo, esto sirve como una señal de que el programa está corriendo correctamente y no se ha bloqueado
    }
}

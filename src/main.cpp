#include <SoftwareSerial.h>

#ifdef ESP8266
    #define RX_PIN D4  // ESP8266 WeMos D1 Mini: Use D4 for RX
    #define TX_PIN D5  // ESP8266 WeMos D1 Mini: Use D5 for TX
#else
    #define RX_PIN 4  // Arduino Nano: Use Pin 4 for RX
    #define TX_PIN 5  // Arduino Nano: Use Pin 5 for TX
#endif

#ifndef ESP8266
    SoftwareSerial softSerial(RX_PIN, TX_PIN);
#endif

void setup() {
    Serial.begin(9600); // USB Serial for PC communication

    #ifdef ESP8266
        Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Use Serial1 on ESP8266
    #else
        softSerial.begin(9600); // Use SoftwareSerial on Arduino Nano
    #endif
}

void loop() {
    // Forward data from USB to secondary serial
    if (Serial.available()) {
        char c = Serial.read();
        #ifdef ESP8266
            Serial1.write(c);
        #else
            softSerial.write(c);
        #endif
    }

    // Forward data from secondary serial to USB
    #ifdef ESP8266
        if (Serial1.available()) {
            char c = Serial1.read();
            Serial.write(c);
        }
    #else
        if (softSerial.available()) {
            char c = softSerial.read();
            Serial.write(c);
        }
    #endif
}

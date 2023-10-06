#include <SoftwareSerial.h>

SoftwareSerial monitorSerial(2, 3);  // RX, TX

void setup() {
    Serial.begin(9600);  // Set the baud rate to match the Python program
    monitorSerial.begin(9600);  // Monitoring
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        // Process the command here
        if (command == 'A') {
            Serial.println("not B");
            
        } else if (command == 'B') {
            Serial.println("not A");

        }
        // Add more commands as needed
    }
}

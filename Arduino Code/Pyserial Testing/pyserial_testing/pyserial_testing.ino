#include <SoftwareSerial.h>

SoftwareSerial monitorSerial(2, 3);  // RX, TX

void setup() {
    Serial.begin(9600);  // Set the baud rate to match the Python program
    monitorSerial.begin(9600);  // Monitoring
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        float command = Serial.read();
        if (command>10){
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(10000);                       // wait for a second
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);                       // wait for a second   
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(10000);                       // wait for a second
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);                       // wait for a second   
        }
    }
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Read the distance value from Python
    if (Serial.available() > 0) {
        int distanceCM = Serial.parseInt();
        if(distanceCM>30){
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(3000);                       // wait for a second
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);                       // wait for a second
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(3000);                       // wait for a second
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);                       // wait for a second
        }
    }
}

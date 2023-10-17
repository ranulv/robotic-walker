int IN3 = 9;
int IN4 = 10;
int ENB = 11;
 
int ENA = 5;
int IN1 = 6;
int IN2 = 7;
 
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Set all motors to OFF
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 
void loop() {
  // Set the speed of the motor (PWM signals) from 0 to 255
  analogWrite(ENA, 170);
  analogWrite(ENB, 170);
 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, LOW);
  
  // Set the direction and turn ON
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
 
  
  
}
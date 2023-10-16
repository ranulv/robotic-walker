int pot_val;
int led_val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  pot_val = analogRead(A0);
  Serial.println(pot_val);
  led_val = map(pot_val,0,1023,0,255);
  analogWrite(9,led_val);
  delay(50);

}

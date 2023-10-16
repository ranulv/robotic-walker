// Motor A connections
int m1pwm = 9; 
int m1en = 24;
int m1inA = 26;
int m1inB = 28;

int m2pwm = 8; 
int m2en = 48;
int m2inA = 50;
int m2inB = 52;

int channel1;
int channel2;

void setup() {
  // Set all the motor control pins to outputs

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

	pinMode(m1pwm, OUTPUT);
	pinMode(m1inA, OUTPUT);
	pinMode(m1inB, OUTPUT);
  pinMode(m1en,OUTPUT);

  pinMode(m1pwm, OUTPUT);
	pinMode(m1inA, OUTPUT);
	pinMode(m1inB, OUTPUT);
  pinMode(m1en,OUTPUT);

  pinMode(36,INPUT);
  pinMode(38,INPUT);

  	// Turn off motors - Initial state
	digitalWrite(m1inA, LOW);
	digitalWrite(m1inB, LOW);
  digitalWrite(m1pwm,LOW);
  digitalWrite(m1en,LOW);

  digitalWrite(m2inA, LOW);
	digitalWrite(m2inB, LOW);
  digitalWrite(m2pwm,LOW);
  digitalWrite(m2en,LOW);

}

void loop() {
  digitalWrite(m1en,HIGH);
  analogWrite(m1pwm,200);
  digitalWrite(m1inA,HIGH);
  digitalWrite(m1inB,LOW);

  digitalWrite(m2en,HIGH);
  analogWrite(m2pwm,200);
  digitalWrite(m2inA,HIGH);
  digitalWrite(m2inB,LOW);

  channel1 = Serial.read();
  channel2 = Serial.read();
  
  Serial.println(channel1 + "  " + channel2);

  delay(50);



}

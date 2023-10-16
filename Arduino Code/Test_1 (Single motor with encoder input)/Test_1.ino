// Motor encoder output pulse per rotation (change as required)
#define ENC_COUNT_REV 1680
 
// Encoder output to Arduino Interrupt pin
#define ENC_IN 3

// Analog pin for potentiometer
int speedcontrol = 0;

// Pulse count from encoder
volatile long encoderValue = 0;
 
// One-second interval for measurements
int interval = 1000;
 
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
int rpm = 0;

// Variable for PWM motor speed output
int motorPwm = 0;

// Motor A connections
int pwm = 9; 
int enable = 5;
int in1 = 6;
int in2 = 7;



void setup() {
  // Set all the motor control pins to outputs

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  // Set encoder as input with internal pullup  
  pinMode(ENC_IN, INPUT_PULLUP);

  // Attach interrupt 
  attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);

	pinMode(pwm, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
  pinMode(enable,OUTPUT);



  	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
  digitalWrite(pwm,LOW);
  digitalWrite(enable,LOW);

  // Setup initial values for timer
  previousMillis = millis();

}

void loop() {

  // Control motor with potentiometer
    motorPwm = map(analogRead(speedcontrol), 0, 1023, 0, 255);

  digitalWrite(enable,HIGH);
  analogWrite(pwm,motorPwm);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);

  // Update RPM value every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
 
 
    // Calculate RPM
    rpm = (float)(encoderValue * 60 / ENC_COUNT_REV);

    // Only update display when there is a reading
    if (motorPwm > 0 || rpm > 0) {
      Serial.print("PWM VALUE: ");
      Serial.print(motorPwm);
      Serial.print('\t');
      Serial.print(" PULSES: ");
      Serial.print(encoderValue);
      Serial.print('\t');
      Serial.print(" SPEED: ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }
    
    encoderValue = 0;
  }

}

void updateEncoder()
{
  // Increment value for each pulse from encoder
  encoderValue++;
}

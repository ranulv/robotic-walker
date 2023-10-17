#include <ros.h>
#include <std_msgs/Int32.h>

int encoderPinLeft = 2;
int encoderPinRight = 3;

int IN3 = 9;
int IN4 = 10;
int ENB = 11;
 
int ENA = 5;
int IN1 = 6;
int IN2 = 7;

volatile unsigned long totalPulseLeft = 0;
volatile unsigned long totalPulseRight = 0;

int motorVelocityLeft = 0;
int motorVelocityRight = 0;

ros::NodeHandle nh;

void callBackFunctionMotorLeft(const std_msgs::Int32 &motorvelocityLeftROS){
  motorVelocityLeft=motorvelocityLeftROS.data;
}
void callBackFunctionMotorRight(const std_msgs::Int32 &motorvelocityRightROS){
  motorVelocityRight=motorvelocityRightROS.data;
}

std_msgs::Int32 leftEncoderROS;
ros::Publisher leftEncoderROSPublisher("left_encoder_pulses", &leftEncoderROS);

std_msgs::Int32 RightEncoderROS;
ros::Publisher RightEncoderROSPublisher("Right_encoder_pulses", &RightEncoderROS);

ros::Subscriber<std_msgs::Int32> leftMotorROSSubscriber('left_motor_velocity',&callBackFunctionMotorLeft);
ros::Subscriber<std_msgs::Int32> rightMotorROSSubscriber('right_motor_velocity',&callBackFunctionMotorRight);

void setup() {
  pinMode(encoderPinLeft,INPUT);
  pinMode(encoderPinRight,INPUT);

  attachInterrupt(digitalPintoInterrupt(encoderPinLeft),interruptFunctionLeft,RISING);
  attachInterrupt(digitalPintoInterrupt(encoderPinRight),interruptFunctionRight,RISING);

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

  nh.getHardware() -> setBaud(9600);
  nh.initNode();

  nh.advertise(leftEncoderROSPublisher);
  nh.advertise(rightEncoderROSPublisher);

  nh.subsribe(leftEncoderROSSubscriber);
  nh.subsribe(rightEncoderROSSubscriber);
}
 
void loop() {
  nh.spinOnce();
  // Set the speed of the motor (PWM signals) from 0 to 255
  analogWrite(ENA, motorVelocityLeft);
  analogWrite(ENB, motorVelocityRight);
 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  
  // Set the direction and turn ON
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  leftEncoderROS.data = totalPulseLeft;
  rightEncoderROS.data = totalPulseRight;
  leftEncoderROSPublisher.publish(&leftEncoderROS);
  rightEncoderROSPublisher.publish(&rightEncoderROS);

  delay(5);
}

void InterruptFunctionLeft(){
  totalPulseLeft = totalPulseLeft + 1;
}

void InterruptFunctionRight(){
  totalPulseRight = totalPulseRight + 1;
}
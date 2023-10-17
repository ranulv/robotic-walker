#include <ros.h> // include the ROS library
#include <std_msgs/Int32.h> // include the standard ROS message type for integers

// define the pins used for the encoders and motor drivers
int encoderPinLeft = 2;
int encoderPinRight = 3;

int IN3 = 9;
int IN4 = 10;
int ENB = 11;
 
int ENA = 5;
int IN1 = 6;
int IN2 = 7;

// define variables to keep track of the encoder pulse counts and motor velocities
volatile unsigned long totalPulseLeft = 0;
volatile unsigned long totalPulseRight = 0;

int motorVelocityLeft = 0;
int motorVelocityRight = 0;

// create a ROS node handle
ros::NodeHandle nh;

// define callback functions for the motor velocity ROS messages
void callBackFunctionMotorLeft(const std_msgs::Int32 &motorvelocityLeftROS){
  motorVelocityLeft=motorvelocityLeftROS.data;
}
void callBackFunctionMotorRight(const std_msgs::Int32 &motorvelocityRightROS){
  motorVelocityRight=motorvelocityRightROS.data;
}

// create ROS message objects for the encoder pulse counts
std_msgs::Int32 leftEncoderROS;
ros::Publisher leftEncoderROSPublisher("left_encoder_pulses", &leftEncoderROS);

std_msgs::Int32 rightEncoderROS;
ros::Publisher rightEncoderROSPublisher("right_encoder_pulses", &rightEncoderROS);

// create ROS subscribers for the motor velocity messages
ros::Subscriber<std_msgs::Int32> leftMotorROSSubscriber("left_motor_velocity",&callBackFunctionMotorLeft);
ros::Subscriber<std_msgs::Int32> rightMotorROSSubscriber("right_motor_velocity",&callBackFunctionMotorRight);

void setup() {
  // set the encoder pins as inputs
  pinMode(encoderPinLeft,INPUT);
  pinMode(encoderPinRight,INPUT);

  // attach interrupt functions to the encoder pins
  attachInterrupt(digitalPinToInterrupt(encoderPinLeft),InterruptFunctionLeft,RISING);
  attachInterrupt(digitalPinToInterrupt(encoderPinRight), InterruptFunctionRight,RISING);

  // set the motor driver pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // set all motors to OFF
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // initialize the ROS node and set the baud rate
  nh.getHardware()->setBaud(9600);
  nh.initNode();

  // advertise the encoder pulse count publishers
  nh.advertise(leftEncoderROSPublisher);
  nh.advertise(rightEncoderROSPublisher);

  // subscribe to the motor velocity messages
  nh.subscribe(leftMotorROSSubscriber);
  nh.subscribe(rightMotorROSSubscriber);
}
 
void loop() {
  // update the ROS node
  nh.spinOnce();

  // set the motor speeds based on the received velocity commands
  analogWrite(ENA, motorVelocityLeft);
  analogWrite(ENB, motorVelocityRight);
 
  // set the motor directions to forward
  digitalWrite(IN1,LOW);
  digitalWrite(IN2, HIGH);
  
  // turn the motors on
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // publish the encoder pulse counts as ROS messages
  leftEncoderROS.data = totalPulseLeft;
  rightEncoderROS.data = totalPulseRight;
  leftEncoderROSPublisher.publish(&leftEncoderROS);
  rightEncoderROSPublisher.publish(&rightEncoderROS);

  // delay to prevent overloading the system
  delay(5);
}

// interrupt functions for the encoder pins
void InterruptFunctionLeft(){
  totalPulseLeft = totalPulseLeft + 1;
}

void InterruptFunctionRight(){
  totalPulseRight = totalPulseRight + 1;
}
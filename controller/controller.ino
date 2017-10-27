#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <TrollBot.h>

TrollBot Master(00, 050);
TrollBot Motor(01, 050);

//Slave pins
int motorPins[2] = {5, 6};

int left_horisontal_neutral;
int left_vertical_neutral;

const int BELT_RIGHT_FORWARD = 2;
const int BELT_RIGHT_BACKWARD = 1;
const int BELT_RIGHT_PWM = 3;
const int BELT_LEFT_FORWARD = 5;
const int BELT_LEFT_BACKWARD = 4;
const int BELT_LEFT_PWM = 6;

void setup() {
  Serial.begin(9600);
  left_horisontal_neutral = analogRead(A1);
  left_vertical_neutral = analogRead(A2);

  Master.setup();
  //Slave setup
  Motor.pinMode(motorPins[0], OUTPUT);
  Motor.pinMode(motorPins[1], OUTPUT);

  Motor.pinMode(BELT_RIGHT_FORWARD, OUTPUT);
  Motor.pinMode(BELT_RIGHT_BACKWARD, OUTPUT);
  Motor.pinMode(BELT_RIGHT_PWM, OUTPUT);
  Motor.pinMode(BELT_LEFT_FORWARD, OUTPUT);
  Motor.pinMode(BELT_LEFT_BACKWARD, OUTPUT);
  Motor.pinMode(BELT_LEFT_PWM, OUTPUT);
  Motor.pinMode(7, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  Master.masterLoop();

  Motor.digitalWrite(7, HIGH);
  digitalWrite(7, HIGH);

  int left_horisontal = analogRead(A1) - left_horisontal_neutral;
  int left_vertical = analogRead(A2) - left_vertical_neutral;

  int left_belt = min(abs(-left_vertical + left_horisontal), 510)/2;
  int right_belt = min(abs(-left_vertical - left_horisontal), 510)/2;

  Serial.print(left_belt);
  Serial.print(' ');
  Serial.println(right_belt);

  Motor.analogWrite(BELT_RIGHT_PWM, right_belt);
  Motor.digitalWrite(BELT_RIGHT_FORWARD, HIGH);
  Motor.digitalWrite(BELT_RIGHT_BACKWARD, LOW);
  Motor.analogWrite(BELT_LEFT_PWM, left_belt);
  Motor.digitalWrite(BELT_LEFT_FORWARD, HIGH);
  Motor.digitalWrite(BELT_LEFT_BACKWARD, LOW);
}

//Define custom functions for motor control
void slaveMotor(bool dir) {
  if (dir) {
    // Control pins on the slave named "Motor"
    Motor.digitalWrite(motorPins[0], HIGH);
    Motor.digitalWrite(motorPins[1], LOW);
  } else {
    Motor.digitalWrite(motorPins[0], LOW);
    Motor.digitalWrite(motorPins[1], HIGH);
  }
}

void slaveMotorOff() {
  Motor.digitalWrite(motorPins[0], LOW);
  Motor.digitalWrite(motorPins[1], LOW);
}

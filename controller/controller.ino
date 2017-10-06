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

void setup() {
  Serial.begin(9600);
  left_horisontal_neutral = analogRead(A1);
  left_vertical_neutral = analogRead(A2);

   Master.setup();
   //Slave setup
   Motor.pinMode(motorPins[0], OUTPUT);
   Motor.pinMode(motorPins[1], OUTPUT);  
}

void loop() {
  //Master.masterLoop();
  Serial.println("A");
  int left_horisontal = analogRead(A1) - left_horisontal_neutral;
  int left_vertical = analogRead(A2) - left_vertical_neutral;
  
  int left_belt = -left_vertical + left_horisontal;
  int right_belt = -left_vertical - left_horisontal;

 if (left_belt < -40) {
    //slaveMotor(1);
    Serial.println("Backwards");
  } else if (left_belt > 40) {
    //slaveMotor(0);
    Serial.println("Forwards");
  } else {
    //slaveMotorOff();
    Serial.println("Standing still");
  }
  
  Serial.print(left_belt);
  Serial.print(' ');
  Serial.println(right_belt);
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


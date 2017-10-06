#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <TrollBot.h>

TrollBot Master(00, 110);
TrollBot Motor(01, 110);

//Slave pins
int motorPins[2] = {5, 6};

//Master pins
int buttonPins[2] = {2, 3};

void setup() {
   Master.setup();
   Serial.begin(9600);

   //Slave setup
   Motor.pinMode(motorPins[0], OUTPUT);
   Motor.pinMode(motorPins[1], OUTPUT);

   //Master pin definitions
   pinMode(buttonPins[0], INPUT);
   pinMode(buttonPins[1], INPUT);
}

void loop() {
  Master.masterLoop();
  //Update the button state in the beginning of the loop
  bool button1 = digitalRead(buttonPins[0]);
  bool button2 = digitalRead(buttonPins[1]);

  if (button1) {
    slaveMotor(1);
    Serial.println("Backwards");
  } else if (button2) {
    slaveMotor(0);
    Serial.println("Forwards");
  } else {
    slaveMotorOff();
    Serial.println("Standing still");
  }
}
//Define custom functions for motor control
void slaveMotor(bool dir) {
  if (dir) {
    // Control pins on the slave named "Motor"
    Motor.digitalWrite(motorPins[0], HIGH);
    Motor.digitalWrite(motorPins[1], LOW);
  } else {
    Motor.digitalWrite(motorPins[1], HIGH);
    Motor.digitalWrite(motorPins[0], LOW);
  }
}
void slaveMotorOff() {
  Motor.digitalWrite(motorPins[0], LOW);
  Motor.digitalWrite(motorPins[1], LOW);
}


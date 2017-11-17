#include"TrollBot.h"

TrollBot Motor(01,050);     // Initiate this node with address 01 and channel 100
int timeout;
unsigned long lastReceivedTime;
const int BELT_RIGHT_FORWARD = 2;
const int BELT_RIGHT_BACKWARD = 1;
const int BELT_RIGHT_PWM = 3;
const int BELT_LEFT_FORWARD = 5;
const int BELT_LEFT_BACKWARD = 4;
const int BELT_LEFT_PWM = 6;

void setup() {
  Motor.setup();            // Run the setup functions for this node
  timeout = 500;
}

bool isTimeout(bool networkAvailable) {
  if(networkAvailable) {
    lastReceivedTime = millis();
    return false;
  }
  else if(millis() - lastReceivedTime > timeout) {
    return true;
  }
  return false;
}

void stopMotor() {
    Motor.digitalWrite(BELT_RIGHT_FORWARD, LOW);
    Motor.digitalWrite(BELT_RIGHT_BACKWARD, LOW);
    Motor.digitalWrite(BELT_LEFT_FORWARD, LOW);
    Motor.digitalWrite(BELT_LEFT_BACKWARD, LOW);
}

void loop() {
  if(isTimeout( Loop() )) {
    stopMotor();
  }
}


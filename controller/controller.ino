#include <TrollBot.h>

TrollBot Master(00, 050);
TrollBot Motor(01, 050);

//Slave pins

int stickLeftNeutral;
int stickRightNeutral;
int stickLeftAbsMax;
int stickRightAbsMax;


const int BELT_RIGHT_FORWARD = 2;
const int BELT_RIGHT_BACKWARD = 1;
const int BELT_RIGHT_PWM = 3;
const int BELT_LEFT_FORWARD = 5;
const int BELT_LEFT_BACKWARD = 4;
const int BELT_LEFT_PWM = 6;

void setup() {
  Serial.begin(9600);
  stickLeftNeutral = analogRead(A2);
  stickRightNeutral = analogRead(A5);
  stickLeftAbsMax = min(stickLeftNeutral, 1024-stickLeftNeutral);
  stickRightAbsMax = min(stickRightNeutral, 1024-stickRightNeutral);

  Serial.print(stickLeftAbsMax);
  Serial.print(' ');
  Serial.println(stickRightAbsMax);

  pinMode(statusPin, OUTPUT);

  Master.setup();
  Motor.pinMode(BELT_RIGHT_FORWARD, OUTPUT);
  Motor.pinMode(BELT_RIGHT_BACKWARD, OUTPUT);
  Motor.pinMode(BELT_RIGHT_PWM, OUTPUT);
  Motor.pinMode(BELT_LEFT_FORWARD, OUTPUT);
  Motor.pinMode(BELT_LEFT_BACKWARD, OUTPUT);
  Motor.pinMode(BELT_LEFT_PWM, OUTPUT);
  Motor.pinMode(statusPin, OUTPUT);

}

void loop() {
  Master.masterLoop();

  Motor.digitalWrite(statusPin, HIGH);
  digitalWrite(statusPin, HIGH);

  int stickLeft = analogRead(A2) - stickLeftNeutral;
  int stickRight = analogRead(A5) - stickRightNeutral;

  Serial.print(stickLeft);
  Serial.print(' ');
  Serial.println(stickRight);

  int leftBelt = map(constrain(abs(stickLeft), 40, stickLeftAbsMax), 40, stickLeftAbsMax, 0, 255);
  int rightBelt = map(constrain(abs(stickRight), 40, stickRightAbsMax), 40, stickRightAbsMax, 0, 255);
  
  Serial.print(leftBelt);
  Serial.print(' ');
  Serial.println(rightBelt);

  if (stickLeft > 40) {
    Motor.digitalWrite(BELT_LEFT_FORWARD, HIGH);
    Motor.digitalWrite(BELT_LEFT_BACKWARD, LOW);
  }
  else if (stickLeft < -40) {
    Motor.digitalWrite(BELT_LEFT_FORWARD, LOW);
    Motor.digitalWrite(BELT_LEFT_BACKWARD, HIGH);
  } else {
    Motor.digitalWrite(BELT_LEFT_FORWARD, LOW);
    Motor.digitalWrite(BELT_LEFT_BACKWARD, LOW);
  }
  
  if (stickRight > 40) {
    Motor.digitalWrite(BELT_RIGHT_FORWARD, HIGH);
    Motor.digitalWrite(BELT_RIGHT_BACKWARD, LOW);
  } else if (stickRight < -40) {
    Motor.digitalWrite(BELT_RIGHT_FORWARD, LOW);
    Motor.digitalWrite(BELT_RIGHT_BACKWARD, HIGH);
  } else {
    Motor.digitalWrite(BELT_RIGHT_FORWARD, LOW);
    Motor.digitalWrite(BELT_RIGHT_BACKWARD, LOW);
  }

  Motor.analogWrite(BELT_RIGHT_PWM, rightBelt);
  Motor.analogWrite(BELT_LEFT_PWM, leftBelt);
}

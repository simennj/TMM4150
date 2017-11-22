#include <TrollBot.h>

TrollBot Master(00, 050);
TrollBot Motor(01, 050);

//Slave pins
const int STATUS_PIN = 7;
const int SERVO_PIN = 9;

int stickLeftNeutral;
int stickRightNeutral;
int stickLeftAbsMax;
int stickRightAbsMax;

const int BUTTON_LEFT_PIN = 3;
const int BUTTON_RIGHT_PIN = 2;
int servoAngle = 0;
int statusValue;


const int BELT_RIGHT_FORWARD = 2;
const int BELT_RIGHT_BACKWARD = 11;
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

  pinMode(BUTTON_LEFT_PIN, INPUT);
  pinMode(BUTTON_RIGHT_PIN, INPUT);
  digitalWrite(BUTTON_LEFT_PIN, HIGH);
  digitalWrite(BUTTON_RIGHT_PIN, HIGH);

  Serial.print(stickLeftAbsMax);
  Serial.print(' ');
  Serial.println(stickRightAbsMax);

  pinMode(STATUS_PIN, OUTPUT);

  Master.setup();
  Motor.pinMode(BELT_RIGHT_FORWARD, OUTPUT);
  Motor.pinMode(BELT_RIGHT_BACKWARD, OUTPUT);
  Motor.pinMode(BELT_RIGHT_PWM, OUTPUT);
  Motor.pinMode(BELT_LEFT_FORWARD, OUTPUT);
  Motor.pinMode(BELT_LEFT_BACKWARD, OUTPUT);
  Motor.pinMode(BELT_LEFT_PWM, OUTPUT);
  Motor.pinMode(STATUS_PIN, OUTPUT);
  Motor.servo_attach(1, SERVO_PIN);

}

void loop() {
  Master.masterLoop();

  digitalWrite(LED_BUILTIN, statusValue);
  statusValue = !statusValue;
  Motor.digitalWrite(STATUS_PIN, statusValue);
  digitalWrite(STATUS_PIN, statusValue);

  int buttonLeft = digitalRead(BUTTON_LEFT_PIN);
  int buttonRight = digitalRead(BUTTON_RIGHT_PIN);
  if (!buttonLeft) {
    servoAngle -= 5;
  }

  if (!buttonRight) {
    servoAngle += 5;
  }

  servoAngle = constrain(servoAngle, 0, 180);
  Serial.print(!buttonLeft);
  Serial.print(' ');
  Serial.println(!buttonRight);
  Serial.println(servoAngle);
  Motor.servo_write(1, servoAngle);

  int stickLeft = analogRead(A2) - stickLeftNeutral;
  int stickRight = analogRead(A5) - stickRightNeutral;


  int leftBelt = map(constrain(abs(stickLeft), 40, stickLeftAbsMax), 40, stickLeftAbsMax, 0, 255);
  int rightBelt = map(constrain(abs(stickRight), 40, stickRightAbsMax), 40, stickRightAbsMax, 0, 255);
  
  // Serial.print(stickLeft);
  // Serial.print(' ');
  // Serial.print(stickRight);
  // Serial.print(', ');
  // Serial.print(leftBelt);
  // Serial.print(' ');
  // Serial.println(rightBelt);

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

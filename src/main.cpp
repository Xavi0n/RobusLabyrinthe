#include <Arduino.h>
#include <LibRobus.h>

#define LEFT_MOTOR_ID 0
#define RIGHT_MOTOR_ID 1
#define PULSE_PER_TURN 3200

unsigned long previousTime;
int lastLeftMotorError = 0;
int lastRightMotorError = 0;
int iLeftMotorError = 0;
int iRightMotorError = 0;
const double kp = 2;
const double ki = 5;
const double kd = 1;

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - previousTime;
  int calculatedPulse = (PULSE_PER_TURN/elapsedTime);

  int leftMotorPulse = ENCODER_Read(LEFT_MOTOR_ID);
  int rightMotorPulse = ENCODER_Read(RIGHT_MOTOR_ID);

  //P
  int leftMotorError = calculatedPulse - leftMotorPulse;
  int rightMotorError = calculatedPulse - rightMotorPulse;

  //I
  iLeftMotorError += leftMotorError * elapsedTime;
  iRightMotorError += rightMotorError * elapsedTime;

  //D
  int dLeftMotorError = (leftMotorError - lastLeftMotorError)/elapsedTime;
  int dRightMotorError = (rightMotorError - lastRightMotorError)/elapsedTime;

  // calcul
  double outLeftMotor = kp*leftMotorError + ki*iLeftMotorError + kd*dLeftMotorError;
  double outRightMotor = kp*rightMotorError + ki*iRightMotorError + kd*dRightMotorError;

  lastLeftMotorError = leftMotorError;
  previousTime = currentTime;

  MOTOR_SetSpeed(LEFT_MOTOR_ID, 0.1);
  MOTOR_SetSpeed(RIGHT_MOTOR_ID, 0.1);

  Serial.print(">");

  Serial.print("PLeft:");
  Serial.print(leftMotorError);
  Serial.print(",");

  Serial.print("ILeft:");
  Serial.print(iLeftMotorError);
  Serial.print(",");

  Serial.print("DLeft:");
  Serial.print(dLeftMotorError);
  Serial.print(",");

  Serial.print("outLeft:");
  Serial.print(outLeftMotor);
  Serial.print(",");

  Serial.print("PRight:");
  Serial.print(leftMotorError);
  Serial.print(",");

  Serial.print("IRight:");
  Serial.print(iLeftMotorError);
  Serial.print(",");

  Serial.print("DRight:");
  Serial.print(dLeftMotorError);
  Serial.print(",");

  Serial.print("outRight:");
  Serial.print(outLeftMotor);
  Serial.println();

  delay(50);
}
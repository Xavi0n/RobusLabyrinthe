#include <LibRobus.h>
#include <Arduino.h>

#define PULSE_PER_TURN 3200
#define POUCE_TO_CM 7.62
#define ROUE_DIAMETRE 3

const float kp = 0.001;
const float ki = 0.0005;
const float kd = 0.0001;
const float maxIntegral = 1000.0;

unsigned long previousTime = 0;
int leftMotorDesiredPulse = 0;
int rightMotorDesiredPulse = 0;
int leftMotorTotalPulse = 0;
int rightMotorTotalPulse = 0;
float lastLeftMotorError = 0;
float lastRightMotorError = 0;
float iLeftMotorError = 0;
float iRightMotorError = 0;

void initPID();
void setPIDDesiredPulse(int, int);
void runPIDController();
float getCoveredDistance();
void resetCoveredDistance();
float constrainFloat(float, float, float);
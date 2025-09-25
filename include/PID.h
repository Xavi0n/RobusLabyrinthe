#ifndef PID_H
#define PID_H

#include <LibRobus.h>
#include <Arduino.h>

#define PULSE_PER_TURN 3200
#define POUCE_TO_CM 7.62
#define ROUE_DIAMETRE 3

const float kp = 0.001;
const float ki = 0.0005;
const float kd = 0.0001;
const float maxIntegral = 1000.0;

void initPID();
void setPIDDesiredPulse(int, int);
void runPIDController();
float getCoveredDistance();
float getRightWheelCoveredDistance();
float getLeftWheelCoveredDistance();
void resetCoveredDistance();
float constrainFloat(float, float, float);
#endif
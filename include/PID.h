#ifndef PID_H
#define PID_H

#include <LibRobus.h>
#include <Arduino.h>

namespace PID{
    constexpr int PULSE_PER_TURN = 3200;
    constexpr float POUCE_TO_CM = 7.62f;
    constexpr float ROUE_DIAMETRE = 3.0f;
    const float kp = 0.001;
    const float ki = 0.0005;
    const float kd = 0.0001;
    const float maxIntegral = 1000.0;

    void initPID();
    void setPIDDesiredPulse(int, int);
    void runPIDController();
    float getCoveredDistance();
    float getRightCoveredDistance();
    float getLeftCoveredDistance();
    void resetCoveredDistance();
}
#endif
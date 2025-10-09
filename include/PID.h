#ifndef PID_H
#define PID_H

#include <LibRobus.h>
#include <Arduino.h>

namespace PID{
    constexpr float PULSE_PER_TURN = 3200.0f;
    constexpr float POUCE_TO_CM = 2.54f;
    constexpr float ROUE_DIAMETRE = 3.0f;
    const float kp = 0.01;
    const float ki = 0.005;
    const float kd = 0.000;
    const float maxIntegral = 1000.0;

    void initPID();
    void setPIDDesiredPulse(int, int);
    void runPIDController();
    void reset();
    float getCoveredDistance();
    float getRightCoveredDistance();
    float getLeftCoveredDistance();
    void resetCoveredDistance();
}
#endif
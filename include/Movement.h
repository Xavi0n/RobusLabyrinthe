#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"
#include "PID.h"

namespace Movement {
    constexpr float DIAMETRE = 0.19f;
    constexpr float QUARTER_TURN_DISTANCE = (DIAMETRE / 2.0f) * (PI / 2.0f);
    constexpr int TURNING_SPEED = 4000;
    constexpr int STRAIGHT_SPEED = 8000;

    enum MoveEnum { FORWARD, TURN_LEFT, TURN_RIGHT, UTURN, NONE };

    //function prototypes
    void moveForward();
    void turnRight();
    void turnLeft();
    void uTurn();
    void stop();
    void runMovementController();
    MoveEnum getCurrentMove();
}
#endif
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"
#include "PID.h"

namespace Movement {
    constexpr float FORWARD_DISTANCE = 50;
    //constexpr float TURN_DISTANCE = 14.92f;
    constexpr float TURN_DISTANCE = 14.50f;
    constexpr int TURNING_SPEED = 4500;
    constexpr int STRAIGHT_SPEED = 8000;

    enum MoveEnum { FORWARD, TURN_LEFT, TURN_RIGHT, UTURN, NONE };

    //function prototypes
    void initMovement();
    void moveForward();
    void turnRight();
    void turnLeft();
    void uTurn();
    void stop();
    void runMovementController();
    void endMove();
    void stopCheck();
    MoveEnum getCurrentMove();
}
#endif
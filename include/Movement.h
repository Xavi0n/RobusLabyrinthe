#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"
#include "PID.h"

namespace Movement {
    constexpr float ACCEL_FORWARD_DISTANCE = 8.0f;
    constexpr float FORWARD_DISTANCE = 50.0f;
    constexpr float ACCEL_TURN_DISTANCE = 4.0f;
    constexpr float TURN_DISTANCE = 14.30f;
    constexpr int MAX_TURNING_SPEED = 4500;
    constexpr int MIN_TURNING_SPEED = 500;
    constexpr int MAX_STRAIGHT_SPEED = 6500;
    constexpr int MIN_STRAIGHT_SPEED = 500;

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
    MoveEnum getLastMove();
}
#endif
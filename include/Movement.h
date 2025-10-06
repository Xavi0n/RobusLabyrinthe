#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"
#include "PID.h"

namespace Movement {
    constexpr float FORWARD_DISTANCE = 51;
    //constexpr float TURN_DISTANCE = 14.92f;
    constexpr float TURN_DISTANCE = 14.35f;
    constexpr int MAX_TURNING_SPEED = 5500;
    constexpr int MIN_TURNING_SPEED = 1500;
    constexpr int MAX_STRAIGHT_SPEED = 7000;
    constexpr int MIN_STRAIGHT_SPEED = 1500;
    constexpr float DECEL_TURN_DISTANCE = 5.0f;
    constexpr float DECEL_FORWARD_DISTANCE = 10.0f;

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
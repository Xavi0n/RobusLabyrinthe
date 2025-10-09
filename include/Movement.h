#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"
#include "PID.h"

namespace Movement {
    constexpr float ACCEL_FORWARD_DISTANCE = 9.0f;
    constexpr float FORWARD_DISTANCE = 51.0f;
    constexpr float ACCEL_TURN_DISTANCE = 4.8f;
    //constexpr float TURN_DISTANCE_LEFT = 15.00f;
    constexpr float TURN_DISTANCE_LEFT = 14.90f;
    //constexpr float TURN_DISTANCE_RIGHT = 14.15f;
    constexpr float TURN_DISTANCE_RIGHT = 13.70f;
    constexpr float UTURN_DISTANCE = 28.90f;
    constexpr int MAX_TURNING_SPEED = 6500;
    constexpr int MIN_TURNING_SPEED = 1500;
    constexpr int MAX_STRAIGHT_SPEED = 9500;
    constexpr int MIN_STRAIGHT_SPEED = 1500;

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
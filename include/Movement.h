#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"
#include "PID.h"

#define DIAMETRE 19
#define QUARTER_TURN_DISTANCE ((DIAMETRE / 2.0) * (PI / 2.0))
#define TURNING_SPEED 4000
#define SRAIGHT_SPEED 8000

enum MoveEnum { FORWARD, TURN_LEFT, TURN_RIGHT, UTURN, NONE };

//function prototypes
void moveForward();
void turnRight();
void turnLeft();
void uTurn();
void stop();
void runMovementController();
MoveEnum getCurrentMove();
#endif
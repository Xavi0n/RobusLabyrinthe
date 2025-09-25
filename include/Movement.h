#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "DetectionState.h"

//function prototypes
void moveForward();
void turnRight();
void turnLeft();
void uTurn();
#endif
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <Arduino.h>
#include <LibRobus.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define LEFT 0
#define RIGHT 1

#define LEFT_COLUMN 1
#define CENTER_COLUMN 2
#define RIGHT_COLUMN 3

//FUNCTION PROTOTYPES
void vUpdateRobotDirection(unsigned char ucTurnDirection);
void vUpdateRobotPosition();
bool bGetNearbyLines(unsigned char ucRobotDirection, unsigned char ucWhereIsRobotX, unsigned char ucWhereIsRobotY);
bool bDangerCheck ();

#endif
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <Arduino.h>
#include <LibRobus.h>
#include "Movement.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define LEFT 0
#define RIGHT 1

//Table mapping the lines is flipped vs IRL, hence why the left column IRL is the right column in the table
#define LEFT_COLUMN 5
#define CENTER_COLUMN 3
#define RIGHT_COLUMN 1

namespace Circuit {
    //FUNCTION PROTOTYPES
    void vUpdateRobotDirection(unsigned char ucTurnDirection);
    void vUpdateRobotPosition();
    bool bGetNearbyLines(unsigned char ucRobotDirection, unsigned char ucWhereIsRobotX, unsigned char ucWhereIsRobotY);
    bool bDangerCheck ();
    bool bIsAtFinish();
    bool bIsAtStart();
    void vSetDirection(int);
    int iGetUcRobotDirection();
}

#endif // CIRCUIT_H
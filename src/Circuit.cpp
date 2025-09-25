#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "main.h"
#include "Movement.h"


unsigned char ucRobotDirection = NORTH;
unsigned char ucWhereIsRobotX = 0;              // Represents the robot's current X
unsigned char ucWhereIsRobotY = CENTER_COLUMN;  // Represents the robot's current Y position with respect to the table
                                                // If the value of a variable is 2, the robot is between edges 2 and 3
//Function to update the robot direction based on the turn direction (LEFT or RIGHT)

void vUpdateRobotDirection(unsigned char ucTurnDirection)
{
    if (ucTurnDirection == LEFT) 
    {
        if (ucRobotDirection == NORTH)  //Since NORTH is 0, we need to set it to WEST (3) if we turn left
        {
            ucRobotDirection = WEST;
        }
        else
        {
            ucRobotDirection --;     
        }    
    }

    if (ucTurnDirection == RIGHT) 
    {
        if (ucRobotDirection == WEST)   //Since WEST is 3, we need to set it to NORTH (0) if we turn right
        {
            ucRobotDirection = NORTH;
        }
        else
        {
            ucRobotDirection ++;  
        }    
    }
}

void vUpdateRobotPosition()
{
    //Coordinates increment/decrement by 2 since the position represents the square between edges
    switch (ucRobotDirection)
    {
        case NORTH:
            ucWhereIsRobotY = ucWhereIsRobotY + 2;
            break;
        case EAST:
            ucWhereIsRobotX = ucWhereIsRobotX + 2;  //Add 2 since the position represents the square between edges
            break;
        case SOUTH:
            ucWhereIsRobotY = ucWhereIsRobotY - 2;
            break;
        case WEST:
            ucWhereIsRobotX = ucWhereIsRobotX - 2;  //Add 2 since the position represents the square between edges
            break;
    }
}

bool bGetNearbyLines(unsigned char ucRobotDirection, unsigned char ucWhereIsRobotX, unsigned char ucWhereIsRobotY)
{
    bool bLineInFront = false;
    switch (ucRobotDirection)
    {
        //NORTH and WEST add 1 to their position since they are facing down or right in the table
        //SOUTH and EAST check the line at their current position since they are facing up or left in the table
        case NORTH:
            if (uctWhereAreLines[ucWhereIsRobotY + 1][ucWhereIsRobotX] == 1)
            {                                                               
                Serial.println("Line in front");
                bLineInFront = true;
            }
            break;

        case EAST:
            if (uctWhereAreLines[ucWhereIsRobotY][ucWhereIsRobotX] == 1)
            {                                                               
                Serial.println("Line in front");
                bLineInFront = true;
            }
            break;

        case SOUTH:
            if (uctWhereAreLines[ucWhereIsRobotY][ucWhereIsRobotX] == 1)
            {                                                           
                Serial.println("Line in front");
                bLineInFront = true;
            }
            break;

        case WEST:
            if (uctWhereAreLines[ucWhereIsRobotY][ucWhereIsRobotX + 1] == 1)
            {
                Serial.println("Line in front");
                bLineInFront = true;
            }
            break;
    }
    return bLineInFront;
}

bool bDangerCheck ()
{
    bool bDangerFlag = false;
    bDangerFlag = bGetNearbyLines(ucRobotDirection, ucWhereIsRobotX, ucWhereIsRobotY) /*|| IRSESONRCHECK()*/;
    return bDangerFlag;
}
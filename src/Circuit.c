#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "main.h"

//Function to update the robot direction based on the turn direction (LEFT or RIGHT)
unsigned char ucUpdateRobotDirection(unsigned char ucTurnDirection)
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
  return ucRobotDirection;
}
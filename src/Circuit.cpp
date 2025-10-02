#include "Circuit.h"

namespace Circuit{
    unsigned char ucRobotDirection = NORTH;
    unsigned char ucWhereIsRobotX = CENTER_COLUMN;              // Represents the robot's current X
    unsigned char ucWhereIsRobotY = 1;  // Represents the robot's current Y position with respect to the table
                                                    // If the value of a variable is 2, the robot is between edges 2 and 3
    //Function to update the robot direction based on the turn direction (LEFT or RIGHT)


    // 1 means line present, 0 means no line. Each element of the table represents the edge
    // of a 50x50 cm square in the maze.
    // The first line of the table represents the start line of the maze, which means maze is flipped in the table vs reality.
    unsigned char uctWhereAreLines [22][7] = {
    {1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1},
    {1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1}
    };

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

    int iGetUcRobotDirection(){
        return ucRobotDirection;
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
                if (uctWhereAreLines[ucWhereIsRobotY][ucWhereIsRobotX+1] == 1)
                {                                                               
                    Serial.println("Line in front");
                    bLineInFront = true;
                }
                break;

            case SOUTH:
                if (uctWhereAreLines[ucWhereIsRobotY-1][ucWhereIsRobotX] == 1)
                {                                                           
                    Serial.println("Line in front");
                    bLineInFront = true;
                }
                break;

            case WEST:
                if (uctWhereAreLines[ucWhereIsRobotY][ucWhereIsRobotX - 1] == 1)
                {
                    Serial.println("Line in front");
                    bLineInFront = true;
                }
                break;
        }
        return bLineInFront;
    }

    bool bDangerCheck()
    {
        bool bDangerFlag = false;
        bDangerFlag = bGetNearbyLines(ucRobotDirection, ucWhereIsRobotX, ucWhereIsRobotY) /*|| IRSESONRCHECK()*/;
        return bDangerFlag;
    }

    bool bIsFinished(){
        return ucWhereIsRobotY >= 19;
    }
}
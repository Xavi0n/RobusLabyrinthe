#include <Arduino.h>
#include <LibRobus.h>
#include "main.h"
#include "Circuit.h"
#include "DetectionState.h"

unsigned char ucCurrentDirection;
unsigned char ucWhereIsRobotY;
unsigned char ucWhereIsRobotX;

void moveforward(){
    //if(bDangerCheck() == false){
    ucUpdateRobotPosition(ucCurrentDirection);
    //}
    //else {
    //[ADD WHAT WE WANT IT TO DO HERE]
    //}
   
    //move forward one unit (50cm) using PID
}

void turnRight(){
    
    //turn right using PID:
        //go forward a bit (so rotation point is in the middle)
        //stop
        //turn left wheel forwards and right wheel backwards until faced right
        //reverse a bit (so robot is perfectly in the center of the «square»)
    
    ucCurrentDirection = ucUpdateRobotDirection(RIGHT);
    //if(bDangerCheck() == true)
        //{
        //do a full u turn
        //}
}

void turnLeft(){

    //turn left using PID:
        //go forward a bit (so rotation point is in the middle)
        //stop
        //turn right wheel forwards and left wheel backwards until faced left
        //reverse a bit (so robot is perfectly in the center of the «square»)

    ucCurrentDirection = ucUpdateRobotDirection(LEFT);
    //if(bDangerCheck() == true)
        //{
        //do a full u turn
        //}
}
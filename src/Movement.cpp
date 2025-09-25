#include <Arduino.h>
#include <LibRobus.h>
#include "main.h"
#include "Circuit.h"
#include "DetectionState.h"
#include "Movement.h"

void moveforward(){
    if(bDangerCheck() == false){
        vUpdateRobotPosition();
        //move forward one unit (50cm) using PID
    }
    else {
    //[ADD WHAT WE WANT IT TO DO HERE]
    }
}

void turnRight(){
    
    //turn right using PID:
        //reverse a bit (so rotation point is in the middle)
        //stop
        //turn left wheel forwards and right wheel backwards until faced right
        //go forward a bit (so robot is perfectly in the center of the «square»)
    
    vUpdateRobotDirection(RIGHT);
    if(bDangerCheck() == true)
    {
        uTurn();
    }
}

void turnLeft(){

    //turn left using PID:
        //reverse a bit (so rotation point is in the middle)
        //stop
        //turn right wheel forwards and left wheel backwards until faced left
        //go forward a bit (so robot is perfectly in the center of the «square»)

    vUpdateRobotDirection(LEFT);
    if(bDangerCheck() == true)
    {
        //do a full u turn
        uTurn();
    }
}

void uTurn(){
    //be careful about using the turn commands to make it do a u turn, 
    //cuz it might trigger the danger check and make it do more than a 180 
}
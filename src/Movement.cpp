#include "Movement.h"

namespace Movement {
    MoveEnum currentMove;

    void initMovement(){
        PID::initPID();
        PID::setPIDDesiredPulse(0, 0);
        currentMove = MoveEnum::NONE;
    }

    void moveForward(){
        if(bDangerCheck() == false){
            //vUpdateRobotPosition();
            //move forward one unit (50cm) using PID
        }
        else {
        //[ADD WHAT WE WANT IT TO DO HERE]
        }
    }

    void turnRight(){
        currentMove = MoveEnum::TURN_RIGHT;
        PID::setPIDDesiredPulse(-TURNING_SPEED, TURNING_SPEED);
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

    void stop(){
        PID::setPIDDesiredPulse(0, 0);
        currentMove = MoveEnum::NONE;
        PID::resetCoveredDistance();
    }

    void runMovementController(){
        // Test if the move is done
        switch(currentMove){
            case MoveEnum::TURN_RIGHT: {
                if(PID::getRightWheelCoveredDistance() >= QUARTER_TURN_DISTANCE){
                    stop();
                }
                break;
            }
            default: {
                break;
            }
        }

        PID::runPIDController();
    }

    MoveEnum getCurrentMove(){
        return currentMove;
    }
}
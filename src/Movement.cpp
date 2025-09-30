#include "Movement.h"

namespace Movement {
    MoveEnum currentMove;
    MoveEnum lastMove;

    void initMovement(){
        PID::initPID();
        PID::setPIDDesiredPulse(0, 0);
        currentMove = MoveEnum::NONE;
        lastMove = MoveEnum::NONE;
    }

    void moveForward(){
        currentMove = MoveEnum::FORWARD;
        PID::setPIDDesiredPulse(STRAIGHT_SPEED, STRAIGHT_SPEED);
    }

    void turnRight(){
        currentMove = MoveEnum::TURN_RIGHT;
        PID::setPIDDesiredPulse(TURNING_SPEED, -TURNING_SPEED);
    }

    void turnLeft(){
        currentMove = MoveEnum::TURN_RIGHT;
        PID::setPIDDesiredPulse(-TURNING_SPEED, TURNING_SPEED);
    }

    void uTurn(){
        currentMove = MoveEnum::UTURN;
        PID::setPIDDesiredPulse(-TURNING_SPEED, TURNING_SPEED);
    }

    void stop(){
        PID::setPIDDesiredPulse(0, 0);
        endMove();
    }

    void endMove(){
        lastMove = currentMove;
        currentMove = MoveEnum::NONE;
        PID::resetCoveredDistance();
    }

    void runMovementController(){
        switch(currentMove){
            case MoveEnum::TURN_RIGHT: {
                if(PID::getRightCoveredDistance() >= TURN_DISTANCE){
                    stop();
                    Circuit::vUpdateRobotDirection(RIGHT);
                }
                break;
            }
            case MoveEnum::TURN_LEFT: {
                if(PID::getRightCoveredDistance() >= TURN_DISTANCE){
                    stop();
                    Circuit::vUpdateRobotDirection(LEFT);
                }
                break;
            }
            case MoveEnum::FORWARD: {
                if(PID::getCoveredDistance() >= FORWARD_DISTANCE){
                    endMove();
                    Circuit::vUpdateRobotPosition();
                }
                break;
            }
            case MoveEnum::UTURN: {
                if(PID::getRightCoveredDistance() >= TURN_DISTANCE*2){
                    stop();
                    Circuit::vUpdateRobotDirection(RIGHT);
                    Circuit::vUpdateRobotDirection(RIGHT);
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
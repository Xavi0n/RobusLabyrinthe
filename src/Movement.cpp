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
    }

    void turnRight(){
        currentMove = MoveEnum::TURN_RIGHT;
    }

    void turnLeft(){
        currentMove = MoveEnum::TURN_LEFT;
    }

    void uTurn(){
        currentMove = MoveEnum::UTURN;
    }

    void stop(){
        PID::setPIDDesiredPulse(0, 0);
        PID::reset();
        endMove();
    }

    void endMove(){
        lastMove = currentMove;
        currentMove = MoveEnum::NONE;
        PID::resetCoveredDistance();
    }

    float computeScaledSpeed(float remainingDistance, float decelDistance, float minSpeed, float maxSpeed) {
        if (remainingDistance <= 0) return 0;

        float speedFactor = constrain(remainingDistance / decelDistance, 0.0f, 1.0f);
        float scaledSpeed = minSpeed + (maxSpeed - minSpeed) * speedFactor;

        return scaledSpeed;
    }

    void runMovementController(){
        switch(currentMove){
            case MoveEnum::TURN_RIGHT: {
                float remaining = TURN_DISTANCE - PID::getRightCoveredDistance();
                if (remaining <= 0.1f) {
                    stop();
                    Circuit::vUpdateRobotDirection(RIGHT);
                } else {
                    float speed = computeScaledSpeed(remaining, DECEL_TURN_DISTANCE, MIN_TURNING_SPEED, MAX_TURNING_SPEED);
                    PID::setPIDDesiredPulse(speed, -speed);
                }
                break;
            }
            case MoveEnum::TURN_LEFT: {
                float remaining = TURN_DISTANCE - PID::getLeftCoveredDistance();
                if (remaining <= 0.1f) {
                    stop();
                    Circuit::vUpdateRobotDirection(LEFT);
                } else {
                    float speed = computeScaledSpeed(remaining, DECEL_TURN_DISTANCE, MIN_TURNING_SPEED, MAX_TURNING_SPEED);
                    PID::setPIDDesiredPulse(-speed, speed);
                }
                break;
            }
            case MoveEnum::FORWARD: {
                float remaining = FORWARD_DISTANCE - PID::getCoveredDistance();
                if (remaining <= 0.1f) {
                    endMove();
                    Circuit::vUpdateRobotPosition();
                } else {
                    float speed = computeScaledSpeed(remaining, DECEL_FORWARD_DISTANCE, MIN_STRAIGHT_SPEED, MAX_STRAIGHT_SPEED);
                    PID::setPIDDesiredPulse(speed, speed);
                }
                break;
            }
            case MoveEnum::UTURN: {
                float remaining = TURN_DISTANCE * 2 - PID::getRightCoveredDistance();
                if (remaining <= 0.1f) {
                    stop();
                    Circuit::vUpdateRobotDirection(RIGHT);
                    Circuit::vUpdateRobotDirection(RIGHT);
                } else {
                    float speed = computeScaledSpeed(remaining, DECEL_TURN_DISTANCE, MIN_TURNING_SPEED, MAX_TURNING_SPEED);
                    PID::setPIDDesiredPulse(-speed, speed);
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
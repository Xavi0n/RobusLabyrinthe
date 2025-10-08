#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "Movement.h"
#include "PID.h"

constexpr int LED_THRESHOLD = 650;
constexpr float WHISTLE_THRESHOLD = 150;
constexpr int FRONT_BUMPER_ID = 2;

bool isWhistleBlown = false;
bool invalidLastCheck = false;
bool reachedFinish = false;

bool getIRDetection();
void waitForWhistle();
void dance();
void delayNextMove();

//-----------------------------
// MAIN CODE.
//-----------------------------
void setup() {
    BoardInit();
    Serial.begin(115200);
    Movement::initMovement();
}

void loop() {
    if(!isWhistleBlown){
        waitForWhistle();
    }

    if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
    }
    else if(Circuit::bIsAtFinish() && !reachedFinish){
        Movement::uTurn();
        reachedFinish = true;
    }
    else if(Circuit::bIsAtStart() && reachedFinish){
        dance();
    }
    else if(!getIRDetection() && !Circuit::bDangerCheck()) {
        invalidLastCheck = false;
        Movement::moveForward();
        delayNextMove();
        return;
    } else if(invalidLastCheck && (Circuit::iGetUcRobotDirection() != NORTH && !reachedFinish) && (Circuit::iGetUcRobotDirection() != SOUTH && reachedFinish)) {
        Movement::uTurn();
        delayNextMove();
        return;
    } else {
        Circuit::vUpdateRobotDirection(RIGHT);
        if (!Circuit::bDangerCheck()) {
            Circuit::vUpdateRobotDirection(LEFT);
            Movement::turnRight();
            invalidLastCheck = true;
            delayNextMove();
            return;
        }
        Circuit::vUpdateRobotDirection(LEFT);

        Circuit::vUpdateRobotDirection(LEFT);
        if (!Circuit::bDangerCheck()) {
            Circuit::vUpdateRobotDirection(RIGHT);
            Movement::turnLeft();
            invalidLastCheck = true;
            delayNextMove();
            return;
        }
        Circuit::vUpdateRobotDirection(RIGHT);

        Movement::turnLeft();
        delayNextMove();
        return;
    }
 
    delay(5);
}

//-----------------------------
// FUNCTIONS
//-----------------------------
void dance(){
    while(true){
        if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
            Movement::runMovementController();
        }else{
            if(Movement::getLastMove() == Movement::MoveEnum::TURN_RIGHT){
                Movement::uTurn();
            }else{
                Movement::turnRight();
            }
        }

        delay(5);
    }
}

void delayNextMove(){
    delay(250);
}

bool getIRDetection(){
    int isGreenLedOn = analogRead(A0) < LED_THRESHOLD;
    int isRedLedOn = analogRead(A1) < LED_THRESHOLD;
    return isGreenLedOn && isRedLedOn;
}

void waitForWhistle(){
    while(!isWhistleBlown)
    {
        int A2Value = analogRead(A2);
        int A3Value = analogRead(A3);
        if((A3Value - A2Value) >= WHISTLE_THRESHOLD || ROBUS_IsBumper(FRONT_BUMPER_ID))
        {
            isWhistleBlown = true;
        }

        delay(50);
    }
}
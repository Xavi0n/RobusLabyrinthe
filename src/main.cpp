#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "Movement.h"
#include "PID.h"

constexpr int IR_GREEN_PIN = 48;
constexpr int IR_RED_PIN = 49;
constexpr int LED_THRESHOLD = 650;
constexpr int WHISTLE_THRESHOLD = 1;
constexpr int FRONT_BUMPER_ID = 2;

bool isWhistleBlown = false;
bool invalidLastCheck = false;
bool reachedFinish = false;

bool getIRDetection();
void waitForWhistle();
void dance();

//-----------------------------
// MAIN CODE.
//-----------------------------
void setup() {
    BoardInit();
    pinMode(IR_GREEN_PIN, INPUT_PULLUP);
    pinMode(IR_RED_PIN, INPUT_PULLUP);
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
        return;
    } else if(invalidLastCheck && (Circuit::iGetUcRobotDirection() != NORTH && !reachedFinish) && (Circuit::iGetUcRobotDirection() != SOUTH && reachedFinish)) {
        Movement::uTurn();
        return;
    } else {
        Circuit::vUpdateRobotDirection(RIGHT);
        if (!Circuit::bDangerCheck()) {
            Circuit::vUpdateRobotDirection(LEFT);
            Movement::turnRight();
            invalidLastCheck = true;
            return;
        }
        Circuit::vUpdateRobotDirection(LEFT);

        Circuit::vUpdateRobotDirection(LEFT);
        if (!Circuit::bDangerCheck()) {
            Circuit::vUpdateRobotDirection(RIGHT);
            Movement::turnLeft();
            invalidLastCheck = true;
            return;
        }
        Circuit::vUpdateRobotDirection(RIGHT);

        Movement::turnLeft();
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

bool getIRDetection(){
    int isGreenLedOn = analogRead(A0) < LED_THRESHOLD;
    int isRedLedOn = analogRead(A1) < LED_THRESHOLD;
    return isGreenLedOn && isRedLedOn;
}

void waitForWhistle(){
    while(!isWhistleBlown)
    {
        Serial.println(analogRead(A2));
        if(analogRead(A2) >= WHISTLE_THRESHOLD || ROBUS_IsBumper(FRONT_BUMPER_ID))
        {
            isWhistleBlown = true;
        }

        delay(10);
    }
}
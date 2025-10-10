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
    // Wait for whitle
    if(!isWhistleBlown){
        waitForWhistle();
    }

    // Run the current movement if there is any
    if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
        return;
    }

    // Check if the robot is at the finish
    if(Circuit::bIsAtFinish() && !reachedFinish){
        Movement::uTurn();

        while(true){
            if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
                Movement::runMovementController();
            }

            Movement::moveForward();
        }
        return;
    }

    // Check if there is an obstacle in front
    if(!getIRDetection() && !Circuit::bDangerCheck()) {
        if(Movement::getLastMove() != Movement::MoveEnum::NONE){
            delayNextMove();
        }
        invalidLastCheck = false;
        Movement::moveForward();
        return;
    }

    delayNextMove();

    // Handle invalid check (last turn didnt work)
    if(invalidLastCheck && ((Circuit::iGetUcRobotDirection() != NORTH && !reachedFinish) || (Circuit::iGetUcRobotDirection() != SOUTH && reachedFinish))) {
        Movement::uTurn();
        return;
    }

    // Check right and turn if there is no line
    if (!Circuit::bDangerCheckRight() && ((Circuit::iGetUcRobotDirection() != EAST && !reachedFinish) || (Circuit::iGetUcRobotDirection() != WEST && reachedFinish))) {
        Movement::turnRight();
        invalidLastCheck = true;
        return;
    }

    // Check left and turn if there is no line
    if (!Circuit::bDangerCheckLeft() && ((Circuit::iGetUcRobotDirection() != WEST && !reachedFinish) || (Circuit::iGetUcRobotDirection() != EAST && reachedFinish))) {
        Movement::turnLeft();
        invalidLastCheck = true;
        return;
    }

    // Default move
    Movement::turnLeft();
    return;
}

//-----------------------------
// FUNCTIONS
//-----------------------------
void delayNextMove(){
    delay(100);
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
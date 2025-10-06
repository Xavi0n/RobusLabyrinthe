#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "Movement.h"
#include "PID.h"

constexpr int IR_GREEN_PIN = 48;
constexpr int IR_RED_PIN = 49;
constexpr int LED_THRESHOLD = 650;
unsigned long startMillis = 0;
constexpr int WHISTLE_THRESHOLD = 1;

bool isWhistleBlown = false;
bool invalidLastCheck = false;
bool finishedAck = false;

bool getIRDetection();
void printDirection();
bool isTimePast(int seconds);
void resetTimer();
void whistleDetection();
void dance();

//-----------------------------
// MAIN CODE.
//-----------------------------
void setup() {
    BoardInit();
    pinMode(IR_GREEN_PIN, INPUT_PULLUP);
    pinMode(IR_RED_PIN, INPUT_PULLUP);
    Serial.begin(115200);
    startMillis = millis();
    Movement::initMovement();
}

void loop() {
    if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
    }
    else{
        if(Circuit::bIsFinished() && !finishedAck){
            Movement::uTurn();
            finishedAck = true;
        }
        else if(!getIRDetection() && !Circuit::bDangerCheck()) {
            invalidLastCheck = false;
            Movement::moveForward();
            return;
        } else if(invalidLastCheck && Circuit::iGetUcRobotDirection() != NORTH) {
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

void printDirection(){
    switch (Circuit::iGetUcRobotDirection()) {
        case NORTH:
            Serial.print("Face: North");
            break;
        case EAST:
            Serial.print("Face: Est");
            break;
        case SOUTH:
            Serial.print("Face: Sud");
            break;
        case WEST:
            Serial.print("Face: Ouest");
            break;
        default:
            Serial.print("Facing: IDK");
            break;
    }
}

bool getIRDetection(){
    int isGreenLedOn = analogRead(A0) < LED_THRESHOLD;
    int isRedLedOn = analogRead(A1) < LED_THRESHOLD;
    return isGreenLedOn && isRedLedOn;
}

void whistleDetection(){
    bool whistleLoopEnd = false;
    while(whistleLoopEnd == false)
    {
        //Make sure to connect whistle detector's out to pin A2
        if(analogRead(A2) > WHISTLE_THRESHOLD)
        {
            whistleLoopEnd = true;
            isWhistleBlown = true;
        }
    }
}
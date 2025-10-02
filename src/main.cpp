#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "Movement.h"
#include "PID.h"

constexpr int IR_GREEN_PIN = 48;
constexpr int IR_RED_PIN = 49;
constexpr int LED_THRESHOLD = 650;
unsigned long startMillis = 0;
Movement::MoveEnum lastMove = Movement::MoveEnum::NONE;
//ADJUST THIS VALUE LATER, BECAUSE I DON'T KNOW HOW HIGH OR HOW LOW IT NEEDS TO BE!!!!!
constexpr int WHISTLE_THRESHOLD = 1;
bool isWhistleBlown = false;
bool invalidLastCheck = false;

bool getIRDetection();
void printDirection();
bool isTimePast(int seconds);
void resetTimer();
void whistleDetection();

//-----------------------------
// MAIN CODE
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
    //printDirection();
    /*
    Movement::MoveEnum currentMove = Movement::getCurrentMove();
    if (lastMove != currentMove) {
        if(currentMove == Movement::MoveEnum::NONE){
            resetTimer();
        }

        lastMove = currentMove;
    }

    if(isTimePast(5)){
        Movement::turnRight();
    }

    Movement::runMovementController();*/

    if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
    } else {
        if(Circuit::bIsFinished()){
            while(1){}
        }
        else if (!getIRDetection() && !Circuit::bDangerCheck()) {
            invalidLastCheck = false;
            Movement::moveForward();
        } else {
            if (invalidLastCheck == true) {
                Movement::uTurn();
            } else {
                Movement::turnRight();
                invalidLastCheck = true;
            }
        }
    }
 
    delay(5);
}

//-----------------------------
// FUNCTIONS
//-----------------------------
bool isTimePast(int seconds){
    return millis() - startMillis >= (unsigned long)seconds * 1000;
}

void resetTimer(){
    startMillis = millis();
}

void printDirection(){
    switch (Circuit::iGetUcRobotDirection()) {
        case NORTH:
            Serial.println("Face: North");
            break;
        case EAST:
            Serial.println("Face: Est");
            break;
        case SOUTH:
            Serial.println("Face: Sud");
            break;
        case WEST:
            Serial.println("Face: Ouest");
            break;
        default:
            Serial.println("Facing: IDK");
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
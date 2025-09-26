#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "Movement.h"
#include "PID.h"

constexpr int IR_GREEN_PIN = 2;
constexpr int IR_RED_PIN = 3;

volatile bool isGreenLedOn, isRedLedOn;

bool getIRDetection();

//-----------------------------
// INTERUPTS
//-----------------------------
void irGreenLed(){
    isGreenLedOn = !digitalRead(IR_GREEN_PIN);
}

void irRedLed(){
    isRedLedOn = !digitalRead(IR_RED_PIN);
}

//-----------------------------
// MAIN CODE
//-----------------------------
void setup() {
    BoardInit();
    pinMode(IR_GREEN_PIN, INPUT_PULLUP);
    pinMode(IR_RED_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(IR_GREEN_PIN), irGreenLed, CHANGE);
    attachInterrupt(digitalPinToInterrupt(IR_RED_PIN), irRedLed, CHANGE);
    Serial.begin(115200);
    Movement::turnRight();
}

void loop() {
    if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
    } else {
        // TODO
        /*
        if(bGetIsFinished()){
            exit();
        }
        */
        if (!Circuit::bDangerCheck() && !getIRDetection()) {
            Movement::moveForward();
        } else {
            int robotDirection = Circuit::iGetUcRobotDirection();
            if (robotDirection == WEST || robotDirection == EAST) {
                Movement::uTurn();
            } else {
                Movement::turnRight();
            }
        }
    }

    delay(50);
}

//-----------------------------
// FUNCTIONS
//-----------------------------
bool getIRDetection(){
    return isGreenLedOn && isRedLedOn;
}
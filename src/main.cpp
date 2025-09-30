#include <Arduino.h>
#include <LibRobus.h>
#include "Circuit.h"
#include "Movement.h"
#include "PID.h"

constexpr int IR_GREEN_PIN = 48;
constexpr int IR_RED_PIN = 49;
constexpr int LED_THRESHOLD = 650;
bool invalidLastCheck = false;

bool getIRDetection();
void printDirection();

//-----------------------------
// MAIN CODE
//-----------------------------
void setup() {
    BoardInit();
    pinMode(IR_GREEN_PIN, INPUT_PULLUP);
    pinMode(IR_RED_PIN, INPUT_PULLUP);
    Serial.begin(115200);
    Movement::initMovement();
    
}

void loop() {
    //printDirection();
    
    if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
    } else {
        // TODO get is finished
        if (!getIRDetection()) {
            invalidLastCheck = false;
            Movement::moveForward();
        } else {
            Movement::turnRight();
        }
    }

    /*if (Movement::getCurrentMove() != Movement::MoveEnum::NONE) {
        Movement::runMovementController();
    } else {
        // TODO get is finished
        if (!getIRDetection()) {
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
    }*/
 
    delay(5);
}

//-----------------------------
// FUNCTIONS
//-----------------------------
void printDirection(){
    switch (Circuit::iGetUcRobotDirection()) {
        case NORTH:
            Serial.println("North");
            break;
        case EAST:
            Serial.println("East");
            break;
        case SOUTH:
            Serial.println("South");
            break;
        case WEST:
            Serial.println("West");
            break;
        default:
            Serial.println("Unknown Direction");
            break;
    }
}
bool getIRDetection(){
    int isGreenLedOn = analogRead(A0) < LED_THRESHOLD;
    int isRedLedOn = analogRead(A1) < LED_THRESHOLD;
    return isGreenLedOn && isRedLedOn;
}
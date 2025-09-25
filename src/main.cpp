#include <Arduino.h>
#include <LibRobus.h>
//#include "PID.h"

void setup() {
    BoardInit();
    //initPID();
    Serial.begin(115200);
    //setPIDDesiredPulse(3200, 3200);
}

void loop() {
    /*runPIDController();
    
    if(getCoveredDistance() >= 50){
         setPIDDesiredPulse(0, 0);
    }*/
    
    delay(50);
}
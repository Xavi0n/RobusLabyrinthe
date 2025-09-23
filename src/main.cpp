#include <Arduino.h>
#include <LibRobus.h>
#include "main.h"
#include "Circuit.h"
#include "DetectionState.h"

#define IR_GREEN_PIN 2
#define IR_RED_PIN 3

volatile bool isGreenLedOn, isRedLedOn;

void irGreenLed(){
  isGreenLedOn = !digitalRead(IR_GREEN_PIN);
}

void irRedLed(){
  isRedLedOn = !digitalRead(IR_RED_PIN);
}

void setup() {
  pinMode(IR_GREEN_PIN, INPUT_PULLUP);
  pinMode(IR_RED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IR_GREEN_PIN), irGreenLed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IR_RED_PIN), irRedLed, CHANGE);
  Serial.begin(9600);
}

void loop() {
  DetectionState detectionState = getDetection(isGreenLedOn, isRedLedOn);

  Serial.print("Détection:");
  Serial.println(detectionState);

  delay(1000);
}
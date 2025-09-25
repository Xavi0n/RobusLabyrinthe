#include "PID.h"

unsigned long previousTime = 0;
int leftMotorDesiredPulse = 0;
int rightMotorDesiredPulse = 0;
int leftMotorTotalPulse = 0;
int rightMotorTotalPulse = 0;
float lastLeftMotorError = 0;
float lastRightMotorError = 0;
float iLeftMotorError = 0;
float iRightMotorError = 0;

float constrainFloat(float value, float min_val, float max_val) {
    if (value < min_val) return min_val;
    if (value > max_val) return max_val;
    return value;
}

void initPID(){
    previousTime = millis();
}

void setPIDDesiredPulse(int newLeftMotorDesiredPulse, int newRightMotorDesiredPulse){
    leftMotorDesiredPulse = newLeftMotorDesiredPulse;
    rightMotorDesiredPulse = newRightMotorDesiredPulse;
}

void runPIDController() {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - previousTime;
    
    float leftMotorCalculatedPulse = (leftMotorDesiredPulse * elapsedTime / 1000.0);
    float rightMotorCalculatedPulse = (rightMotorDesiredPulse * elapsedTime / 1000.0);
    int leftMotorPulse = ENCODER_ReadReset(LEFT);
    int rightMotorPulse = ENCODER_ReadReset(RIGHT);
    
    leftMotorTotalPulse += leftMotorPulse;
    rightMotorTotalPulse += rightMotorPulse;

    // P
    float leftMotorError = leftMotorCalculatedPulse - leftMotorPulse;
    float rightMotorError = rightMotorCalculatedPulse - rightMotorPulse;
    
    // I
    float elapsedTimeSec = elapsedTime / 1000.0;
    iLeftMotorError += leftMotorError * elapsedTimeSec;
    iRightMotorError += rightMotorError * elapsedTimeSec;
    
    iLeftMotorError = constrainFloat(iLeftMotorError, -maxIntegral, maxIntegral);
    iRightMotorError = constrainFloat(iRightMotorError, -maxIntegral, maxIntegral);
    
    // D
    float dLeftMotorError = (leftMotorError - lastLeftMotorError) / elapsedTimeSec;
    float dRightMotorError = (rightMotorError - lastRightMotorError) / elapsedTimeSec;
    
    // Calculation
    float outLeftMotor = kp * leftMotorError + ki * iLeftMotorError + kd * dLeftMotorError;
    float outRightMotor = kp * rightMotorError + ki * iRightMotorError + kd * dRightMotorError;
    
    // Range 0-1
    outLeftMotor = constrainFloat(outLeftMotor, 0.0, 1.0);
    outRightMotor = constrainFloat(outRightMotor, 0.0, 1.0);

    MOTOR_SetSpeed(RIGHT, outRightMotor);
    MOTOR_SetSpeed(LEFT, outLeftMotor);
    
    lastLeftMotorError = leftMotorError;
    lastRightMotorError = rightMotorError;
    previousTime = currentTime;

    // Debug
    Serial.print(">");
    Serial.print("TotalLeftPulse:");
    Serial.print(leftMotorTotalPulse);
    Serial.print(",");
    Serial.print("TotalRightPulse:");
    Serial.print(rightMotorTotalPulse);
    Serial.print(",");
    Serial.print("PLeft:");
    Serial.print(leftMotorError);
    Serial.print(",");
    Serial.print("ILeft:");
    Serial.print(iLeftMotorError);
    Serial.print(",");
    Serial.print("DLeft:");
    Serial.print(dLeftMotorError);
    Serial.print(",");
    Serial.print("outLeft:");
    Serial.print(outLeftMotor);
    Serial.print(",");
    Serial.print("outRight:");
    Serial.print(outRightMotor);
    Serial.println();
}

// Retourne la distance en cm
float getCoveredDistance(){
    float combinedAveragePulse = (leftMotorTotalPulse + rightMotorTotalPulse) / 2;
    float distanceEnPouce = combinedAveragePulse / PULSE_PER_TURN * ROUE_DIAMETRE;
    float distance = distanceEnPouce * POUCE_TO_CM;
    return distance;
}

void resetCoveredDistance(){
    leftMotorTotalPulse = 0;
    rightMotorTotalPulse = 0;
}
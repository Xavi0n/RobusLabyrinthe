#include "PID.h"

namespace PID{
    unsigned long previousTime = 0;
    int leftDesiredPulse = 0;
    int rightDesiredPulse = 0;
    int leftTotalPulse = 0;
    int rightTotalPulse = 0;
    float lastLeftError = 0;
    float lastRightError = 0;
    float iLeftError = 0;
    float iRightError = 0;

    inline float constrainFloat(float value, float min_val, float max_val) {
        if (value < min_val) return min_val;
        if (value > max_val) return max_val;
        return value;
    }

    void initPID(){
        previousTime = millis();
    }

    void setPIDDesiredPulse(int newLeftDesiredPulse, int newRightDesiredPulse){
        leftDesiredPulse = newLeftDesiredPulse;
        rightDesiredPulse = newRightDesiredPulse;
        iLeftError = 0;
        iRightError = 0;
        lastLeftError = 0;
        lastRightError = 0;
    }

    void runPIDController() {
        unsigned long currentTime = millis();
        float elapsedTimeSec = (currentTime - previousTime) / 1000.0f;

        if (elapsedTimeSec <= 0.0f) return;
        
        float leftMotorCalculatedPulse = (abs(leftDesiredPulse) * elapsedTimeSec);
        float rightMotorCalculatedPulse = (abs(rightDesiredPulse) * elapsedTimeSec);
        int rawLeftMotorPulse = ENCODER_ReadReset(LEFT);
        int rawRightMotorPulse = ENCODER_ReadReset(RIGHT);
        int rightMotorPulse = abs(rawRightMotorPulse);
        int leftMotorPulse = abs(rawLeftMotorPulse);
        
        leftTotalPulse += rawLeftMotorPulse;
        rightTotalPulse += rawRightMotorPulse;

        // P
        float leftMotorError = leftMotorCalculatedPulse - leftMotorPulse;
        float rightMotorError = rightMotorCalculatedPulse - rightMotorPulse;
        
        // I
        iLeftError += leftMotorError * elapsedTimeSec;
        iRightError += rightMotorError * elapsedTimeSec;
        
        iLeftError = constrainFloat(iLeftError, -maxIntegral, maxIntegral);
        iRightError = constrainFloat(iRightError, -maxIntegral, maxIntegral);
        
        // D
        float dLeftMotorError = (leftMotorError - lastLeftError) / elapsedTimeSec;
        float dRightMotorError = (rightMotorError - lastRightError) / elapsedTimeSec;
        
        // Calculation
        float outLeftMotor = kp * leftMotorError + ki * iLeftError + kd * dLeftMotorError;
        float outRightMotor = kp * rightMotorError + ki * iRightError + kd * dRightMotorError;
        
        // Range 0-1
        outLeftMotor = constrainFloat(outLeftMotor, 0, 1.0);
        outRightMotor = constrainFloat(outRightMotor, 0, 1.0);

        if(leftDesiredPulse < 0){
            outLeftMotor = -outLeftMotor;
        }
        if(rightDesiredPulse < 0){
            outRightMotor = -outRightMotor;
        }

        MOTOR_SetSpeed(RIGHT, outRightMotor);
        MOTOR_SetSpeed(LEFT, outLeftMotor);
        
        lastLeftError = leftMotorError;
        lastRightError = rightMotorError;
        previousTime = currentTime;
    }

    void reset(){
        lastLeftError = 0;
        lastRightError = 0;
        iLeftError = 0;
        iRightError = 0;
    }

    // Retourne la distance en cm
    float getCoveredDistance(){
        float combinedAveragePulse = (leftTotalPulse + rightTotalPulse) / 2;
        float distance_cm = abs(combinedAveragePulse) / PULSE_PER_TURN * (PI * ROUE_DIAMETRE) * POUCE_TO_CM;
        return distance_cm;
    }

    float getRightCoveredDistance() {
        float distance_cm = abs(rightTotalPulse) / PULSE_PER_TURN * (PI * ROUE_DIAMETRE) * POUCE_TO_CM;
        return distance_cm;
    }

    float getLeftCoveredDistance(){
        float distance_cm = abs(leftTotalPulse) / PULSE_PER_TURN * (PI * ROUE_DIAMETRE) * POUCE_TO_CM;
        return distance_cm;
    }

    void resetCoveredDistance(){
        leftTotalPulse = 0;
        rightTotalPulse = 0;
    }
}
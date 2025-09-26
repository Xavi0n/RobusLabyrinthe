#include "PID.h"

namespace PID{
    unsigned long previousTime = 0;
    int leftMotorDesiredPulse = 0;
    int rightMotorDesiredPulse = 0;
    int leftMotorTotalPulse = 0;
    int rightMotorTotalPulse = 0;
    float lastLeftMotorError = 0;
    float lastRightMotorError = 0;
    float iLeftMotorError = 0;
    float iRightMotorError = 0;

    inline float constrainFloat(float value, float min_val, float max_val) {
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
        iLeftMotorError = 0;
        iRightMotorError = 0;
        lastLeftMotorError = 0;
        lastRightMotorError = 0;
    }

    void runPIDController() {
        unsigned long currentTime = millis();
        float elapsedTimeSec = (currentTime - previousTime) / 1000.0f;

        if (elapsedTimeSec <= 0.0f) return;
        
        float leftMotorCalculatedPulse = (abs(leftMotorDesiredPulse) * elapsedTimeSec);
        float rightMotorCalculatedPulse = (abs(rightMotorDesiredPulse) * elapsedTimeSec);
        int leftMotorPulse = abs(ENCODER_ReadReset(LEFT));
        int rightMotorPulse = abs(ENCODER_ReadReset(RIGHT));
        
        leftMotorTotalPulse += leftMotorPulse;
        rightMotorTotalPulse += rightMotorPulse;

        // P
        float leftMotorError = leftMotorCalculatedPulse - leftMotorPulse;
        float rightMotorError = rightMotorCalculatedPulse - rightMotorPulse;
        
        // I
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
        outLeftMotor = constrainFloat(outLeftMotor, 0, 1.0);
        outRightMotor = constrainFloat(outRightMotor, 0, 1.0);

        if(leftMotorDesiredPulse < 0){
            outLeftMotor = -outLeftMotor;
        }
        if(rightMotorDesiredPulse < 0){
            outRightMotor = -outRightMotor;
        }

        MOTOR_SetSpeed(RIGHT, outRightMotor);
        MOTOR_SetSpeed(LEFT, outLeftMotor);
        
        lastLeftMotorError = leftMotorError;
        lastRightMotorError = rightMotorError;
        previousTime = currentTime;

        // Debug
        #ifdef DEBUG
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
        #endif
    }

    // Retourne la distance en cm
    float getCoveredDistance(){
        float combinedAveragePulse = (leftMotorTotalPulse + rightMotorTotalPulse) / 2;
        float distanceEnPouce = combinedAveragePulse / PULSE_PER_TURN * ROUE_DIAMETRE;
        float distance = distanceEnPouce * POUCE_TO_CM;
        return distance;
    }

    float getRightWheelCoveredDistance(){
        float distanceEnPouce = (float)rightMotorTotalPulse / PULSE_PER_TURN * ROUE_DIAMETRE;
        float distance = distanceEnPouce * POUCE_TO_CM;
        return distance;
    }

    float getLeftWheelCoveredDistance(){
        float distanceEnPouce = (float)leftMotorTotalPulse / PULSE_PER_TURN * ROUE_DIAMETRE;
        float distance = distanceEnPouce * POUCE_TO_CM;
        return distance;
    }

    void resetCoveredDistance(){
        leftMotorTotalPulse = 0;
        rightMotorTotalPulse = 0;
    }
}
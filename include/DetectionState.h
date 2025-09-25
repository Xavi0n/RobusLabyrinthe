#ifndef DETECTION_STATE_H
#define DETECTION_STATE_H

enum DetectionState { DETECT_NONE, DETECT_LEFT, DETECT_RIGHT, DETECT_FRONT };

DetectionState getDetection(bool detectionOnRight, bool detectionOnLeft);
#endif
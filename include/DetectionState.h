#pragma once

enum DetectionState { DETECT_NONE, DETECT_LEFT, DETECT_RIGHT, DETECT_FRONT };

DetectionState getDetection(bool detectionOnRight, bool detectionOnLeft);

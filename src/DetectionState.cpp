#include "DetectionState.h"

DetectionState getDetection(bool detectionOnRight, bool detectionOnLeft) {
  if (detectionOnRight && detectionOnLeft) return DETECT_FRONT;
  if (detectionOnRight) return DETECT_RIGHT;
  if (detectionOnLeft) return DETECT_LEFT;
  return DETECT_NONE;
}

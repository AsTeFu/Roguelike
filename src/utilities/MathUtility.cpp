//
// Created by AsTeFu on 01.09.2019.
//

#include <utilities/MathUtility.h>
int MathUtility::clamp(int value, int min, int max) {
  if (value < min) return min;
  if (value > max) return max;
  return value;
}
int MathUtility::sign(int num) {
  return num > 0 ? 1 : (num < 0 ? -1 : 0);
}

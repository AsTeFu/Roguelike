//
// Created by AsTeFu on 27.07.2019.
//

#ifndef INCLUDE_UTILITIES_RANDOM_H_
#define INCLUDE_UTILITIES_RANDOM_H_

#include <time.h>
#include <random>
#include "utilities/Range.h"

class Random {
  static std::mt19937 _rnd;

 public:
  static int random(int min, int max);
  static int random(int max);
  static int randomDist(int min, int max);
  static int random(const Range& range);
};

#endif  // INCLUDE_UTILITIES_RANDOM_H_

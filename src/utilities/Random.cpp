//
// Created by AsTeFu on 27.07.2019.
//

#include "Utilities/Random.h"
#include <utilities/Range.h>
#include <iostream>

std::mt19937 Random::_rnd = [] {
  std::mt19937 tmp;
  time_t t;
  time(&t);
  std::cout << "rnd: " << t << std::endl;
  tmp.seed(t);
  return tmp;
}();

int Random::random(int min, int max) {
  // std::normal_distribution<int> d{0, 1, minValue, maxValue};
  return static_cast<int>(_rnd() % (max - min + 1) + min);
}
int Random::random(int max) {
  if (max == 0) {
    std::cout << "Random(0)" << std::endl;
    return 0;
  }
  return static_cast<int>(_rnd() % max);
}
int Random::random(const Range& range) {
  return static_cast<int>(_rnd() % (range.maxValue - range.minValue + 1) + range.minValue);
}
int Random::randomDist(int min, int max) {
  std::normal_distribution<> distribution(max - (min / 2), (max - min) / 5);
  return distribution(_rnd);
}

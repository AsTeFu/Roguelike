//
// Created by AsTeFu on 27.07.2019.
//

#include "game/Utility/Random.h"
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
  return static_cast<int>(_rnd() % max);
}
int Random::randomDist(int min, int max) {
  std::normal_distribution<> distribution(max - (min / 2), (max - min) / 5);
  return distribution(_rnd);
}

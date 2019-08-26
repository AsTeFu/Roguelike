//
// Created by AsTeFu on 27.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_RANDOM_H_
#define INCLUDE_GAME_UTILITY_RANDOM_H_

#include <time.h>
#include <random>

class Random {
  static std::mt19937 _rnd;

 public:
  static int random(int min, int max);
  static int random(int max);
  static int randomDist(int min, int max);
};

#endif  // INCLUDE_GAME_UTILITY_RANDOM_H_

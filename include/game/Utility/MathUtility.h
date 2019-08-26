//
// Created by AsTeFu on 24.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_MATHUTILITY_H_
#define INCLUDE_GAME_UTILITY_MATHUTILITY_H_

class MathUtility {
 public:
  static int sign(int num) {
    return num > 0 ? 1 : (num < 0 ? -1 : 0);
  }
};

#endif  // INCLUDE_GAME_UTILITY_MATHUTILITY_H_

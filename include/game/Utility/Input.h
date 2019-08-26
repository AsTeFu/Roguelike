//
// Created by AsTeFu on 10.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_INPUT_H_
#define INCLUDE_GAME_UTILITY_INPUT_H_

#include "game/Utility/Vector2.h"

class Input {
 public:
  static Vector2 axis;
  static void updateAxis();
  static const Vector2& getAxis();

  static bool isPressed(int button);
  static bool isExit();
  static bool mouseLeft();
  static bool hasInput();
  static int read();
  static bool mouseRight();
};

#endif  // INCLUDE_GAME_UTILITY_INPUT_H_

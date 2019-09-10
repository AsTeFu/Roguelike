//
// Created by AsTeFu on 10.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_INPUT_H_
#define INCLUDE_GAME_UTILITY_INPUT_H_

#include <utilities/KeyCode.h>
#include <map>
#include <vector>
#include "utilities/Vector2.h"

class Input {
 private:
  // static std::vector<bool> keys;
  static std::map<int, bool> keys;

 public:
  static bool getKey(const KeyCode& code);
  static bool getKeyDown(const KeyCode& code);
  static void updateKeys();
  static bool isExit();
  static bool mouseLeft();
  static bool hasInput();
  static int read();
  static bool mouseRight();
  static bool getKeyUp(const KeyCode& button);
  static bool check(const KeyCode& button);
  static bool isMouseWheel();
  static int getMouseWheel();
  static Vector2 getMousePosition();
};

#endif  // INCLUDE_GAME_UTILITY_INPUT_H_

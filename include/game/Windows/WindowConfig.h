//
// Created by AsTeFu on 14.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_WINDOWCONFIG_H_
#define INCLUDE_GAME_WINDOWS_WINDOWCONFIG_H_

#include <BearLibTerminal.h>
#include <string>
#include <utility>
#include "game/Utility/Vector2.h"

class WindowConfig {
 private:
  static int _allLayer;

 public:
  int layer;
  color_t color;
  Vector2 size;
  Vector2 position;
  std::string name;

  WindowConfig(const Vector2& size, const Vector2& position, color_t color, std::string  name)
      : layer(_allLayer++), color(color), size(size), position(position), name(std::move(name)) {
    // std::cout << "ConfigWindow create!" << std::endl;
  }
};

#endif  // INCLUDE_GAME_WINDOWS_WINDOWCONFIG_H_

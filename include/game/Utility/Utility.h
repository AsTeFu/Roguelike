//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_UTILITY_H_
#define INCLUDE_GAME_UTILITY_UTILITY_H_

#include <BearLibTerminal.h>
#include <dirent.h>
#include <game/Utility/Vector2.h>
#include <string>
#include <vector>

class Utility {
 public:
  static std::vector<std::string> readNames(const std::string& path) {
    std::vector<std::string> _names;
    DIR* dir = opendir(path.c_str());

    int i = 0;
    if (dir) {
      struct dirent* file;
      while ((file = readdir(dir)) != nullptr) {
        if (i > 1) _names.emplace_back(file->d_name);
        i++;
      }
    } else {
      std::cout << "Dir doesnt exits: " << path << std::endl;
    }

    return _names;
  }

  static void drawBorder(const Vector2& position, const Vector2& size) {
    // horizontal
    for (int i = 0; i < size.getX(); i++) {
      terminal_put(position.getX() + i, position.getY(), '=');
      terminal_put(position.getX() + i, position.getY() + size.getY() - 1, '=');
    }

    // vertical
    for (int i = 1; i < size.getY() - 1; i++) {
      terminal_put(position.getX(), position.getY() + i, '|');
      terminal_put(position.getX() + size.getX() - 1, position.getY() + i, '|');
    }
  }
  static void drawHorizontalLine(const Vector2& position, const Vector2& size) {
    for (int i = 0; i < size.getX(); i++) {
      terminal_put(position.getX() + i, position.getY(), '=');
    }
  }
  static void drawVerticalLine(const Vector2& position, const Vector2& size) {
    for (int i = 1; i < size.getY() - 1; i++) {
      terminal_put(position.getX(), position.getY() + i, '|');
    }
  }
};

#endif  // INCLUDE_GAME_UTILITY_UTILITY_H_

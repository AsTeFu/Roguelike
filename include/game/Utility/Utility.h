//
// Created by AsTeFu on 22.08.2019.
//

#ifndef INCLUDE_GAME_UTILITY_UTILITY_H_
#define INCLUDE_GAME_UTILITY_UTILITY_H_

#include <dirent.h>
#include <utilities/Vector2.h>
#include <algorithm>
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
};

#endif  // INCLUDE_GAME_UTILITY_UTILITY_H_

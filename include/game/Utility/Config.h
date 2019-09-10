//
// Created by AsTeFu on 16.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_CONFIG_H_
#define INCLUDE_GAME_UTILITY_CONFIG_H_

#include <utilities/Range.h>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "game/Utility/Display.h"
#include "utilities/Vector2.h"

using std::bind;
using std::function;
using std::make_pair;
using std::map;
using std::placeholders::_1;

class Config {
 private:
  map<std::string, function<void(const std::string&)>> _variables;

  int toInt(const std::string& str) const;
  std::vector<int> toIntVector(const std::vector<std::string>& vector);
  template<typename Type>
  Type readTwoValues(const std::vector<std::string>& strVector) const {
    return Type{toInt(strVector[0]), toInt(strVector[1])};
  }

  void readSizeTerminal(const std::string& str);
  void readBorderSize(const std::string& str);
  void readArea(const std::string& str);
  void readPointSpecialRange(const std::string& str);
  void readMaxPointsSpecial(const std::string& str);
  void readStatsSpecial(const std::string& str);
  void readRarityNames(const std::string& str);
  void readRarityChances(const std::string& str);
  void readMaxItemsChest(const std::string& str);
  void readDisableColor(const std::string& str);
  void readExperienceRange(const std::string& str);

 public:
  Config();

  static Config& getInstance();

  Vector2 sizeTerminal;
  Vector2 borderSize;
  Vector2 area;

  Range pointSpecialRange;
  int maxPointsSpecial;
  std::vector<std::string> statsSpecial;

  std::vector<std::string> rarityNames;
  std::vector<int> rarityChances;
  int maxItemsChest;

  Vector2 positionChestScene;
  Vector2 sizeChestScene;
  Vector2 roomSize;

  Color disableColor;

  Range experienceRange;
  void readRoomSize(const std::string& str);
};

#endif  // INCLUDE_GAME_UTILITY_CONFIG_H_

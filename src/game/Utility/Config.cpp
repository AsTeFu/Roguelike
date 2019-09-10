//
// Created by AsTeFu on 16.07.2019.
//

#include "game/Utility/Config.h"
#include <utilities/Color.h>
#include <game/Utility/Utility.h>
#include <utilities/StringUtility.h>
#include <fstream>
#include <string>
#include <vector>

Config& Config::getInstance() {
  static Config instance;
  return instance;
}
Config::Config() {
  _variables.insert(make_pair("sizeTerminal", bind(&Config::readSizeTerminal, this, _1)));
  _variables.insert(make_pair("borderSize", bind(&Config::readBorderSize, this, _1)));
  _variables.insert(make_pair("area", bind(&Config::readArea, this, _1)));
  _variables.insert(make_pair("pointSpecialRange", bind(&Config::readPointSpecialRange, this, _1)));
  _variables.insert(make_pair("maxPointsSpecial", bind(&Config::readMaxPointsSpecial, this, _1)));
  _variables.insert(make_pair("statsSpecial", bind(&Config::readStatsSpecial, this, _1)));
  _variables.insert(make_pair("rarityNames", bind(&Config::readRarityNames, this, _1)));
  _variables.insert(make_pair("rarityChances", bind(&Config::readRarityChances, this, _1)));
  _variables.insert(make_pair("maxItemsChest", bind(&Config::readMaxItemsChest, this, _1)));
  _variables.insert(make_pair("disableColor", bind(&Config::readDisableColor, this, _1)));
  _variables.insert(make_pair("experienceRange", bind(&Config::readExperienceRange, this, _1)));
  _variables.insert(make_pair("roomSize", bind(&Config::readRoomSize, this, _1)));

  std::string path = "Resource\\Configuration";
  std::string buffer;
  std::ifstream file(path);

  if (file.is_open()) {
    std::cout << "File configuration is opened: " << path << std::endl;

    while (getline(file, buffer)) {
      auto pair = StringUtility::split(buffer, ':');
      _variables[pair[0]](pair[1]);
    }

    file.close();
  } else {
    std::cout << "File path: " << path << " doesn't exits!" << std::endl;
  }

  positionChestScene = Vector2(sizeTerminal.getX() * area.getX() / 100, 0);
  sizeChestScene = Vector2(sizeTerminal.getX() * (100 - area.getX()) / 100, sizeTerminal.getY());
}

int Config::toInt(const std::string& str) const {
  return atoi(str.c_str());
}
std::vector<int> Config::toIntVector(const std::vector<std::string>& vector) {
  std::vector<int> newVector;
  for (const auto& str : vector) newVector.push_back(toInt(str));
  return newVector;
}

void Config::readSizeTerminal(const std::string& str) {
  sizeTerminal = readTwoValues<Vector2>(StringUtility::split(str, ','));
  std::cout << "Size Terminal: " << sizeTerminal << std::endl;
}
void Config::readBorderSize(const std::string& str) {
  borderSize = readTwoValues<Vector2>(StringUtility::split(str, ','));
  std::cout << "Border sizeShop: " << borderSize << std::endl;
}
void Config::readArea(const std::string& str) {
  area = readTwoValues<Vector2>(StringUtility::split(str, ','));
  std::cout << "Area: " << area << std::endl;
}
void Config::readPointSpecialRange(const std::string& str) {
  pointSpecialRange = readTwoValues<Range>(StringUtility::split(str, ','));
  std::cout << "Point special range: " << pointSpecialRange << std::endl;
}
void Config::readMaxPointsSpecial(const std::string& str) {
  maxPointsSpecial = toInt(str);
  std::cout << "Max points special: " << maxPointsSpecial << std::endl;
}
void Config::readStatsSpecial(const std::string& str) {
  statsSpecial = StringUtility::split(str, ',');
  for (auto& stat : statsSpecial) {
    StringUtility::trim(&stat);
  }
  std::cout << "SPECIAL: ";
  for (const auto& special : statsSpecial) std::cout << special << ", ";
  std::cout << std::endl;
}
void Config::readRarityNames(const std::string& str) {
  rarityNames = StringUtility::split(str, ',');
  std::cout << "Rarity: ";
  for (auto& name : rarityNames) {
    StringUtility::trim(&name);
  }
  for (const auto& rarity : rarityNames) std::cout << rarity << ", ";
  std::cout << std::endl;
}
void Config::readRarityChances(const std::string& str) {
  rarityChances = toIntVector(StringUtility::split(str, ','));
  std::cout << "Rarity chances: ";
  for (const auto& chance : rarityChances) std::cout << chance << ", ";
  std::cout << std::endl;
}
void Config::readMaxItemsChest(const std::string& str) {
  maxItemsChest = toInt(str);
  std::cout << "Max items in chest: " << maxItemsChest << std::endl;
}
void Config::readDisableColor(const std::string& str) {
  auto ints = toIntVector(StringUtility::split(str, ','));
  disableColor = Color(ints[0], ints[1], ints[2], ints[3]);
  std::cout << "disable color: " << Color(ints[0], ints[1], ints[2], ints[3]) << std::endl;
}
void Config::readExperienceRange(const std::string& str) {
  experienceRange = readTwoValues<Range>(StringUtility::split(str, ','));
  std::cout << "Experience range: " << experienceRange << std::endl;
}
void Config::readRoomSize(const std::string& str) {
  roomSize = readTwoValues<Vector2>(StringUtility::split(str, ','));
  std::cout << "Room size: " << experienceRange << std::endl;
}

//
// Created by AsTeFu on 16.07.2019.
//

#ifndef INCLUDE_GAME_UTILITY_CONFIGTERMINAL_H_
#define INCLUDE_GAME_UTILITY_CONFIGTERMINAL_H_

#include <string>
#include <vector>
#include "game/Utility/Display.h"
#include "game/Utility/Vector2.h"

class ConfigTerminal {
 public:
  static Vector2 sizeTerminal;
  static Vector2 startPos;
  static Vector2 borderSize;
  static int areaX;
  static int areaY;

  static Display displayPlayer;
  static Display displayWall;
  static Display displayChest;

  static int maxPointsSpecial;
  static int minPointsSpecial;
  static int pointsSpecial;
  static std::vector<std::string> statsSpecial;

  static std::vector<std::string> rarityName;
  static std::vector<int> rarityChances;
  static std::vector<int> armorClassChances;
  static int maxItemsChest;

  static Vector2 positionChestScene;
  static Vector2 sizeChestScene;
  static int maxDisplayInventory;

  // Colors
  static color_t disableColor;
  static std::vector<color_t> colorRarity;
  static std::vector<color_t> colorClass;
};

#endif  // INCLUDE_GAME_UTILITY_CONFIGTERMINAL_H_

//
// Created by AsTeFu on 16.07.2019.
//

#include "game/Utility/ConfigTerminal.h"

#include <string>
#include <vector>

Vector2 ConfigTerminal::sizeTerminal = Vector2(150, 45);
Vector2 ConfigTerminal::borderSize = Vector2(4, 2);
Vector2 ConfigTerminal::startPos = Vector2(1, 1);
int ConfigTerminal::areaX = 60;
int ConfigTerminal::areaY = 70;

Display ConfigTerminal::displayPlayer = {'@', color_from_argb(255, 230, 180, 0)};
Display ConfigTerminal::displayWall = {'#', color_from_argb(255, 255, 255, 255)};
Display ConfigTerminal::displayChest = {'X', color_from_argb(255, 255, 255, 0)};

int ConfigTerminal::minPointsSpecial = 1;
int ConfigTerminal::maxPointsSpecial = 10;
int ConfigTerminal::pointsSpecial = 40;
std::vector<std::string> ConfigTerminal::statsSpecial = {"strength",     "perception", "endurance", "charisma",
                                                         "intelligence", "agility",    "luck"};

std::vector<std::string> ConfigTerminal::rarityName = {"Usual", "Rare", "Epic", "Legendary", "Mythical", "Sublime"};
std::vector<int> ConfigTerminal::rarityChances = {50, 30, 12, 5, 2, 1};
std::vector<int> ConfigTerminal::armorClassChances = {15, 15, 55, 15};
int ConfigTerminal::maxItemsChest = 4;
std::vector<color_t> ConfigTerminal::colorRarity = {
    color_from_argb(255, 40, 180, 90),     // Usual - dark green
    color_from_argb(255, 0, 191, 255),     // Rare - blue
    color_from_argb(255, 124, 17, 136),    // Epic - purple
    color_from_argb(255, 243, 215, 75),    // Legendary - gold
    color_from_argb(255, 178, 34, 34),     // Mythical - dark red
    color_from_argb(255, 255, 218, 185)};  // Sublime - ligh grey / white

Vector2 ConfigTerminal::positionChestScene = Vector2(sizeTerminal.getX() * areaX / 100, 0);
Vector2 ConfigTerminal::sizeChestScene = Vector2(sizeTerminal.getX() * (100 - areaX) / 100, sizeTerminal.getY());
/* Vector2 ConfigTerminal::sizeChestScene = Vector2(
    ConfigTerminal::sizeTerminal.getX() * ConfigTerminal::areaX / 100 - ConfigTerminal::positionChestScene.getX() * 2,
    23); */
int ConfigTerminal::maxDisplayInventory = 5;

// Color
color_t ConfigTerminal::disableColor = color_from_argb(255, 40, 40, 40);

std::vector<color_t> ConfigTerminal::colorClass = {color_from_argb(255, 139, 69, 19),   // Heavy - brown
                                                   color_from_argb(255, 0, 0, 205),     // Magic - blue
                                                   color_from_argb(255, 255, 140, 0),   // Medium - orange
                                                   color_from_argb(255, 255, 215, 0)};  // Light - yellow

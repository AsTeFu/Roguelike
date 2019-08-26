//
// Created by AsTeFu on 14.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_
#define INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_

#include <game/Utility/DTO/PlayerDTO.h>
#include <string>
#include "game/Windows/BaseGameWindow.h"
#include "game/Windows/WindowConfig.h"

class InventoryWindow : public BaseGameWindow {
 public:
  explicit InventoryWindow(const WindowConfig& config);
  void render(const PlayerDTO& game) const;
  void printWeapon(const Weapon* weapon, int posX, int posY) const;
  void printArmor(const ArmorComponent* armor, int posX, int posY) const;
  void printArmor(const Armor& armor, const std::string& slot, int x, int* y) const;
};

#endif  // INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_

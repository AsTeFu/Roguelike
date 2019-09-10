//
// Created by AsTeFu on 14.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_
#define INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_

#include <ecs/Entity.h>
#include <game/Utility/DTO/PlayerDTO.h>
#include <string>
#include "game/Windows/BaseGameWindow.h"
#include "game/Windows/WindowConfig.h"

class InventoryWindow : public BaseGameWindow {
 private:
  int leftMargin{5};
  int topMargin{2};

  int drawPlayerStats(const Entity* player, int x, int y) const;
  int drawPlayerLevel(const Entity* player, int x, int y) const;

  string& getName(const Entity* player) const;
  int getHealth(const Entity* player) const;
  int getCash(const Entity* player) const;
  int getFood(const Entity* player) const;
  int getSteps(const Entity* player) const;

  int getLevel(const Entity* player) const;
  int getExperience(const Entity* player) const;
  int getMaxExperience(const Entity* player) const;

  int drawPlayerEquipments(const Entity* player, int x, int y) const;
  int drawEquipmentStats(const Entity* player, int x, int y) const;

 public:
  explicit InventoryWindow(const WindowConfig& config);
  void render(Entity* const player) const;
};

#endif  // INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_

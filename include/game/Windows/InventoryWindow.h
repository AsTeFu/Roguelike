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
 public:
  explicit InventoryWindow(const WindowConfig& config);
  void render(Entity* const player) const;
};

#endif  // INCLUDE_GAME_WINDOWS_INVENTORYWINDOW_H_

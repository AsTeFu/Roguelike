//
// Created by AsTeFu on 14.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_GAMEWINDOW_H_
#define INCLUDE_GAME_WINDOWS_GAMEWINDOW_H_

#include <BearLibTerminal.h>
#include <game/RoomManager/RoomManager.h>
#include <utility>

#include "game/Windows/BaseGameWindow.h"
#include "game/Windows/WindowConfig.h"

class GameWindow : public BaseGameWindow {
 public:
  explicit GameWindow(const WindowConfig& config);
  void render(RoomManager* roomManager) const;
};

#endif  // INCLUDE_GAME_WINDOWS_GAMEWINDOW_H_

//
// Created by AsTeFu on 15.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_GAMEWINDOWSMANAGER_H_
#define INCLUDE_GAME_WINDOWS_GAMEWINDOWSMANAGER_H_

#include "game/Windows/GameWindow.h"
#include "game/Windows/InventoryWindow.h"
#include "game/Windows/LogWindow.h"

class GameWindowsManager {
 private:
  int _width;
  int _height;

  GameWindow _gameWindow;
  InventoryWindow _invWindow;
  LogWindow _logWindow;

 public:
  GameWindowsManager(int blockSizeX, int blockSizeY);

  void update(RoomManager *roomManager) const;
  void start();
};

#endif  // INCLUDE_GAME_WINDOWS_GAMEWINDOWSMANAGER_H_

//
// Created by AsTeFu on 15.07.2019.
//

#include "game/Windows/GameWindowsManager.h"
#include <game/Utility/ConfigTerminal.h>

void GameWindowsManager::update(RoomManager *roomManager) const {
  _gameWindow.render(roomManager);
  _logWindow.render();
  _invWindow.render(roomManager->getPlayerInfo());
}

GameWindowsManager::GameWindowsManager(int blockSizeX, int blockSizeY)
    : _width(ConfigTerminal::sizeTerminal.getX()),
      _height(ConfigTerminal::sizeTerminal.getY()),

      _gameWindow({{_width * blockSizeX / 100, _height * blockSizeY / 100},
                   {0, 0},
                   color_from_argb(255, 255, 255, 255),
                   "GAME"}),

      _invWindow({{_width * (100 - blockSizeX) / 100, _height},
                 {_width * blockSizeX / 100, 0},
                 color_from_argb(255, 255, 255, 255),
                 "STATE"}),

      _logWindow({{_width * blockSizeX / 100, _height * (100 - blockSizeY) / 100 + 2},
                  {0, _height * blockSizeY / 100 - 1},
                  color_from_argb(255, 255, 255, 255),
                  "WHAT=IS=GOING=ON?"}) {}

void GameWindowsManager::start() {
  terminal_clear();
  // _logWindow.start();
  _gameWindow.start();
  // _invWindow.start();
}

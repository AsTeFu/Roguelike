//
// Created by AsTeFu on 15.07.2019.
//

#include "game/Windows/GameWindowsManager.h"
#include <BearLibTerminal.h>
#include <game/Utility/Config.h>

void GameWindowsManager::update(RoomManager *roomManager) const {
  _gameWindow.render(roomManager);
  _logWindow.render();
  _invWindow.render(roomManager->getCurrentPlayer());
}

GameWindowsManager::GameWindowsManager(int blockSizeX, int blockSizeY)
    : _width(Config::getInstance().sizeTerminal.getX()),
      _height(Config::getInstance().sizeTerminal.getY()),

      _gameWindow({{_width * blockSizeX / 100, _height * blockSizeY / 100}, {0, 0}, Color::White, "GAME"}),

      _invWindow({{_width * (100 - blockSizeX) / 100, _height}, {_width * blockSizeX / 100, 0}, Color::White, "STATE"}),

      _logWindow({{_width * blockSizeX / 100, _height * (100 - blockSizeY) / 100 + 2},
                  {0, _height * blockSizeY / 100 - 1},
                  Color::White,
                  "WHAT=IS=GOING=ON?"}) {}

void GameWindowsManager::start() {
  Terminal::clear();
  _logWindow.start();
  _gameWindow.start();
  _invWindow.start();
}

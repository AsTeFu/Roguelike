//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/GameWindow.h"
#include <game/RoomManager/RoomManager.h>
#include <game/Scenes/SceneRenderUtility.h>

void GameWindow::render(RoomManager* roomManager) const {
  configurateTerminal();
  for (int i = 0; i < 6; ++i) {
    Terminal::setLayer(i);
    Terminal::clearArea(_config.position, _config.size);
  }
  roomManager->update();

  Terminal::setColor(_config.color);
  SceneRenderUtility::verticalBorder(_config.position, _config.size);
  SceneRenderUtility::horizontalLine(_config.position, _config.size.getX());

  Terminal::print(_config.position.getX() + 5, _config.position.getY(), _config.name);
}
GameWindow::GameWindow(const WindowConfig& config) : BaseGameWindow(config) {
  for (int i = 0; i < 6; ++i) {
    Terminal::setLayer(i);
    Terminal::crop(_config.position, _config.size);
  }

  std::cout << "GameWindow (layer: " << _config.layer << "); Position: " << _config.position << "; Size "
            << _config.size << std::endl;
}

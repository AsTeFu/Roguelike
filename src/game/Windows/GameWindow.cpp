//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/GameWindow.h"
#include <game/RoomManager/RoomManager.h>

void GameWindow::render(RoomManager* roomManager) const {
  configurateTerminal();
  roomManager->update();

  terminal_color(_config.color);
  verticalBorder();
  // horizontalBorder();
  horizontalLine(_config.position, _config.size);

  terminal_print(_config.position.getX() + 5, _config.position.getY(), _config.name.c_str());
}
GameWindow::GameWindow(const WindowConfig& config) : BaseGameWindow(config) {
  terminal_layer(_config.layer);
  terminal_crop(_config.position.getX(), _config.position.getY(), _config.size.getX(), _config.size.getY());

  std::cout << "GameWindow (layer: " << _config.layer << "); Position: " << _config.position << "; Size "
            << _config.size << std::endl;
}

//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/LogWindow.h"
#include <game/Logs/GameLogger.h>
void LogWindow::render() const {
  configurateTerminal();
  Terminal::clearArea(_config.position, _config.size);

  GameLogger::getInstance().render(_config.position.getY() + 2);

  Terminal::print(_config.position.getX() + 4, _config.position.getY(), _config.name);
}
LogWindow::LogWindow(const WindowConfig& config) : BaseGameWindow(config) {
  // terminal_layer(_config.layer);
  // terminal_crop(_config.position.getX(), _config.position.getY(), _config._size.getX(), _config._size.getY());
  std::cout << "Log (layer: " << _config.layer << "); Position: " << _config.position << "; Size " << _config.size
            << std::endl;
}

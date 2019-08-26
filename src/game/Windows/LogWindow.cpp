//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/LogWindow.h"
#include <game/Logs/GameLogger.h>
void LogWindow::render() const {
  configurateTerminal();
  terminal_clear_area(_config.position.getX(), _config.position.getY(), _config.size.getX(), _config.size.getY());

  GameLogger::getInstance().render(_config.position.getY() + 2);

  verticalBorder();
  horizontalBorder();
  terminal_print(_config.position.getX() + 4, _config.position.getY(), _config.name.c_str());
}
LogWindow::LogWindow(const WindowConfig& config) : BaseGameWindow(config) {
  // terminal_layer(_config.layer);
  // terminal_crop(_config.position.getX(), _config.position.getY(), _config._size.getX(), _config._size.getY());
  std::cout << "Log (layer: " << _config.layer << "); Position: " << _config.position << "; Size " << _config.size
            << std::endl;
}

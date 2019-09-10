//
// Created by AsTeFu on 14.07.2019.
//

#include "game/Windows/LogWindow.h"
#include <game/Logs/GameLogger.h>
#include <game/Scenes/SceneRenderUtility.h>
void LogWindow::render() const {
  configurateTerminal();
  Terminal::clearArea(_config.position, _config.size);

  GameLogger::getInstance().render(_config.position.getY() + 2);

  SceneRenderUtility::drawBorder(_config.position, _config.size);
  Terminal::print(_config.position.getX() + 4, _config.position.getY(), _config.name);
}
LogWindow::LogWindow(const WindowConfig& config) : BaseGameWindow(config) {
  Terminal::setLayer(_config.layer);
  Terminal::crop(_config.position, _config.size);
  std::cout << "Log (layer: " << _config.layer << "); Position: " << _config.position << "; Size " << _config.size
            << std::endl;
}

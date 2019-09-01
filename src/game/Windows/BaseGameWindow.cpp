//
// Created by AsTeFu on 18.07.2019.
//

#include "game/Windows/BaseGameWindow.h"

void BaseGameWindow::configurateTerminal() const {
  Terminal::setLayer(_config.layer);
  Terminal::clearArea(_config.position, _config.size);
  Terminal::setColor(_config.color);
}

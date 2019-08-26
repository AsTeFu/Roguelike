//
// Created by AsTeFu on 18.07.2019.
//

#include "game/Windows/BaseGameWindow.h"

void BaseGameWindow::horizontalLine(const Vector2& position, const Vector2& size) const {
  for (int i = 0; i < size.getX(); i++) {
    terminal_put(position.getX() + i, position.getY(), '=');
  }
}
void BaseGameWindow::horizontalBorder() const {
  for (int i = 0; i < _config.size.getX(); i++) {
    terminal_put(_config.position.getX() + i, _config.position.getY(), '=');
    terminal_put(_config.position.getX() + i, _config.position.getY() + _config.size.getY() - 1, '=');
  }
}
void BaseGameWindow::verticalBorder() const {
  for (int i = 1; i < _config.size.getY() - 1; i++) {
    terminal_put(_config.position.getX(), _config.position.getY() + i, '|');
    terminal_put(_config.position.getX() + _config.size.getX() - 1, _config.position.getY() + i, '|');
  }
}
void BaseGameWindow::configurateTerminal() const {
  terminal_layer(_config.layer);
  terminal_clear_area(_config.position.getX(), _config.position.getY(), _config.size.getX(), _config.size.getY());
  terminal_color(_config.color);
}

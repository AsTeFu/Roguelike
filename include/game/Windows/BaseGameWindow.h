//
// Created by AsTeFu on 18.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_BASEGAMEWINDOW_H_
#define INCLUDE_GAME_WINDOWS_BASEGAMEWINDOW_H_

#include <utility>
#include "game/Windows/WindowConfig.h"

class BaseGameWindow {
 protected:
  WindowConfig _config;

  virtual void horizontalBorder() const;
  void horizontalLine(const Vector2& position, const Vector2& size) const;
  virtual void verticalBorder() const;
  void configurateTerminal() const;

 public:
  explicit BaseGameWindow(WindowConfig config) : _config(std::move(config)) {
    start();
  }
  void start() {
    terminal_layer(_config.layer);
    terminal_crop(_config.position.getX(), _config.position.getY(), _config.size.getX(), _config.size.getY());
  }
};

#endif  // INCLUDE_GAME_WINDOWS_BASEGAMEWINDOW_H_

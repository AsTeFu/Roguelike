//
// Created by AsTeFu on 18.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_BASEGAMEWINDOW_H_
#define INCLUDE_GAME_WINDOWS_BASEGAMEWINDOW_H_

#include <utilities/Terminal.h>
#include <utility>
#include "game/Windows/WindowConfig.h"

class BaseGameWindow {
 protected:
  WindowConfig _config;

  void configurateTerminal() const;

 public:
  explicit BaseGameWindow(WindowConfig config) : _config(std::move(config)) {
    start();
  }
  void start() {
    Terminal::setLayer(_config.layer);
    Terminal::crop(_config.position, _config.size);
  }
};

#endif  // INCLUDE_GAME_WINDOWS_BASEGAMEWINDOW_H_

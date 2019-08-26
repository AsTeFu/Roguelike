//
// Created by AsTeFu on 14.07.2019.
//

#ifndef INCLUDE_GAME_WINDOWS_LOGWINDOW_H_
#define INCLUDE_GAME_WINDOWS_LOGWINDOW_H_

#include "game/Windows/BaseGameWindow.h"
#include "game/Windows/WindowConfig.h"

class LogWindow : public BaseGameWindow {
 public:
  explicit LogWindow(const WindowConfig& config);
  void render() const;
};

#endif  // INCLUDE_GAME_WINDOWS_LOGWINDOW_H_

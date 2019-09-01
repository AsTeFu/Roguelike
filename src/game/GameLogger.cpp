//
// Created by AsTeFu on 17.07.2019.
//

#include "game/Logs/GameLogger.h"
#include <utilities/Terminal.h>
#include <string>

void GameLogger::add(const std::string& log) {
  _lastLogs.push_back(log);

  if (_lastLogs.size() > _lines) _lastLogs.pop_front();
}
void GameLogger::clear() {
  _lastLogs.clear();
}
void GameLogger::render(int posY) const {
  for (const std::string& log : _lastLogs) {
    Terminal::print(2, posY++, log);
  }
}
GameLogger& GameLogger::getInstance() {
  static GameLogger instance(10);
  return instance;
}

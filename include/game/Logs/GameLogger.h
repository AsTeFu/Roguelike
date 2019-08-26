//
// Created by AsTeFu on 17.07.2019.
//

#ifndef INCLUDE_GAME_LOGS_GAMELOGGER_H_
#define INCLUDE_GAME_LOGS_GAMELOGGER_H_

#include <BearLibTerminal.h>
#include <deque>
#include <string>

class GameLogger {
 private:
  size_t _lines;
  std::deque<std::string> _lastLogs;

 public:
  explicit GameLogger(int lines) : _lines(lines) {}
  void add(const std::string& log);
  void clear();
  void render(int posY) const;

  static GameLogger& getInstance();
};

#endif  // INCLUDE_GAME_LOGS_GAMELOGGER_H_

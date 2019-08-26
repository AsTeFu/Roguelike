//
// Created by AsTeFu on 16.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_ENDGAMESCENE_H_
#define INCLUDE_GAME_SCENES_ENDGAMESCENE_H_

#include <BearLibTerminal.h>
#include <string>
#include <utility>
#include <vector>
#include "game/Scenes/SceneManager.h"
#include "game/Utility/ConfigTerminal.h"
#include "game/Utility/DTO/PlayerDTO.h"
#include "game/Windows/WindowConfig.h"

class Score {
 public:
  std::string key;
  int value;
  Score(std::string key, int value) : key(std::move(key)), value(value) {}
  bool operator<(const Score& rhs) const;
  bool operator>(const Score& rhs) const;
  bool operator<=(const Score& rhs) const;
  bool operator>=(const Score& rhs) const;
};

class EndGameScene : public Scene {
 private:
  PlayerDTO* player;
  std::vector<Score> scores;

 public:
  EndGameScene(Context* const context, SceneManager* sceneManager);
  void start(SceneManager* sceneManager) override;
  void render() override;
  void update(SceneManager* sceneManager) override;
  void read();
  void write();
};

#endif  // INCLUDE_GAME_SCENES_ENDGAMESCENE_H_

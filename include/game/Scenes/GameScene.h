//
// Created by AsTeFu on 22.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_GAMESCENE_H_
#define INCLUDE_GAME_SCENES_GAMESCENE_H_

#include <game/Player/Special.h>
#include <game/Utility/ConfigTerminal.h>
#include "game/Scenes/SceneManager.h"
#include "game/Windows/GameWindowsManager.h"

class GameScene : public Scene {
 private:
  RoomManager roomManager;
  GameWindowsManager _windowsManager;

 public:
  GameScene(Context* context, SceneManager* sceneManager)
      : Scene(context, sceneManager),
        roomManager(sceneManager),
        _windowsManager(ConfigTerminal::areaX, ConfigTerminal::areaY) {}
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;

  void newGame();
  void continueGame();
  void setSpicial(const Special& special);
};

#endif  // INCLUDE_GAME_SCENES_GAMESCENE_H_

//
// Created by AsTeFu on 11.08.2019.
//

#ifndef INCLUDE_GAME_SCENES_INPUTNAMESCENE_H_
#define INCLUDE_GAME_SCENES_INPUTNAMESCENE_H_

#include "game/Scenes/SceneManager.h"

class InputNameScene : public Scene {
 private:
  char name[32];
 public:
  InputNameScene(Context *const context, SceneManager *sceneManager);
  void render() override;
  void update(SceneManager *sceneManager) override;
};

#endif  // INCLUDE_GAME_SCENES_INPUTNAMESCENE_H_

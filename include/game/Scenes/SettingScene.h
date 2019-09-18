//
// Created by AsTeFu on 22.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_SETTINGSCENE_H_
#define INCLUDE_GAME_SCENES_SETTINGSCENE_H_

#include <utilities/Vector2.h>
#include "game/Scenes/SceneManager.h"

class SettingScene : public Scene {
 private:
  bool mode{false};
 public:
  SettingScene(Context* const context, SceneManager* sceneManager);
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_SETTINGSCENE_H_

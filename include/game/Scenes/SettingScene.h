//
// Created by AsTeFu on 22.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_SETTINGSCENE_H_
#define INCLUDE_GAME_SCENES_SETTINGSCENE_H_

#include <game/Utility/Vector2.h>
#include "game/Scenes/SceneManager.h"

class SettingScene : public Scene {
 public:
  void update(SceneManager* context) override;
  void start(SceneManager* context) override;
  void end(SceneManager* context) override;
  void render() override;

  // DECLARE_GET_INSTANCE(SettingScene)
};

#endif  // INCLUDE_GAME_SCENES_SETTINGSCENE_H_

//
// Created by AsTeFu on 27.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_CHESTSCENE_H_
#define INCLUDE_GAME_SCENES_CHESTSCENE_H_

#include <game/Utility/DTO/ChestDTO.h>
#include <string>
#include "game/Scenes/SceneManager.h"

class ChestScene : public Scene {
 private:
  ChestDTO* gameDTO;
  int _currentItem{};

  void decrease();
  void increase();
  void equipMenu(SceneManager* context);
  void takeMenu(SceneManager* context);

 public:
  ChestScene(Context* context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_CHESTSCENE_H_

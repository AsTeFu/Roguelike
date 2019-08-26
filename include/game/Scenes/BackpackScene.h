//
// Created by AsTeFu on 29.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_BACKPACKSCENE_H_
#define INCLUDE_GAME_SCENES_BACKPACKSCENE_H_

#include <game/Utility/DTO/BackpackDTO.h>
#include <vector>
#include "game/Scenes/SceneManager.h"

class BackpackScene : public Scene {
 private:
  BackpackDTO* backpack;
  int _currentItem;
  // std::vector<int> localItemOffsets{};

  void decrease();
  void increase();
  void equipMenu(SceneManager* sceneManager);
  void deleteMenu(SceneManager* sceneManager);

 public:
  BackpackScene(Context* const context, SceneManager* sceneManager);
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* context) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_BACKPACKSCENE_H_

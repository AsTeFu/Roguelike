//
// Created by AsTeFu on 20.08.2019.
//

#ifndef INCLUDE_GAME_SCENES_ABILITYSCENE_H_
#define INCLUDE_GAME_SCENES_ABILITYSCENE_H_

#include <game/Components/PlayerComponents/AbilitiesComponent.h>
#include <game/Utility/DTO/EnhanceDTO.h>
#include <string>
#include <vector>
#include "game/Scenes/SceneManager.h"

// TODO(ATF): устаревший код

enum Side { LeftSide, RightSide };

class AbilityScene : public Scene {
 private:
  int _currentItem;
  Side _side;
  EnhanceDTO *enhanceDto;
  std::vector<std::string> _desription;

  std::vector<Ability> _abilities;

  void leftRender();
  void rightRender();

 public:
  AbilityScene(Context *const context, SceneManager *sceneManager);
  void update(SceneManager *sceneManager) override;
  void render() override;
  void start(SceneManager *sceneManager) override;
};

#endif  // INCLUDE_GAME_SCENES_ABILITYSCENE_H_

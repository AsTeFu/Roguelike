//
// Created by AsTeFu on 11.08.2019.
//

#ifndef INCLUDE_GAME_SCENES_INPUTNAMESCENE_H_
#define INCLUDE_GAME_SCENES_INPUTNAMESCENE_H_

#include <utilities/Range.h>
#include <string>
#include "game/Scenes/SceneManager.h"

class InputNameScene : public Scene {
 private:
  std::string name;
  Vector2 positionInput{32, 12};
  Vector2 positionLabel{10, 3};
  Vector2 positonPica;
  Vector2 sizeLabel;
  int leftMargin{5};
  int topMargin{3};
  Range rangeLen{4, 12};

 public:
  InputNameScene(Context *const context, SceneManager *sceneManager);
  void render() override;
  void update(SceneManager *sceneManager) override;
  void start(SceneManager *sceneManager) override;
  void drawPica() const;
};

#endif  // INCLUDE_GAME_SCENES_INPUTNAMESCENE_H_

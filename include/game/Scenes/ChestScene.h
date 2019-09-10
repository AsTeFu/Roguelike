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
  ChestDTO* game;
  int _currentItem{};

  Vector2 position;
  Vector2 size;
  int leftMargin{5};
  int topMargin{2};
  const std::string cursor{"=>"};

  void upward();
  void downward();
  void equipMenu();
  void takeMenu();

  int renderItems(int x, int y) const;
  int renderWeaponPlayer(int x, int y) const;
  int renderArmorPlayer(int x, int y) const;
  void updateCursor();
  bool isAvailableSpace() const;

 public:
  ChestScene(Context* context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_CHESTSCENE_H_

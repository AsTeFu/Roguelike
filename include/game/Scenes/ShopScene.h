//
// Created by AsTeFu on 19.08.2019.
//

#ifndef INCLUDE_GAME_SCENES_SHOPSCENE_H_
#define INCLUDE_GAME_SCENES_SHOPSCENE_H_

#include <game/Utility/DTO/ChestDTO.h>
#include <game/Utility/DTO/ShopDTO.h>
#include "game/Scenes/SceneManager.h"

class ShopScene : public Scene {
 private:
  ShopDTO* gameDTO;
  int _currentItem;

  void decrease();
  void increase();
  void buyItem(SceneManager* sceneManager);
  void saleItem(SceneManager* sceneManager);

 public:
  ShopScene(Context* context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_SHOPSCENE_H_

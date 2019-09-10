//
// Created by AsTeFu on 29.07.2019.
//

#ifndef INCLUDE_GAME_SCENES_BACKPACKSCENE_H_
#define INCLUDE_GAME_SCENES_BACKPACKSCENE_H_

#include <game/Utility/DTO/BackpackDTO.h>
#include <string>
#include <vector>
#include "game/Scenes/SceneManager.h"

class BackpackScene : public Scene {
 private:
  BackpackDTO* backpack;
  int _currentItem;

  std::string cursor{"=>"};
  int leftMargin{5};
  int topMargin{2};
  size_t lenStatName = 16;
  Vector2 positionInv;
  Vector2 sizeInv;
  Vector2 positionSpecial;
  Vector2 sizeSpecial;

  void downward();
  void upward();
  void equipMenu();
  void deleteMenu();

  void renderCursor(int x, int y) const;
  int renderWeapon(int x, int y) const;
  int renderArmors(int x, int y) const;
  int renderPlayerInventory(int x, int y) const;
  int renderSpecial(int x, int y) const;
  int renderStat(int x, int y, const std::string& stat) const;
  std::string getNameStat(const std::string& stat) const;

  void renderInventory() const;
  void renderSpecial() const;

  bool isInventory() const;
  int getInventoryItemIndex() const;

 public:
  BackpackScene(Context* const context, SceneManager* sceneManager);
  void start(SceneManager* sceneManager) override;
  void update(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_BACKPACKSCENE_H_

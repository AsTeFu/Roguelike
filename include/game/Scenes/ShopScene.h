//
// Created by AsTeFu on 19.08.2019.
//

#ifndef INCLUDE_GAME_SCENES_SHOPSCENE_H_
#define INCLUDE_GAME_SCENES_SHOPSCENE_H_

#include <game/Utility/DTO/ChestDTO.h>
#include <game/Utility/DTO/ShopDTO.h>
#include <string>
#include "game/Scenes/SceneManager.h"

class ShopScene : public Scene {
 private:
  ShopDTO* gameDTO;
  int _currentItem;

  int loyaltyBuy{10};
  int loyaltySale{5};

  Vector2 positionShop;
  Vector2 sizeShop;
  Vector2 positionRightside;
  Vector2 sizeRightside;
  int leftMargin{5};
  int topMargin{2};
  std::string cursor{"=>"};

  void downward();
  void upward();

  void buyItem();
  void saleItem();
  int getMaxCursorPosition() const;

  bool canBuy() const;
  bool canSale() const;
  int getCostBuy(const InventoryItem* item) const;
  int getCostSale(InventoryItem* item) const;
  void updateCursorAfterBuy();
  void updateCursorAfterSale(int currItem);

  void renderShop() const;
  void renderRightSide() const;

  void startRenderShop() const;
  void startRenderRightside() const;

  void drawCursor(int x, int y) const;
  void switchColor(InventoryItem* item, int cost) const;

  void drawCostBuy(int x, int y, InventoryItem* item) const;
  void drawCostSale(int x, int y, InventoryItem* item) const;
  int drawAvailableSpace(int x, int y) const;
  int drawTraderInfo(int x, int y) const;
  int drawPlayerInfo(int x, int y) const;
  void drawPlayerEquopments(int x, int y) const;

 public:
  ShopScene(Context* context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
  void update(SceneManager* sceneManager) override;
  void start(SceneManager* sceneManager) override;
  void end(SceneManager* sceneManager) override;
  void render() override;
};

#endif  // INCLUDE_GAME_SCENES_SHOPSCENE_H_

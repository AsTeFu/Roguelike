//
// Created by AsTeFu on 19.08.2019.
//

#include "game/Scenes/ShopScene.h"
#include <game/Items/FoodItem.h>
#include <game/Items/MedkitItem.h>
#include <game/Logs/GameLogger.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/DTO/ShopDTO.h>
#include <game/Utility/Input.h>
#include <utilities/MathUtility.h>
#include <algorithm>

void ShopScene::start(SceneManager* sceneManager) {
  gameDTO = sceneManager->getContext()->getObject<ShopDTO>();
  if (!gameDTO->shopComponent->items.empty() || !gameDTO->getComponent<InventoryComponent>()->items.empty())
    _currentItem = 0;

  auto& config = Config::getInstance();

  positionShop = {};
  sizeShop = {config.sizeTerminal.getX() * config.area.getX() / 100,
              config.sizeTerminal.getY() * config.area.getY() / 100};

  positionRightside = {config.sizeTerminal.getX() * config.area.getX() / 100, 0};
  sizeRightside = {config.sizeTerminal.getX() * (100 - config.area.getX()) / 100, config.sizeTerminal.getY()};
}
void ShopScene::end(SceneManager* sceneManager) {}
void ShopScene::update(SceneManager* sceneManager) {
  if (Input::getKey(KeyCode::Escape)) sceneManager->switchScene("Game");

  if (_currentItem == -1) return;

  if (Input::getKey(KeyCode::UpArrow)) upward();
  if (Input::getKey(KeyCode::DownArrow)) downward();

  if (Input::getKey(KeyCode::Space)) buyItem();
  if (Input::getKey(KeyCode::Space)) saleItem();
}

void ShopScene::downward() {
  _currentItem = MathUtility::clamp(_currentItem + 1, 0, getMaxCursorPosition());
}
void ShopScene::upward() {
  _currentItem = MathUtility::clamp(_currentItem - 1, 0, getMaxCursorPosition());
}
int ShopScene::getMaxCursorPosition() const {
  return static_cast<int>(gameDTO->getComponent<InventoryComponent>()->items.size()) +
         static_cast<int>(gameDTO->shopComponent->items.size()) - 1;
}

void ShopScene::buyItem() {
  if (!canBuy()) return;
  auto item = gameDTO->shopComponent->items[_currentItem].get();

  int cost = getCostBuy(item);
  if (cost > gameDTO->getComponent<WalletComponent>()->cash) return;
  gameDTO->getComponent<WalletComponent>()->cash -= cost;

  item->takeItem(gameDTO->player);
  gameDTO->shopComponent->deleteItem(_currentItem);
  gameDTO->shopComponent->loyalty += loyaltyBuy;

  updateCursorAfterBuy();
}
void ShopScene::saleItem() {
  if (!canSale()) return;
  int currItem = _currentItem - static_cast<int>(gameDTO->shopComponent->items.size());
  int cost = getCostSale(gameDTO->getComponent<InventoryComponent>()->items[currItem].get());

  gameDTO->getComponent<WalletComponent>()->cash += cost;
  gameDTO->getComponent<InventoryComponent>()->deleteItem(currItem);
  gameDTO->shopComponent->loyalty += loyaltySale;

  updateCursorAfterSale(currItem);
}

bool ShopScene::canBuy() const {
  if (_currentItem >= static_cast<int>(gameDTO->shopComponent->items.size())) return false;
  auto inventory = gameDTO->getComponent<InventoryComponent>();
  return inventory->maxItems != inventory->items.size();
}
bool ShopScene::canSale() const {
  if (gameDTO->shopComponent->items.empty() && gameDTO->getComponent<InventoryComponent>()->items.empty()) return false;
  return _currentItem - static_cast<int>(gameDTO->shopComponent->items.size()) >= 0;
}
int ShopScene::getCostSale(InventoryItem* item) const {
  int cost = item->cost / 2 + gameDTO->getComponent<SpecialComponent>()->getValue(CHARISMA) * 2;
  cost /= (100 + gameDTO->shopComponent->loyalty) / 100;
  return cost;
}
int ShopScene::getCostBuy(const InventoryItem* item) const {
  int cost = item->cost - gameDTO->getComponent<SpecialComponent>()->getValue(CHARISMA) * 2;
  cost /= (100 + gameDTO->shopComponent->loyalty) / 100;
  return cost;
}
void ShopScene::updateCursorAfterSale(int currItem) {
  if (_currentItem > 0 && gameDTO->getComponent<InventoryComponent>()->items.size() == static_cast<size_t>(currItem))
    _currentItem--;
}
void ShopScene::updateCursorAfterBuy() {
  if (_currentItem > 0 && gameDTO->shopComponent->items.size() == static_cast<size_t>(_currentItem)) _currentItem--;
}

void ShopScene::render() {
  // if (_currentItem == -1) return;
  renderShop();
  renderRightSide();
  SceneRenderUtility::verticalBorder(positionRightside, sizeRightside);
}
void ShopScene::renderRightSide() const {
  startRenderRightside();

  int x = positionRightside.getX() + leftMargin;
  int y = positionRightside.getY() + topMargin;

  SceneRenderUtility::horizontalBorder(positionRightside, sizeRightside);

  // Trader info
  y = drawTraderInfo(x, y) + 3;

  SceneRenderUtility::horizontalLine(positionRightside.getX(), y, sizeRightside.getX());
  Terminal::print(x, y, "YOU");
  y = drawPlayerInfo(x, y + 2) + 1;

  SceneRenderUtility::horizontalLine(positionRightside.getX(), y, sizeRightside.getX());
  Terminal::print(x, y, "EQUIPMENTS");

  drawPlayerEquopments(x, y + 2);
}
void ShopScene::drawPlayerEquopments(int x, int y) const {
  y += gameDTO->getComponent<WeaponComponent>()->weapon->printItemExtended(x, y) + 1;
  for (const auto& equipment : gameDTO->getComponent<ArmorComponent>()->equipments) {
    y += equipment.second->printItemExtended(x, y) + 1;
  }
}
int ShopScene::drawPlayerInfo(int x, int y) const {
  Terminal::printf(x, y++, "Money: %d", gameDTO->getComponent<WalletComponent>()->cash);
  Terminal::printf(x, y++, "Charisma: %d", gameDTO->getComponent<SpecialComponent>()->getValue(CHARISMA));
  return y;
}
int ShopScene::drawTraderInfo(int x, int y) const {
  Terminal::printf(x, positionShop.getY(), "TRADER");
  Terminal::printf(x, y++, "Shopname: %s", "Magnit");
  Terminal::printf(x, y++, "Loyalty: %d", gameDTO->shopComponent->loyalty);
  return y;
}
void ShopScene::startRenderRightside() const {
  Terminal::setLayer(1);
  Terminal::clearArea(positionRightside, sizeRightside);
  Terminal::setLayer(9);
  Terminal::crop(positionRightside, sizeRightside);
  Terminal::clearArea(positionRightside, sizeRightside);
}
void ShopScene::renderShop() const {
  startRenderShop();

  int x = positionShop.getX() + leftMargin;
  int y = positionShop.getY() + topMargin;

  Terminal::print(x, y, "Cost\t\tGoods");
  y += 2;

  int costArea = 12;
  int i = 0;
  for (const auto& item : gameDTO->shopComponent->items) {
    if (_currentItem == i) drawCursor(x, y);
    drawCostBuy(x, y, item.get());

    Terminal::setColor(Color::White);
    y += item->printItemExtended(x + costArea, y) + 1;
    i++;
  }

  // Inventory
  y += 2;
  SceneRenderUtility::horizontalLine(positionShop.getX(), y, sizeShop.getX());
  Terminal::print(positionShop.getX() + 4, y, "Inventory");

  SceneRenderUtility::drawBorder(positionShop, sizeShop);
  Terminal::print(x, positionShop.getY(), "SHOP");

  y = drawAvailableSpace(x, y + 2) + 1;

  for (const auto& item : gameDTO->getComponent<InventoryComponent>()->items) {
    if (_currentItem == i) drawCursor(x, y);
    drawCostSale(x, y, item.get());

    y += item->printItemExtended(x + costArea, y) + 1;
    i++;
  }
}
int ShopScene::drawAvailableSpace(int x, int y) const {
  auto inventory = gameDTO->getComponent<InventoryComponent>();
  Terminal::printf(x, y, "Available space: %d/%d", inventory->items.size(), inventory->maxItems);
  return y + 1;
}
void ShopScene::drawCostBuy(int x, int y, InventoryItem* item) const {
  int cost = getCostBuy(item);
  switchColor(item, cost);
  Terminal::printf(x, y, "%d$", cost);
}
void ShopScene::drawCostSale(int x, int y, InventoryItem* item) const {
  int cost = getCostSale(item);
  Terminal::printf(x, y, "[color=yellow]%d$", cost);
}
void ShopScene::switchColor(InventoryItem* item, int cost) const {
  if (cost > gameDTO->getComponent<WalletComponent>()->cash)
    Terminal::setColor(Color::Red);
  else
    Terminal::setColor(Color::Yellow);
}
void ShopScene::drawCursor(int x, int y) const {
  Terminal::print(x - static_cast<int>(cursor.size()) - 1, y, cursor);
}
void ShopScene::startRenderShop() const {
  Terminal::setLayer(0);
  Terminal::clearArea(positionShop, sizeShop);
  Terminal::setLayer(8);
  Terminal::crop(positionShop, sizeShop);
  Terminal::clearArea(positionShop, sizeShop);
  Terminal::setColor(Color::White);
}

//
// Created by AsTeFu on 27.07.2019.
//

#include "game/Scenes/ChestScene.h"
#include <ecs/Entity.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include <game/Items/CoinItem.h>
#include <game/Items/FoodItem.h>
#include <game/Items/MedkitItem.h>
#include <game/Scenes/SceneRenderUtility.h>
#include <game/Utility/DTO/ChestDTO.h>
#include <utilities/Color.h>
#include <utilities/MathUtility.h>
#include <utilities/Terminal.h>
#include <algorithm>
#include <string>
#include "game/Scenes/GameScene.h"
#include "game/Utility/Config.h"
#include "game/Utility/Input.h"

void ChestScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::Escape)) sceneManager->switchScene("Game");

  if (_currentItem == -1) return;

  if (Input::getKeyDown(KeyCode::UpArrow)) upward();
  if (Input::getKeyDown(KeyCode::DownArrow)) downward();

  if (Input::getKeyDown(KeyCode::Space)) equipMenu();
  if (Input::getKeyDown(KeyCode::E)) takeMenu();
}

void ChestScene::equipMenu() {
  auto item = game->chestComponent->items[_currentItem].get();
  item->equipItem(game->player, game->chestComponent, _currentItem);
  updateCursor();
}
void ChestScene::updateCursor() {
  if (static_cast<int>(game->chestComponent->items.size()) == _currentItem) _currentItem--;
  if (game->chestComponent->items.empty()) _currentItem = -1;
}

void ChestScene::takeMenu() {
  if (isAvailableSpace()) {
    auto item = game->chestComponent->items[_currentItem].get();
    item->takeItem(game->player);
    game->chestComponent->deleteItem(_currentItem);

    updateCursor();
  }
}
bool ChestScene::isAvailableSpace() const {
  return game->getComponent<InventoryComponent>()->items.size() < game->getComponent<InventoryComponent>()->maxItems;
}

void ChestScene::upward() {
  _currentItem = MathUtility::clamp(_currentItem - 1, 0, static_cast<int>(game->chestComponent->items.size()) - 1);
}
void ChestScene::downward() {
  _currentItem = MathUtility::clamp(_currentItem + 1, 0, static_cast<int>(game->chestComponent->items.size()) - 1);
}

void ChestScene::start(SceneManager* sceneManager) {
  game = sceneManager->getContext()->getObject<ChestDTO>();
  if (!game->chestComponent->items.empty()) _currentItem = 0;

  position = Config::getInstance().positionChestScene;
  size = Config::getInstance().sizeChestScene;
}

void ChestScene::render() {
  Terminal::setLayer(1);
  Terminal::clearArea(position, size);
  Terminal::setLayer(8);
  Terminal::clearArea(position, size);
  Terminal::setColor(Color::White);

  int x = position.getX() + leftMargin;
  int y = position.getY() + topMargin;

  if (_currentItem == -1) Terminal::print(x, y, "Chest is empty");

  y = renderItems(x, y) + 1;

  SceneRenderUtility::horizontalLine(position.getX(), position.getY() + y, size.getX());
  Terminal::print(position.getX() + leftMargin, position.getY() + y, "EQUIPMENTS");

  SceneRenderUtility::drawBorder(position, size);

  Terminal::print(position.getX() + leftMargin, position.getY(), "CHEST");

  y = renderWeaponPlayer(x, y + 2);
  y = renderArmorPlayer(x, y);

  Terminal::setColor(Color::White);
  Terminal::print(x, size.getY() - 2, "Equip - Space\tTake - E\tExit - ESC");
}
int ChestScene::renderArmorPlayer(int x, int y) const {
  auto armor = game->player->Entity::getComponent<ArmorComponent>();
  for (const auto& pair : armor->equipments) y += pair.second->printItemExtended(x, y) + 1;
  return y;
}
int ChestScene::renderWeaponPlayer(int x, int y) const {
  y += game->player->Entity::getComponent<WeaponComponent>()->weapon->printItemExtended(x, y) + 1;
  return y;
}
int ChestScene::renderItems(int x, int y) const {
  int i = 0;
  for (const auto& item : game->chestComponent->items) {
    if (_currentItem == i) Terminal::print(x - static_cast<int>(cursor.size()) - 1, y, "=>");
    y += item->printItemExtended(x, y) + 1;
    i++;
  }
  y++;
  return y;
}

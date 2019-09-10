//
// Created by AsTeFu on 29.07.2019.
//

#include "game/Scenes/BackpackScene.h"
#include <game/Scenes/SceneRenderUtility.h>
#include <utilities/Color.h>
#include <utilities/Terminal.h>
#include <algorithm>
#include <string>
#include "game/Utility/Input.h"

BackpackScene::BackpackScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {}
void BackpackScene::update(SceneManager* sceneManager) {
  if (Input::getKeyDown(KeyCode::Escape) || Input::getKey(KeyCode::I)) sceneManager->switchScene("Game");

  if (Input::getKeyDown(KeyCode::UpArrow)) upward();
  if (Input::getKeyDown(KeyCode::DownArrow)) downward();
  if (Input::getKeyDown(KeyCode::C)) deleteMenu();

  if (Input::getKeyDown(KeyCode::Space)) equipMenu();
}
void BackpackScene::start(SceneManager* sceneManager) {
  backpack = _context->getObject<BackpackDTO>();
  _currentItem = 0;

  positionInv = Vector2::ZERO;
  sizeInv = {Config::getInstance().sizeTerminal.getX() * Config::getInstance().area.getX() / 100,
             Config::getInstance().sizeTerminal.getY() * Config::getInstance().area.getY() / 100};

  positionSpecial = {Config::getInstance().sizeTerminal.getX() * Config::getInstance().area.getX() / 100, 0};
  sizeSpecial = {Config::getInstance().sizeTerminal.getX() * (100 - Config::getInstance().area.getX()) / 100,
                 Config::getInstance().sizeTerminal.getY()};
}
void BackpackScene::render() {
  renderInventory();
  renderSpecial();
}
void BackpackScene::renderSpecial() const {
  Terminal::setLayer(1);
  Terminal::clearArea(positionSpecial, sizeSpecial);
  Terminal::setLayer(9);
  Terminal::clearArea(positionSpecial, sizeSpecial);
  Terminal::setColor(Color::White);

  int x = positionSpecial.getX() + leftMargin;
  int y = positionSpecial.getY() + topMargin;

  SceneRenderUtility::drawBorder(positionSpecial, sizeSpecial);
  Terminal::print(x, positionSpecial.getY(), "SPECIAL");

  y = renderSpecial(x, y);
}
void BackpackScene::renderInventory() const {
  Terminal::setLayer(0);
  Terminal::clearArea(positionInv, sizeInv);
  Terminal::setLayer(9);
  Terminal::clearArea(positionInv, sizeInv);
  Terminal::setColor(Color::White);

  int x = positionInv.getX() + leftMargin;
  int y = positionInv.getY() + topMargin;

  SceneRenderUtility::horizontalLine(positionInv, sizeInv.getX());
  SceneRenderUtility::verticalBorder(positionInv, sizeInv);
  Terminal::print(x, positionInv.getY(), "EQUIPMENTS");

  Terminal::print(x, y++, "Weapon:");
  x += leftMargin;

  if (_currentItem == 0) renderCursor(x, y);
  y = renderWeapon(x, y) + 1;

  Terminal::print(x - leftMargin, y++, "Armors:");
  y = renderArmors(x, y) + 1;

  SceneRenderUtility::horizontalLine(positionInv.getX(), positionInv.getY() + y, sizeInv.getX());
  Terminal::print(x, y, "INVENTORY");
  y += 2;

  Terminal::printf(x - leftMargin, y, "Available space: %d/%d",
                   backpack->getComponent<InventoryComponent>()->items.size(),
                   backpack->getComponent<InventoryComponent>()->maxItems);

  y = renderPlayerInventory(x, y + 2);
}
int BackpackScene::renderSpecial(int x, int y) const {
  for (const auto& stat : Config::getInstance().statsSpecial) y = renderStat(x, y, stat) + 2;
  return y;
}
int BackpackScene::renderStat(int x, int y, const string& stat) const {
  std::string upperEffect = getNameStat(stat);

  auto special = backpack->getComponent<SpecialComponent>();
  int value = special->special.getValue(stat);
  int bonusValue = special->addictiveSpecial.getValue(stat);

  if (bonusValue)
    Terminal::printf(x, y, "%s%d+%d", upperEffect.c_str(), value, bonusValue);
  else
    Terminal::printf(x, y, "%s%d", upperEffect.c_str(), value);

  return y;
}
std::string BackpackScene::getNameStat(const string& stat) const {
  std::string statName;
  for (size_t i = 0; i < lenStatName; ++i) {
    if (i < stat.size())
      statName.push_back(toupper(stat[i]));
    else if (i == stat.size())
      statName.push_back(':');
    else
      statName.push_back(' ');
  }
  return statName;
}
int BackpackScene::renderPlayerInventory(int x, int y) const {
  int i = static_cast<int>(backpack->getComponent<ArmorComponent>()->equipments.size()) + 1;
  for (const auto& item : backpack->getComponent<InventoryComponent>()->items) {
    if (_currentItem == i) renderCursor(x, y);
    y += item->printItemExtended(x, y) + 1;
    i++;
  }
  return y;
}
int BackpackScene::renderArmors(int x, int y) const {
  int i = 1;
  for (const auto& pair : backpack->getComponent<ArmorComponent>()->equipments) {
    if (_currentItem == i) renderCursor(x, y);
    y += pair.second->printItemExtended(x, y) + 1;
    i++;
  }
  return y;
}
int BackpackScene::renderWeapon(int x, int y) const {
  y += backpack->getComponent<WeaponComponent>()->weapon->printItemExtended(x, y) + 1;
  return y;
}
void BackpackScene::renderCursor(int x, int y) const {
  Terminal::print(x - static_cast<int>(cursor.size()), y, cursor);
}
void BackpackScene::downward() {
  _currentItem = std::min<int>(backpack->getComponent<InventoryComponent>()->items.size() +
                                   backpack->getComponent<ArmorComponent>()->equipments.size(),
                               _currentItem + 1);
}
void BackpackScene::upward() {
  _currentItem = std::max(0, _currentItem - 1);
}

void BackpackScene::equipMenu() {
  if (isInventory()) return;
  int currItem = getInventoryItemIndex();
  backpack->getComponent<InventoryComponent>()->items[currItem]->equipItem(backpack->player, currItem);
}
int BackpackScene::getInventoryItemIndex() const {
  return _currentItem - static_cast<int>(backpack->getComponent<ArmorComponent>()->equipments.size()) - 1;
}
bool BackpackScene::isInventory() const {
  return _currentItem - static_cast<int>(backpack->getComponent<ArmorComponent>()->equipments.size()) <= 0;
}

void BackpackScene::deleteMenu() {
  auto armors = backpack->getComponent<ArmorComponent>();
  if (_currentItem - static_cast<int>(armors->equipments.size()) <= 0) return;
  int currItem = _currentItem - static_cast<int>(armors->equipments.size()) - 1;

  auto inventory = backpack->getComponent<InventoryComponent>();
  inventory->deleteItem(currItem);

  if (inventory->items.size() == static_cast<size_t>(currItem)) _currentItem--;
}

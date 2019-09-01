//
// Created by AsTeFu on 19.08.2019.
//

#include "game/Scenes/ShopScene.h"
#include <game/Items/FoodItem.h>
#include <game/Items/MedkitItem.h>
#include <game/Logs/GameLogger.h>
#include <game/Utility/DTO/ShopDTO.h>
#include <game/Utility/Input.h>
#include <algorithm>

void ShopScene::start(SceneManager* sceneManager) {
  gameDTO = sceneManager->getContext()->getObject<ShopDTO>();
  if (!gameDTO->shopComponent->items.empty() || !gameDTO->inventoryComponent->items.empty()) _currentItem = 0;
}
void ShopScene::update(SceneManager* sceneManager) {
  if (Input::getKey(KeyCode::Escape)) {
    Terminal::clearArea(Config::getInstance().positionChestScene, Config::getInstance().sizeChestScene);
    sceneManager->switchScene("Game");
  }

  if (_currentItem == -1) return;

  if (Input::getKey(KeyCode::UpArrow)) increase();
  if (Input::getKey(KeyCode::DownArrow)) decrease();

  if (Input::getKey(KeyCode::Space)) buyItem(sceneManager);
  if (Input::getKey(KeyCode::Space)) saleItem(sceneManager);
}

void ShopScene::decrease() {
  _currentItem = std::min<int>(gameDTO->inventoryComponent->items.size() + gameDTO->shopComponent->items.size() - 1,
                               _currentItem + 1);
}
void ShopScene::increase() {
  _currentItem = std::max(0, _currentItem - 1);
}
void ShopScene::buyItem(SceneManager* sceneManager) {
  if (_currentItem >= static_cast<int>(gameDTO->shopComponent->items.size())) return;
  if (gameDTO->inventoryComponent->maxItems == gameDTO->inventoryComponent->items.size()) return;

  auto item = gameDTO->shopComponent->items[_currentItem].get();

  int cost = item->cost - gameDTO->specialComponent->getValue(CHARISMA) * 2;
  cost /= (100 + gameDTO->shopComponent->loyalty) / 100;

  if (cost > gameDTO->walletComponent->cash) return;
  gameDTO->walletComponent->cash -= cost;

  if (item->itemType == ArmorType) {
    auto* armor = new Armor(*dynamic_cast<Armor*>(item));
    gameDTO->inventoryComponent->items.push_back(std::unique_ptr<Armor>(armor));
  }
  if (item->itemType == WeaponType) {
    auto* weapon = new Weapon(*dynamic_cast<Weapon*>(item));
    gameDTO->inventoryComponent->items.push_back(std::unique_ptr<Weapon>(weapon));
  }
  if (item->itemType == FoodType) {
    gameDTO->starvationComponent->currentFood += dynamic_cast<FoodItem*>(item)->food;
  }
  if (item->itemType == MedkitType) {
    gameDTO->healthComponent->health += dynamic_cast<MedkitItem*>(item)->health;
  }

  gameDTO->shopComponent->deleteItem(_currentItem);

  gameDTO->shopComponent->loyalty += 10;

  if (_currentItem > 0 && gameDTO->shopComponent->items.size() == static_cast<size_t>(_currentItem)) _currentItem--;
}

void ShopScene::saleItem(SceneManager* sceneManager) {
  // TODO(AsTeFu): переделать первое условие, костыль какой-то
  if (gameDTO->shopComponent->items.empty() && gameDTO->inventoryComponent->items.empty()) return;

  if (_currentItem - static_cast<int>(gameDTO->shopComponent->items.size()) < 0) return;
  int currItem = _currentItem - static_cast<int>(gameDTO->shopComponent->items.size());

  int cost = gameDTO->inventoryComponent->items[currItem]->cost / 2 + gameDTO->specialComponent->getValue(CHARISMA) * 2;
  cost /= (100 + gameDTO->shopComponent->loyalty) / 100;
  gameDTO->walletComponent->cash += cost;
  gameDTO->inventoryComponent->deleteItem(currItem);

  gameDTO->shopComponent->loyalty += 5;

  if (_currentItem > 0 && gameDTO->inventoryComponent->items.size() == static_cast<size_t>(currItem)) _currentItem--;
}

void ShopScene::render() {
  // if (_currentItem == -1) return;

  Vector2 position(0, 0);
  Vector2 size(Config::getInstance().sizeTerminal.getX() * Config::getInstance().area.getX() / 100,
               Config::getInstance().sizeTerminal.getY() * Config::getInstance().area.getY() / 100);

  /*
  terminal_layer(0);
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  terminal_layer(8);
  terminal_crop(position.getX(), position.getY(), size.getX(), size.getY());
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());
  terminal_color(color_from_argb(255, 255, 255, 255));

  int leftIndent = 5;
  int topIndent = 2;

  int offsetX = position.getX() + leftIndent;
  int offsetY = position.getY() + topIndent;

  terminal_print(offsetX, offsetY, "Cost\t\tGoods");

  offsetY += 2;

  int costArea = 12;
  int i = 0;
  for (const auto& item : gameDTO->shopComponent->items) {
    if (i == _currentItem) terminal_print(offsetX - 3, offsetY, "=>");

    if (item->cost > gameDTO->walletComponent->cash)
      terminal_color("red");
    else
      terminal_color("yellow");

    int cost = item->cost - gameDTO->shopComponent->loyalty - gameDTO->specialComponent->getValue(CHARISMA) * 2;
    cost /= (100 + gameDTO->shopComponent->loyalty) / 100;

    terminal_printf(offsetX, offsetY, "%d$", cost);

    terminal_color("white");
    offsetY += item->printItemExtended(offsetX + costArea, offsetY) + 1;
    i++;
  }

  // Inventory
  offsetY += 2;
  // horizontalLine({position.getX(), offsetY}, size);
  terminal_print(position.getX() + 4, offsetY, "Inventory");

  // horizontalLine(position, size);
  // verticalBorder(position, size);
  terminal_print(offsetX, position.getY(), "SHOP");

  offsetY += 2;

  terminal_printf(offsetX, offsetY, "Available space: %d/%d", gameDTO->inventoryComponent->items.size(),
                  gameDTO->inventoryComponent->maxItems);

  offsetY += 2;

  for (const auto& item : gameDTO->inventoryComponent->items) {
    if (_currentItem == i) terminal_print(offsetX - 3, offsetY, "=>");

    int cost = item->cost / 2 + gameDTO->specialComponent->getValue(CHARISMA) * 2;
    cost /= (100 + gameDTO->shopComponent->loyalty) / 100;

    terminal_printf(offsetX, offsetY, "[color=yellow]%d$", cost);

    offsetY += item->printItemExtended(offsetX + costArea, offsetY) + 1;
    i++;
  }

  // Right side
  position = {Config::getInstance().sizeTerminal.getX() * Config::getInstance().area.getX() / 100, 0};
  size = {Config::getInstance().sizeTerminal.getX() * (100 - Config::getInstance().area.getY()) / 100,
          Config::getInstance().sizeTerminal.getY()};

  terminal_layer(1);
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  terminal_layer(9);
  terminal_crop(position.getX(), position.getY(), size.getX(), size.getY());
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  offsetX = position.getX() + leftIndent;
  offsetY = position.getY() + topIndent;

  // horizontalBorder(position, size);

  // Trader info
  terminal_printf(position.getX() + leftIndent, position.getY(), "TRADER");

  terminal_printf(offsetX, offsetY++, "Shopname: %s", "Magnit");
  terminal_printf(offsetX, offsetY++, "Loyalty: %d", gameDTO->shopComponent->loyalty);

  // You
  offsetY += 3;

  // horizontalLine({position.getX(), offsetY}, size);
  terminal_printf(position.getX() + leftIndent, offsetY, "YOU");

  offsetY += 2;

  terminal_printf(offsetX, offsetY++, "Money: %d", gameDTO->walletComponent->cash);
  terminal_printf(offsetX, offsetY++, "Charisma: %d", gameDTO->specialComponent->getValue(CHARISMA));

  // Equipments

  offsetY += 1;
  // horizontalLine({position.getX(), offsetY}, size);
  terminal_printf(position.getX() + leftIndent, offsetY, "EQUIPMENTS");

  offsetY += 2;

  offsetY += gameDTO->weaponComponent->weapon->printItemExtended(offsetX, offsetY) + 1;
  for (const auto& equipment : gameDTO->armorComponent->equipments) {
    offsetY += equipment.second->printItemExtended(offsetX, offsetY) + 1;
  }

  // verticalBorder(position, size); */
}

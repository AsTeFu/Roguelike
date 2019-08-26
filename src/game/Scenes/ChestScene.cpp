//
// Created by AsTeFu on 27.07.2019.
//

#include "game/Scenes/ChestScene.h"
#include <BearLibTerminal.h>
#include <game/Utility/DTO/ChestDTO.h>
#include <algorithm>
#include <string>
#include "game/Scenes/GameScene.h"
#include "game/Utility/ConfigTerminal.h"
#include "game/Utility/Input.h"

// TODO(AsTeFu): зарефакторить

void ChestScene::update(SceneManager* sceneManager) {
  if (Input::isPressed(TK_ESCAPE)) {
    terminal_clear_area(ConfigTerminal::positionChestScene.getX(), ConfigTerminal::positionChestScene.getY(),
                        ConfigTerminal::sizeChestScene.getX(), ConfigTerminal::sizeChestScene.getY());
    sceneManager->switchScene("Game");
  }

  if (_currentItem == -1) return;

  if (Input::isPressed(TK_UP)) increase();
  if (Input::isPressed(TK_DOWN)) decrease();

  if (Input::isPressed(TK_SPACE)) equipMenu(sceneManager);
  if (Input::isPressed(TK_E)) takeMenu(sceneManager);
}
void ChestScene::equipMenu(SceneManager* context) {
  auto item = gameDTO->chestComponent->items[_currentItem].get();
  if (item->itemType == ArmorType) {
    auto* armor = new Armor(*dynamic_cast<Armor*>(item));
    auto* pItem = new Armor(*gameDTO->armorComponent->equipments[armor->slot]);
    gameDTO->chestComponent->items[_currentItem] = std::unique_ptr<Armor>(pItem);
    gameDTO->armorComponent->equipments[armor->slot] = std::unique_ptr<Armor>(armor);
  }
  if (item->itemType == WeaponType) {
    auto* weapon = new Weapon(*dynamic_cast<Weapon*>(item));
    auto* pItem = new Weapon(*gameDTO->weaponComponent->weapon);
    gameDTO->chestComponent->items[_currentItem] = std::unique_ptr<Weapon>(pItem);
    gameDTO->weaponComponent->weapon = std::unique_ptr<Weapon>(weapon);
  }
  if (item->itemType == CoinType) {
    gameDTO->walletComponent->cash += dynamic_cast<CoinItem*>(item)->cost;
    gameDTO->chestComponent->deleteItem(_currentItem);
  }
  if (item->itemType == MedkitType) {
    gameDTO->healthComponent->health += dynamic_cast<MedkitItem*>(item)->health;
    gameDTO->chestComponent->deleteItem(_currentItem);
  }
  if (item->itemType == FoodType) {
    gameDTO->starvationComponent->currentFood += dynamic_cast<FoodItem*>(item)->food;
    gameDTO->chestComponent->deleteItem(_currentItem);
  }

  gameDTO->specialComponent->addictiveSpecial.clear();
  for (const auto& armor : gameDTO->armorComponent->equipments) {
    for (const auto& effect : armor.second->effects) {
      for (int i = 0; i < effect.second; ++i) {
        gameDTO->specialComponent->addictiveSpecial.addPoint(effect.first);
      }
    }
  }

  if (static_cast<int>(gameDTO->chestComponent->items.size()) == _currentItem) _currentItem--;
  if (gameDTO->chestComponent->items.empty()) {
    _currentItem = -1;
    terminal_clear_area(ConfigTerminal::positionChestScene.getX() + 1, ConfigTerminal::positionChestScene.getY() + 2,
                        ConfigTerminal::sizeChestScene.getX() - 2, 1);
    terminal_printf(ConfigTerminal::positionChestScene.getX() + 5, ConfigTerminal::positionChestScene.getY() + 2,
                    "Chest is empty");
  }
}

void ChestScene::takeMenu(SceneManager* context) {
  if (gameDTO->inventoryComponent->items.size() < gameDTO->inventoryComponent->maxItems) {
    auto item = gameDTO->chestComponent->items[_currentItem].get();

    int clearArea = 1;

    if (item->itemType == CoinType) {
      gameDTO->walletComponent->cash += dynamic_cast<CoinItem*>(item)->cost;
    }
    if (item->itemType == ArmorType) {
      auto* armor = new Armor(*dynamic_cast<Armor*>(item));
      gameDTO->inventoryComponent->items.push_back(std::unique_ptr<Armor>(armor));
      clearArea += dynamic_cast<Armor*>(item)->effects.size();
    }
    if (item->itemType == WeaponType) {
      auto* weapon = new Weapon(*dynamic_cast<Weapon*>(item));
      gameDTO->inventoryComponent->items.push_back(std::unique_ptr<Weapon>(weapon));
    }

    gameDTO->chestComponent->deleteItem(_currentItem);

    if (gameDTO->chestComponent->items.size() == static_cast<size_t>(_currentItem)) _currentItem--;
    if (gameDTO->chestComponent->items.empty()) {
      _currentItem = -1;
      terminal_clear_area(ConfigTerminal::positionChestScene.getX() + 1, ConfigTerminal::positionChestScene.getY() + 2,
                          ConfigTerminal::sizeChestScene.getX() - 2, clearArea);
      terminal_printf(ConfigTerminal::positionChestScene.getX() + 5, ConfigTerminal::positionChestScene.getY() + 2,
                      "Chest is empty");
    }
  }
}

void ChestScene::decrease() {
  _currentItem = std::min<int>(gameDTO->chestComponent->items.size() - 1, _currentItem + 1);
}
void ChestScene::increase() {
  _currentItem = std::max(0, _currentItem - 1);
}

void ChestScene::start(SceneManager* sceneManager) {
  gameDTO = sceneManager->getContext()->getObject<ChestDTO>();
  if (!gameDTO->chestComponent->items.empty()) _currentItem = 0;
}
void ChestScene::end(SceneManager* sceneManager) {
  Scene::end(sceneManager);
}
void ChestScene::render() {
  if (_currentItem == -1) return;

  terminal_layer(1);
  terminal_clear_area(ConfigTerminal::positionChestScene.getX(), ConfigTerminal::positionChestScene.getY(),
                      ConfigTerminal::sizeChestScene.getX(), ConfigTerminal::sizeChestScene.getY());

  terminal_layer(8);
  terminal_clear_area(ConfigTerminal::positionChestScene.getX(), ConfigTerminal::positionChestScene.getY(),
                      ConfigTerminal::sizeChestScene.getX(), ConfigTerminal::sizeChestScene.getY());

  terminal_color(color_from_argb(255, 255, 255, 255));

  int leftOffset = 5;
  int topOffset = 2;

  int offsetX = ConfigTerminal::positionChestScene.getX() + leftOffset;
  int offsetY = ConfigTerminal::positionChestScene.getY() + topOffset;

  int i = 0;
  for (const auto& item : gameDTO->chestComponent->items) {
    if (_currentItem == i) terminal_print(offsetX - 3, offsetY, "=>");
    offsetY += item->printItemExtended(offsetX, offsetY) + 1;
    i++;
  }
  offsetY++;

  horizontalLine({ConfigTerminal::positionChestScene.getX(), ConfigTerminal::positionChestScene.getY() + ++offsetY},
                 ConfigTerminal::sizeChestScene);
  terminal_print(ConfigTerminal::positionChestScene.getX() + leftOffset,
                 ConfigTerminal::positionChestScene.getY() + offsetY, "EQUIPMENTS");

  verticalBorder(ConfigTerminal::positionChestScene, ConfigTerminal::sizeChestScene);
  horizontalBorder(ConfigTerminal::positionChestScene, ConfigTerminal::sizeChestScene);

  terminal_print(ConfigTerminal::positionChestScene.getX() + leftOffset, ConfigTerminal::positionChestScene.getY(),
                 "CHEST");

  offsetY += 2;

  offsetY += gameDTO->weaponComponent->weapon->printItemExtended(offsetX, offsetY) + 1;
  for (const auto& pair : gameDTO->armorComponent->equipments) {
    offsetY += pair.second->printItemExtended(offsetX, offsetY) + 1;
  }

  terminal_color(color_from_argb(255, 255, 255, 255));
  terminal_print(offsetX, ConfigTerminal::sizeChestScene.getY() - 2, "Equip - SPACE\tTake - E\tExit - ESC");
}

//
// Created by AsTeFu on 29.07.2019.
//

#include "game/Scenes/BackpackScene.h"
#include <BearLibTerminal.h>
#include <algorithm>
#include <string>
#include "game/Utility/Input.h"

void BackpackScene::update(SceneManager* sceneManager) {
  if (Input::isPressed(TK_ESCAPE) || Input::isPressed(TK_I)) {
    // terminal_clear_area(ConfigTerminal::positionChestScene.getX(), ConfigTerminal::positionChestScene.getY(),
    //                     ConfigTerminal::sizeChestScene.getX(), ConfigTerminal::sizeChestScene.getY());
    sceneManager->switchScene("Game");
  }
  if (Input::isPressed(TK_UP)) increase();
  if (Input::isPressed(TK_DOWN)) decrease();
  if (Input::isPressed(TK_C)) deleteMenu(sceneManager);

  if (Input::isPressed(TK_SPACE)) equipMenu(sceneManager);
}
void BackpackScene::start(SceneManager* sceneManager) {
  backpack = _context->getObject<BackpackDTO>();
  _currentItem = 0;
}
void BackpackScene::end(SceneManager* context) {}
void BackpackScene::render() {
  // Inventory
  Vector2 position{};
  Vector2 size(ConfigTerminal::sizeTerminal.getX() * ConfigTerminal::areaX / 100,
               ConfigTerminal::sizeTerminal.getY() * ConfigTerminal::areaY / 100);

  terminal_layer(0);
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  terminal_layer(9);
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  terminal_color(color_from_argb(255, 255, 255, 255));

  int leftIndent = 5;
  int topIndent = 2;
  int offsetX = position.getX() + leftIndent;
  int offsetY = position.getY() + topIndent;

  horizontalLine(position, size);
  verticalBorder(position, size);
  terminal_printf(offsetX, position.getY(), "EQUIPMENTS");

  terminal_printf(offsetX, offsetY++, "Weapon:");
  offsetX += 3;

  if (_currentItem == 0) terminal_print(offsetX - 3, offsetY, "=>");
  offsetY += backpack->weaponComponent->weapon->printItemExtended(offsetX, offsetY) + 1;
  offsetY += 1;

  terminal_printf(offsetX - 3, offsetY++, "Armors:");
  int i = 1;
  for (const auto& pair : backpack->armorComponent->equipments) {
    if (_currentItem == i) terminal_print(offsetX - 3, offsetY, "=>");
    offsetY += pair.second->printItemExtended(offsetX, offsetY) + 1;
    i++;
  }
  offsetY += 1;

  horizontalLine({position.getX(), position.getY() + offsetY}, size);
  terminal_print(offsetX, offsetY, "INVENTORY");

  offsetY += 2;

  terminal_printf(offsetX - 3, offsetY++, "Available space: %d/%d", backpack->inventoryComponent->items.size(),
                  backpack->inventoryComponent->maxItems);

  offsetY += 1;

  for (const auto& item : backpack->inventoryComponent->items) {
    if (_currentItem == i) terminal_print(offsetX - 3, offsetY, "=>");
    offsetY += item->printItemExtended(offsetX, offsetY) + 1;
    i++;
  }

  // SPECIAl
  position = {ConfigTerminal::sizeTerminal.getX() * ConfigTerminal::areaX / 100, 0};
  size = {ConfigTerminal::sizeTerminal.getX() * (100 - ConfigTerminal::areaX) / 100,
          ConfigTerminal::sizeTerminal.getY()};

  terminal_layer(1);
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  terminal_layer(9);
  terminal_clear_area(position.getX(), position.getY(), size.getX(), size.getY());

  offsetX = position.getX() + leftIndent;
  offsetY = position.getY() + topIndent;

  horizontalBorder(position, size);
  verticalBorder(position, size);
  terminal_printf(position.getX() + leftIndent, position.getY(), "SPECIAL");

  for (const auto& stat : ConfigTerminal::statsSpecial) {
    int bonusEffect = 0;
    for (const auto& pairArmor : backpack->armorComponent->equipments) {
      if (pairArmor.second->effects.count(stat)) bonusEffect += pairArmor.second->effects[stat];
    }

    size_t maxLen = 16;
    std::string upperEffect{};
    for (size_t symbol = 0; symbol < maxLen; ++symbol) {
      if (symbol < stat.size())
        upperEffect.push_back(toupper(stat[symbol]));
      else if (symbol == stat.size())
        upperEffect.push_back(':');
      else
        upperEffect.push_back(' ');
    }

    int value = backpack->specialComponent->special.getValue(stat);

    if (bonusEffect)
      terminal_printf(offsetX, offsetY, "%s%d+%d", upperEffect.c_str(), value, bonusEffect);
    else
      terminal_printf(offsetX, offsetY, "%s%d", upperEffect.c_str(), value);

    offsetY += 2;
  }
}
void BackpackScene::decrease() {
  _currentItem = std::min<int>(backpack->inventoryComponent->items.size() + backpack->armorComponent->equipments.size(),
                               _currentItem + 1);
}
void BackpackScene::increase() {
  _currentItem = std::max(0, _currentItem - 1);
}

void BackpackScene::equipMenu(SceneManager* sceneManager) {
  if (_currentItem - static_cast<int>(backpack->armorComponent->equipments.size()) <= 0) return;

  int currItem = _currentItem - backpack->armorComponent->equipments.size() - 1;

  InventoryItem* item = backpack->inventoryComponent->items[currItem].get();

  if (item->itemType == ArmorType) {
    auto* armor = new Armor(*dynamic_cast<Armor*>(item));
    auto* pItem = new Armor(*backpack->armorComponent->equipments[armor->slot]);
    backpack->inventoryComponent->items[currItem] = std::unique_ptr<Armor>(pItem);
    backpack->armorComponent->equipments[armor->slot] = std::unique_ptr<Armor>(armor);
  }
  if (item->itemType == WeaponType) {
    auto* weapon = new Weapon(*dynamic_cast<Weapon*>(item));
    auto* pItem = new Weapon(*backpack->weaponComponent->weapon);
    backpack->inventoryComponent->items[currItem] = std::unique_ptr<Weapon>(pItem);
    backpack->weaponComponent->weapon = std::unique_ptr<Weapon>(weapon);
  }

  // TODO(AsTeFu): special
  backpack->specialComponent->addictiveSpecial.clear();
  for (const auto& armor : backpack->armorComponent->equipments) {
    for (const auto& effect : armor.second->effects) {
      for (int i = 0; i < effect.second; ++i) {
        backpack->specialComponent->addictiveSpecial.addPoint(effect.first);
      }
    }
  }
}

void BackpackScene::deleteMenu(SceneManager* sceneManager) {
  if (_currentItem - static_cast<int>(backpack->armorComponent->equipments.size()) <= 0) return;
  int currItem = _currentItem - backpack->armorComponent->equipments.size() - 1;

  backpack->inventoryComponent->deleteItem(currItem);

  if (backpack->inventoryComponent->items.size() == static_cast<size_t>(currItem)) _currentItem--;
}
BackpackScene::BackpackScene(Context* const context, SceneManager* sceneManager) : Scene(context, sceneManager) {}

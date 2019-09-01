//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_MEDKITITEM_H_
#define INCLUDE_GAME_ITEMS_MEDKITITEM_H_

#include <ecs/Entity.h>
#include <game/Components/ItemComponents/HealthComponent.h>
#include <utilities/Terminal.h>
#include "game/Items/InventoryItem.h"

class MedkitItem : public InventoryItem {
 public:
  int health;
  MedkitItem(int health, int cost) : InventoryItem(MedkitType, "Medkit", Usual, cost), health(health) {}
  void printItem(int x, int y) const override {
    Terminal::printf(x, y, "[color=red]%s:[/color] %d", name.c_str(), health);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
  void equipItem(Entity* player, ChestComponent* chestComponent, int indexItem) override {
    player->getComponent<HealthComponent>()->health += health;
    chestComponent->deleteItem(indexItem);
    GameLogger::getInstance().add("Health: [color=red]" + std::to_string(health));
  }
  void equipItem(Entity* player, int indexItem) override {
    std::cout << "Error. Medkit in inventory!" << std::endl;
  }
  void takeItem(Entity* player) override {
    player->getComponent<HealthComponent>()->health += health;
  }
};

#endif  // INCLUDE_GAME_ITEMS_MEDKITITEM_H_

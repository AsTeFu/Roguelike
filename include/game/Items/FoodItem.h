//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_FOODITEM_H_
#define INCLUDE_GAME_ITEMS_FOODITEM_H_

#include <game/Components/PlayerComponents/StarvationComponent.h>
#include <game/Logs/GameLogger.h>
#include <utilities/Terminal.h>

class FoodItem : public InventoryItem {
 public:
  int food;
  FoodItem(int food, int cost) : InventoryItem("Food", Usual, cost), food(food) {}
  void printItem(int x, int y) const override {
    Terminal::printf(x, y, "[color=green]%s:[/color] %d", name.c_str(), food);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
  void equipItem(Entity* player, ChestComponent* chestComponent, int indexItem) override {
    player->getComponent<StarvationComponent>()->currentFood += food;
    chestComponent->deleteItem(indexItem);
    GameLogger::getInstance().add("Food: [color=green]" + std::to_string(food));
  }
  void equipItem(Entity* player, int indexItem) override {
    std::cout << "Error. Food in inventory!" << std::endl;
  }
  void takeItem(Entity* player) override {
    player->getComponent<StarvationComponent>()->currentFood += food;
  }
};

#endif  // INCLUDE_GAME_ITEMS_FOODITEM_H_

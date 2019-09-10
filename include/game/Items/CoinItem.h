//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_COINITEM_H_
#define INCLUDE_GAME_ITEMS_COINITEM_H_

#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/PlayerComponents/WalletComponent.h>
#include <game/Logs/GameLogger.h>
#include <utilities/Terminal.h>
#include "game/Items/InventoryItem.h"

class CoinItem : public InventoryItem {
 public:
  explicit CoinItem(int cost) : InventoryItem("Coin", Usual, cost) {}
  void printItem(int x, int y) const override {
    Terminal::printf(x, y, "[color=yellow]%s:[/color] %d", name.c_str(), cost);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
  void equipItem(Entity* player, ChestComponent* chestComponent, int indexItem) override {
    player->getComponent<WalletComponent>()->cash += cost;
    chestComponent->deleteItem(indexItem);
    GameLogger::getInstance().add("Money: [color=yellow]" + std::to_string(cost));
  }
  void equipItem(Entity* player, int indexItem) override {
    std::cout << "Error. Coin in inventory!" << std::endl;
  }
  void takeItem(Entity* player) override {
    player->getComponent<WalletComponent>()->cash += cost;
  }
};

#endif  // INCLUDE_GAME_ITEMS_COINITEM_H_

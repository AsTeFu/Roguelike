//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_WEAPON_H_
#define INCLUDE_GAME_ITEMS_WEAPON_H_

#include <string>
#include "game/Items/InventoryItem.h"

class Weapon : public InventoryItem {
 public:
  int damage;
  int chanceCritical;

  Weapon(const std::string& name, Rarity rarity, int cost, int damage, int chanceCritical)
      : InventoryItem(WeaponType, name, rarity, cost), damage(damage), chanceCritical(chanceCritical) {}

  void printItem(int x, int y) const override;
  int printItemExtended(int x, int y) const override;
  void equipItem(Entity* player, ChestComponent* chestComponent, int indexItem) override;
  void takeItem(Entity* player) override;
  void equipItem(Entity* player, int indexItem) override;
};

#endif  // INCLUDE_GAME_ITEMS_WEAPON_H_

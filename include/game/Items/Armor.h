//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_ARMOR_H_
#define INCLUDE_GAME_ITEMS_ARMOR_H_

#include <game/Components/ItemComponents/SpecialComponent.h>
#include <game/Utility/Config.h>
#include <map>
#include <string>
#include "game/Items/InventoryItem.h"

class Armor : public InventoryItem {
 private:
  void updateEffects(const Entity* player, const Armor* newItem, const Armor* oldItem) const;

 public:
  Slot slot;
  int protect;
  int dodge;
  std::map<std::string, int> effects;

  Armor(const std::string& name, Rarity rarity, int cost, Slot slot, int protect, int dodge,
        std::map<std::string, int> effects);
  void printItem(int x, int y) const override;
  int printItemExtended(int x, int y) const override;
  void equipItem(Entity* player, ChestComponent* chestComponent, int index) override;
  void takeItem(Entity* player) override;
  void equipItem(Entity* player, int indexItem) override;
  std::string getSlotName() const;
};

#endif  // INCLUDE_GAME_ITEMS_ARMOR_H_

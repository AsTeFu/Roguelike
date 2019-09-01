//
// Created by AsTeFu on 31.08.2019.
//

#ifndef INCLUDE_GAME_ITEMS_INVENTORYITEM_H_
#define INCLUDE_GAME_ITEMS_INVENTORYITEM_H_

#include <ecs/Entity.h>
#include <string>

enum Slot { Helmet = 0, Armour, Boots };
enum Rarity { Usual = 1, Rare, Epic, Legendary, Mythical, Sublime };
enum ItemType { ArmorType, WeaponType, CoinType, MedkitType, FoodType };

class ChestComponent;

class InventoryItem {
 public:
  ItemType itemType;
  std::string name;
  Rarity rarity;
  int cost;

  InventoryItem(ItemType itemType, std::string name, Rarity rarity, int cost)
      : itemType(itemType), name(std::move(name)), rarity(rarity), cost(cost) {}

  virtual ~InventoryItem() = default;
  virtual void printItem(int x, int y) const = 0;
  virtual int printItemExtended(int x, int y) const = 0;
  virtual void equipItem(Entity* player, int indexItem) = 0;
  virtual void equipItem(Entity* player, ChestComponent* chestComponent, int indexItem) = 0;
  virtual void takeItem(Entity* player) = 0;
};

#endif  // INCLUDE_GAME_ITEMS_INVENTORYITEM_H_

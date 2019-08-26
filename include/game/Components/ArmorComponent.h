//
// Created by  on 09.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ARMORCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ARMORCOMPONENT_H_

#include <game/Utility/ConfigTerminal.h>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "ecs/IComponent.h"

enum Slot { Helmet = 0, Armour, Boots };
enum Rarity { Usual = 1, Rare, Epic, Legendary, Mythical, Sublime };
enum ItemType { ArmorType, WeaponType, CoinType, MedkitType, FoodType };

// TODO(AsTeFu): вот тут точно разнести этот ад

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
};

class CoinItem : public InventoryItem {
 public:
  explicit CoinItem(int cost) : InventoryItem(CoinType, "Coin", Usual, cost) {}
  void printItem(int x, int y) const override {
    terminal_printf(x, y, "[color=yellow]%s:[/color] %d", name.c_str(), cost);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
};
class MedkitItem : public InventoryItem {
 public:
  int health;
  MedkitItem(int health, int cost) : InventoryItem(MedkitType, "Medkit", Usual, cost), health(health) {}
  void printItem(int x, int y) const override {
    terminal_printf(x, y, "[color=red]%s:[/color] %d", name.c_str(), health);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
};
class FoodItem : public InventoryItem {
 public:
  int food;
  FoodItem(int food, int cost) : InventoryItem(FoodType, "Food", Usual, cost), food(food) {}
  void printItem(int x, int y) const override {
    terminal_printf(x, y, "[color=green]%s:[/color] %d", name.c_str(), food);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
};

class Armor : public InventoryItem {
 public:
  Slot slot;
  int protect;
  int dodge;
  std::map<std::string, int> effects;

  Armor(const std::string& name, Rarity rarity, int cost, Slot slot, int protect, int dodge,
        std::map<std::string, int> effects)
      : InventoryItem(ArmorType, name, rarity, cost),
        slot(slot),
        protect(protect),
        dodge(dodge),
        effects(std::move(effects)) {}

  void printItem(int x, int y) const override {
    terminal_printf(x, y, "%s [color=%s]%s[/color] PR: %d, DG: %d", getSlotName().c_str(),
                    ConfigTerminal::rarityName[rarity - 1].c_str(), name.c_str(), protect, dodge);
  }
  int printItemExtended(int x, int y) const override {
    int leftIndent = 4;
    printItem(x, y);
    int i = 0;
    for (const auto& effect : effects) {
      terminal_printf(x + leftIndent, ++y, "%s: %d", effect.first.c_str(), effect.second);
      i++;
    }
    return i;
  }
  std::string getSlotName() const {
    if (slot == Helmet) return "Helmet:";
    if (slot == Armour) return "Armour:";
    if (slot == Boots) return "Boots: ";
    return "Unknown";
  }
};

class ArmorComponent : public IComponent {
 public:
  std::map<Slot, std::unique_ptr<Armor>> equipments;
  explicit ArmorComponent(const std::vector<Armor*>& armors) {
    for (const auto& armor : armors) {
      equipments[armor->slot] = std::unique_ptr<Armor>(armor);
    }
  }
  ArmorComponent(const ArmorComponent& armorComponent) {
    for (const auto& equipment : armorComponent.equipments) {
      equipments[equipment.first] = std::unique_ptr<Armor>(equipment.second.get());
    }
  }

  int getProtect() const {
    int protect = 0;
    for (const auto& equipment : equipments) {
      protect += equipment.second->protect;
    }
    return protect;
  }

  std::vector<Armor*> getEquipments() {
    std::vector<Armor*> armors;
    for (const auto& armor : equipments) {
      armors.push_back(armor.second.get());
    }
    return armors;
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_ARMORCOMPONENT_H_

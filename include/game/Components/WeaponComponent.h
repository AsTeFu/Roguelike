//
// Created by  on 09.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_WEAPONCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_WEAPONCOMPONENT_H_

#include <game/Components/ArmorComponent.h>
#include <string>
#include <utility>
#include "ecs/IComponent.h"

class Weapon : public InventoryItem {
 public:
  int damage;
  int chanceCritical;

  Weapon(const std::string& name, Rarity rarity, int cost, int damage, int chanceCritical)
      : InventoryItem(WeaponType, name, rarity, cost), damage(damage), chanceCritical(chanceCritical) {}

  void printItem(int x, int y) const override {
    terminal_printf(x, y, "Weapon: [color=%s]%s[/color] DMG: %d, CR: %d",
                    ConfigTerminal::rarityName[rarity - 1].c_str(), name.c_str(), damage, chanceCritical);
  }
  int printItemExtended(int x, int y) const override {
    printItem(x, y);
    return 0;
  }
};

class WeaponComponent : public IComponent {
 public:
  std::unique_ptr<Weapon> weapon;
  explicit WeaponComponent(Weapon* weapon) {
    this->weapon = std::unique_ptr<Weapon>(weapon);
  }
  WeaponComponent(const WeaponComponent& weaponComponent) {
    weapon = std::unique_ptr<Weapon>(weaponComponent.weapon.get());
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_WEAPONCOMPONENT_H_

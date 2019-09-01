//
// Created by AsTeFu on 31.08.2019.
//

#include <game/Components/EnvironmentComponents/ChestComponent.h>
#include <game/Components/ItemComponents/InventoryComponent.h>
#include <game/Components/ItemComponents/WeaponComponent.h>
#include <game/Items/Weapon.h>
#include <game/Utility/Config.h>
#include <utilities/Terminal.h>

int Weapon::printItemExtended(int x, int y) const {
  printItem(x, y);
  return 0;
}
void Weapon::printItem(int x, int y) const {
  Terminal::printf(x, y, "Weapon: [color=%s]%s[/color] DMG: %d, CR: %d",
                   Config::getInstance().rarityNames[rarity - 1].c_str(), name.c_str(), damage, chanceCritical);
}
void Weapon::equipItem(Entity* player, ChestComponent* chestComponent, int indexItem) {
  auto weaponComponent = player->getComponent<WeaponComponent>();

  auto* newWeapon = new Weapon(*this);
  auto* oldWeapon = new Weapon(*weaponComponent->weapon);
  chestComponent->items[indexItem] = std::unique_ptr<Weapon>(oldWeapon);
  weaponComponent->weapon = std::unique_ptr<Weapon>(newWeapon);
}
void Weapon::equipItem(Entity* player, int indexItem) {
  auto* newWeapon = new Weapon(*this);
  auto* oldWeapon = new Weapon(*player->getComponent<WeaponComponent>()->weapon);
  player->getComponent<InventoryComponent>()->items[indexItem] = std::unique_ptr<Weapon>(oldWeapon);
  player->getComponent<WeaponComponent>()->weapon = std::unique_ptr<Weapon>(newWeapon);
}
void Weapon::takeItem(Entity* player) {
  auto* weapon = new Weapon(*this);
  player->getComponent<InventoryComponent>()->items.push_back(std::unique_ptr<Weapon>(weapon));
}

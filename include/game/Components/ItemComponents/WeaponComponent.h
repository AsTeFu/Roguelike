//
// Created by  on 09.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_WEAPONCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_WEAPONCOMPONENT_H_

#include <game/Components/ItemComponents/ArmorComponent.h>
#include <game/Items/Weapon.h>
#include <string>
#include <utility>
#include "ecs/IComponent.h"

class WeaponComponent : public IComponent {
 public:
  std::unique_ptr<Weapon> weapon;
  explicit WeaponComponent(Weapon* weapon) {
    this->weapon = std::unique_ptr<Weapon>(weapon);
  }
  explicit WeaponComponent(WeaponComponent* weaponComponent) {
    weapon = std::unique_ptr<Weapon>(weaponComponent->weapon.get());
  }
  WeaponComponent(const WeaponComponent& weaponComponent) {
    weapon = std::unique_ptr<Weapon>(weaponComponent.weapon.get());
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_WEAPONCOMPONENT_H_

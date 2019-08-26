//
// Created by  on 09.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_DAMAGEEVENT_H_
#define INCLUDE_GAME_COMPONENTS_DAMAGEEVENT_H_

#include <ecs/Entity.h>
#include "ecs/IComponent.h"
#include "game/Components/WeaponComponent.h"

class DamageEvent : public IComponent {
 public:
  Weapon* weapon;
  Entity* target;
  DamageEvent(Weapon* weapon, Entity* target) : weapon(weapon), target(target) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_DAMAGEEVENT_H_

//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_DAMAGECOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_DAMAGECOMPONENT_H_

#include "ecs/IComponent.h"

class DamageComponent : public IComponent {
 public:
  int damage;
  explicit DamageComponent(int damage) : damage(damage) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_DAMAGECOMPONENT_H_

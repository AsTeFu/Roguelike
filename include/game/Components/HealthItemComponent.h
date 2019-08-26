//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_HEALTHITEMCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_HEALTHITEMCOMPONENT_H_

#include "ecs/IComponent.h"

class HealthItemComponent : public IComponent {
 public:
  int health;
  explicit HealthItemComponent(int health) : health(health) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_HEALTHITEMCOMPONENT_H_

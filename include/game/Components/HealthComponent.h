//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_HEALTHCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_HEALTHCOMPONENT_H_

#include "ecs/IComponent.h"

class HealthComponent : public IComponent {
 public:
  int health;
  explicit HealthComponent(int startHealth) : health(startHealth) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_HEALTHCOMPONENT_H_

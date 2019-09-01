//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_STARVATIONCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_STARVATIONCOMPONENT_H_

#include "ecs/IComponent.h"

class StarvationComponent : public IComponent {
 public:
  int currentFood;
  explicit StarvationComponent(int startFood) : currentFood(startFood) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_STARVATIONCOMPONENT_H_

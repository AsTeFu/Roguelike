//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_FOODITEMCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_FOODITEMCOMPONENT_H_

#include "ecs/IComponent.h"

class FoodItemComponent : public IComponent {
 public:
  int food;
  explicit FoodItemComponent(int food) : food(food) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_FOODITEMCOMPONENT_H_

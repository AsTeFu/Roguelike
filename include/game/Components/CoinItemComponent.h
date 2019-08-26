//
// Created by  on 03.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_COINITEMCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_COINITEMCOMPONENT_H_

#include "ecs/IComponent.h"

class CoinItemComponent : public IComponent {
 public:
  int cost;
  explicit CoinItemComponent(int money) : cost(money) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_COINITEMCOMPONENT_H_

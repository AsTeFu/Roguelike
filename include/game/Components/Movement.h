//
// Created by AsTeFu on 02.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_MOVEMENT_H_
#define INCLUDE_GAME_COMPONENTS_MOVEMENT_H_

#include "ecs/IComponent.h"
#include "game/Utility/Vector2.h"

class Movement : public IComponent {
 public:
  Vector2 direction;
};

#endif  // INCLUDE_GAME_COMPONENTS_MOVEMENT_H_

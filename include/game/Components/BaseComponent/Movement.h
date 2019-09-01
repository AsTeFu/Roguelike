//
// Created by AsTeFu on 02.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_BASECOMPONENT_MOVEMENT_H_
#define INCLUDE_GAME_COMPONENTS_BASECOMPONENT_MOVEMENT_H_

#include "Utilities/Vector2.h"
#include "ecs/IComponent.h"

class Movement : public IComponent {
 public:
  Vector2 direction;
};

#endif  // INCLUDE_GAME_COMPONENTS_BASECOMPONENT_MOVEMENT_H_

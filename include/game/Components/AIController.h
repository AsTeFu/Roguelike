//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_AICONTROLLER_H_
#define INCLUDE_GAME_COMPONENTS_AICONTROLLER_H_

#include "ecs/IComponent.h"
#include "game/Utility/Vector2.h"

class AIController : public IComponent {
 public:
  Vector2 lastPosition{};
};

#endif  // INCLUDE_GAME_COMPONENTS_AICONTROLLER_H_

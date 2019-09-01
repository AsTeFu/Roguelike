//
// Created by  on 08.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_MOVEMENTEVENT_H_
#define INCLUDE_GAME_COMPONENTS_MOVEMENTEVENT_H_

#include <Utilities/Vector2.h>
#include "ecs/IComponent.h"

class MovementEvent : public IComponent {
 public:
  size_t idEntity;
  Vector2 direction;
  MovementEvent(size_t idEntity, const Vector2& direction) : idEntity(idEntity), direction(direction) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_MOVEMENTEVENT_H_

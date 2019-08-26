//
// Created by AsTeFu on 01.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_TRANSFORM_H_
#define INCLUDE_GAME_COMPONENTS_TRANSFORM_H_

#include "ecs/IComponent.h"
#include "game/Utility/Vector2.h"

class Transform : public IComponent {
 public:
  Vector2 position;
  explicit Transform(const Vector2& position) : position(position) {}
  Transform(int x, int y) : position(x, y) {}
  Transform() : position() {}
};

#endif  // INCLUDE_GAME_COMPONENTS_TRANSFORM_H_

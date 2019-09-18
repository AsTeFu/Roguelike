//
// Created by AsTeFu on 18.09.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_BASECOMPONENT_LIGHTING_H_
#define INCLUDE_GAME_COMPONENTS_BASECOMPONENT_LIGHTING_H_

#include <ecs/IComponent.h>
#include <utilities/Vector2.h>

class Lighting : public IComponent {
 public:
  bool visible{false};
  bool isLit{};
  Vector2 renderPos{};
  explicit Lighting(const Vector2& renderPos) : renderPos(renderPos) {}
  Lighting(int x, int y) : renderPos(x, y) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_BASECOMPONENT_LIGHTING_H_

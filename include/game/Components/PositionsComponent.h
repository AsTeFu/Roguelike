//
// Created by  on 06.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_POSITIONSCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_POSITIONSCOMPONENT_H_

#include <unordered_set>
#include "ecs/IComponent.h"

class PositionsComponent : public IComponent {
 public:
  std::unordered_set<int> wallPositions;
  int width;
  explicit PositionsComponent(int width) : width(width) {}

  void addWall(int x, int y) {
    wallPositions.emplace(x + y * width);
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_POSITIONSCOMPONENT_H_

//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_COMPONENTS_STRUCTURECOMPONENT_H_
#define INCLUDE_EDITOR_COMPONENTS_STRUCTURECOMPONENT_H_

#include <Utilities/Vector2.h>
#include <editor/Tile.h>
#include <vector>
#include "ecs/IComponent.h"

class StructureComponent : public IComponent {
 public:
  std::vector<std::vector<Tile>> objects;
  Vector2 size;

  StructureComponent(int sizeX, int sizeY) : StructureComponent(Vector2{sizeX, sizeY}) {}
  explicit StructureComponent(const Vector2& size) : size(size) {
    for (int i = 0; i < size.getX(); ++i) {
      objects.emplace_back();
      for (int j = 0; j < size.getY(); ++j) {
        objects[i].emplace_back();
      }
    }
  }
};

#endif  // INCLUDE_EDITOR_COMPONENTS_STRUCTURECOMPONENT_H_

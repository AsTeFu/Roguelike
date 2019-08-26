//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_COMPONENTS_BRUSHCOMPONENT_H_
#define INCLUDE_ROOMCREATOR_COMPONENTS_BRUSHCOMPONENT_H_

#include <roomcreator/Tile.h>
#include <string>
#include "ecs/IComponent.h"

class BrushComponent : public IComponent {
 public:
  std::string name;
  char graphic;
  BrushComponent(std::string name, char brush) : name(std::move(name)), graphic(brush) {}
  explicit BrushComponent(BrushComponent* const brushComponent)
      : name(brushComponent->name), graphic(brushComponent->graphic) {}
};

#endif  // INCLUDE_ROOMCREATOR_COMPONENTS_BRUSHCOMPONENT_H_

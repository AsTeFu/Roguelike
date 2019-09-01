//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_EDITOR_COMPONENTS_COLORCOMPONENT_H_
#define INCLUDE_EDITOR_COMPONENTS_COLORCOMPONENT_H_

#include <Utilities/Color.h>
#include <string>
#include <utility>
#include "ecs/IComponent.h"

class ColorComponent : public IComponent {
 public:
  std::string name;
  Color color;
  ColorComponent(std::string name, Color color) : name(std::move(name)), color(color) {}
  explicit ColorComponent(ColorComponent* const colorComponent)
      : ColorComponent(colorComponent->name, colorComponent->color) {}
};

#endif  // INCLUDE_EDITOR_COMPONENTS_COLORCOMPONENT_H_

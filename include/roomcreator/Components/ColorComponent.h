//
// Created by  on 22.08.2019.
//

#ifndef INCLUDE_ROOMCREATOR_COMPONENTS_COLORCOMPONENT_H_
#define INCLUDE_ROOMCREATOR_COMPONENTS_COLORCOMPONENT_H_

#include <BearLibTerminal.h>
#include <roomcreator/Argb.h>
#include <string>
#include <utility>
#include "ecs/IComponent.h"

class ColorComponent : public IComponent {
 public:
  std::string name;
  Argb argb;
  color_t color;
  ColorComponent(std::string name, Argb argb)
      : name(std::move(name)), argb(argb), color(color_from_argb(argb.a, argb.r, argb.g, argb.b)) {}
  explicit ColorComponent(ColorComponent* const colorComponent)
      : ColorComponent(colorComponent->name, colorComponent->argb) {}

  void setColor(const std::string& nameColor) {
    name = nameColor;
    color = color_from_name(nameColor.c_str());
  }
};

#endif  // INCLUDE_ROOMCREATOR_COMPONENTS_COLORCOMPONENT_H_

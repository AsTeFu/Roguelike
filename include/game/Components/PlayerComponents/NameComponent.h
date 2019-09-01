//
// Created by  on 11.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_NAMECOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_NAMECOMPONENT_H_

#include <string>
#include <utility>
#include "ecs/IComponent.h"

class NameComponent : public IComponent {
 public:
  std::string name;
  explicit NameComponent(std::string name) : name(std::move(name)) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_NAMECOMPONENT_H_

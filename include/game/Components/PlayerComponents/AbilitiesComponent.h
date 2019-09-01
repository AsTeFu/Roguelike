//
// Created by  on 21.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_ABILITIESCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_ABILITIESCOMPONENT_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include "ecs/IComponent.h"

class Ability {
 public:
  std::string name;
  std::string description;
  Ability(std::string name, std::string description) : name(std::move(name)), description(std::move(description)) {}

  bool operator==(const Ability& rhs) const {
    return name == rhs.name;
  }
  bool operator!=(const Ability& rhs) const {
    return !(rhs == *this);
  }
};

class AbilitiesComponent : public IComponent {
 public:
  std::vector<Ability> abilities;
  int available{};

  bool hasAbility(const std::string& name) const {
    return std::count(abilities.begin(), abilities.end(), Ability(name, ""));
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_PLAYERCOMPONENTS_ABILITIESCOMPONENT_H_

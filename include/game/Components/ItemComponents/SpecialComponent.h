//
// Created by  on 10.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_SPECIALCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_SPECIALCOMPONENT_H_

#include <game/Player/Special.h>
#include <map>
#include <string>
#include <utility>
#include "ecs/IComponent.h"
#include "game/Utility/Config.h"

class SpecialComponent : public IComponent {
 public:
  Special special;
  Special addictiveSpecial;
  explicit SpecialComponent(Special special)
      : special(std::move(special)),
        addictiveSpecial(0, Config::getInstance().pointSpecialRange.maxValue, Config::getInstance().maxPointsSpecial) {}

  SpecialComponent(const SpecialComponent& specialComponent)
      : special(specialComponent.special), addictiveSpecial(specialComponent.addictiveSpecial) {}

  int getValue(StatSpecial stat) const {
    return special.getValue(stat) + addictiveSpecial.getValue(stat);
  }
  void setSpecials(SpecialComponent* specialComponent) {
    special = specialComponent->special;
    addictiveSpecial = specialComponent->addictiveSpecial;
  }
};

#endif  // INCLUDE_GAME_COMPONENTS_ITEMCOMPONENTS_SPECIALCOMPONENT_H_

//
// Created by  on 20.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_VISIBLECOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_VISIBLECOMPONENT_H_

#include "ecs/IComponent.h"

class VisibleComponent : public IComponent {
 public:
  bool visible;
  VisibleComponent() : visible(false) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_VISIBLECOMPONENT_H_

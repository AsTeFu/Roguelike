//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_PROTECTCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_PROTECTCOMPONENT_H_

#include "ecs/IComponent.h"

class ProtectComponent : public IComponent {
 public:
  int protect;
  explicit ProtectComponent(int protect) : protect(protect) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_PROTECTCOMPONENT_H_

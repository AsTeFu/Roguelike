//
// Created by  on 07.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_EXITCOMPONENT_H_
#define INCLUDE_GAME_COMPONENTS_EXITCOMPONENT_H_

#include "ecs/IComponent.h"
#include "game/RoomManager/Room.h"

class ExitComponent : public IComponent {
 public:
  bool direction;
  explicit ExitComponent(bool direction) : direction(direction) {}
};

#endif  // INCLUDE_GAME_COMPONENTS_EXITCOMPONENT_H_

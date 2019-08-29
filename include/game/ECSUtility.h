//
// Created by AsTeFu on 27.08.2019.
//

#ifndef INCLUDE_GAME_ECSUTILITY_H_
#define INCLUDE_GAME_ECSUTILITY_H_

#include <ecs/Entity.h>

class ECSUtility {
 public:
  static Entity* copyPlayer(Entity* const fromPlayer, Entity* toPlayer);
  static Entity* transferPlayer(Entity* const fromPlayer, Entity* toPlayer);
};

#endif  // INCLUDE_GAME_ECSUTILITY_H_

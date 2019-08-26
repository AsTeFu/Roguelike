//
// Created by AsTeFu on 03.08.2019.
//

#ifndef INCLUDE_GAME_COMPONENTS_COLLIDER_H_
#define INCLUDE_GAME_COMPONENTS_COLLIDER_H_

#include <ecs/Entity.h>
#include <memory>
#include <vector>
#include "ecs/IComponent.h"

class Collider : public IComponent {
 public:
  std::vector<Entity*> colls;
};

#endif  // INCLUDE_GAME_COMPONENTS_COLLIDER_H_
